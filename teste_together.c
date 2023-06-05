#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_ARGS 100
#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100
#define BUFFER_SIZE 1024

char* ft_strtok(char* str, const char* delim)
{
    static char* next_token = NULL;

    if (str != NULL)
        next_token = str;
    if (next_token == NULL)
        return (NULL);
    size_t delim_len = strlen(delim);
    char* token_start = next_token;
    char* token_end = strstr(next_token, delim);

    if (token_end != NULL)
    {
        next_token = token_end + delim_len;
        *token_end = '\0';
    }
    else
        next_token = NULL;
    return (token_start);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		i++;
	}
	if (s[i] == '\n')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] && s2[j] != '\n')
		str[i++] = s2[j++];
	if (s2[j] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	free(s1);
	return (str);
}

int	stash_organizer(char *stash)
{
	int	i;
	int	j;
	int	isnewline;

	i = 0;
	j = 0;
	isnewline = 0;
	while (stash[i])
	{
		if (isnewline)
		{
			stash[j++] = stash[i];
		}
		if (stash[i] == '\n')
		{
			isnewline = 1;
		}
		stash[i++] = '\0';
	}
	return (isnewline);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	if (!stash[0])
		stash[read(fd, stash, BUFFER_SIZE)] = 0;
	while (stash[0])
	{
		line = ft_strjoin_gnl(line, stash);
		if (!line)
			return (NULL);
		if (stash_organizer(stash) == 1)
			break ;
		if (read(fd, stash, 0) < 0)
		{
			free(line);
			return (NULL);
		}
		stash[read(fd, stash, BUFFER_SIZE)] = 0;
	}
	return (line);
}

char* ft_strjoin(char const *s1, char const *s2)
{
    char* str;
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t total_len = len1 + len2 + 1;

    str = (char*)malloc(total_len * sizeof(char));
    if (!str)
    {
        return NULL;
    }
    strncpy(str, s1, len1);
    strncpy(str + len1, s2, len2);
    str[total_len - 1] = '\0';
    return str;
}

void redirect_input(char* file)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void redirect_output(char* file, int append)
{
    int flags = O_WRONLY | O_CREAT;

    if (append)
    {
        flags |= O_APPEND;
    }
    else
    {
        flags |= O_TRUNC;
    }
    int fd = open(file, flags, 0666);
    if (fd < 0)
    {
        perror("open failed");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

char* get_command_path(char* command)
{
    char* path = NULL;

    // Tokenize the PATH environment variable
    char* path_env = getenv("PATH");
    char* path_token = ft_strtok(path_env, ":");
    while (path_token != NULL)
    {
        // Construct the full command path
        char* command_path = ft_strjoin(path_token, "/");
        command_path = ft_strjoin(command_path, command);

        // Check if the command path is executable
        if (access(command_path, X_OK) == 0)
        {
            path = command_path;
            break;
        }

        free(command_path);
        path_token = ft_strtok(NULL, ":");
    }

    return path;
}

void execute_command(char* command)
{
    char* arguments[MAX_ARGS];
    int arg_count = 0;

    // Tokenize the command string
    char* token = ft_strtok(command, " \t\n");
    while (token != NULL) {
        arguments[arg_count] = token;
        arg_count++;
        token = ft_strtok(NULL, " \t\n");
    }

    arguments[arg_count] = NULL; // Set last argument to NULL for execve

    char* command_path = get_command_path(arguments[0]);
    if (command_path != NULL)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            char* envp[] = {NULL}; // Empty environment array
            execve(command_path, arguments, envp);
            perror("execve failed");
            free(command_path);
            exit(1);
        }
        else
        {
            // Parent process
            wait(NULL);
        }

        free(command_path);
    }
    else
    {
        printf("Command '%s' not found\n", arguments[0]);
        exit(1);
    }
}

void execute_commands(char** commands, int num_commands)
{
    int pipe_fd[2];  // Pipe file descriptors
    int in_fd = 0;   // Input file descriptor for the first command

    for (int i = 0; i < num_commands; i++)
    {
        // Create pipe for inter-process communication
        if (i < num_commands - 1)
        {
            if (pipe(pipe_fd) < 0)
            {
                perror("pipe failed");
                exit(1);
            }
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process

            // Redirect input from the previous command or file
            if (i != 0)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            // Redirect output to the next command or file
            if (i < num_commands - 1)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            char* command = commands[i];
            char* arguments[100];
            int arg_count = 0;

            char* token = ft_strtok(command, " ");
            while (token != NULL)
            {
                if (strcmp(token, "<") == 0)
                {
                    char* file = ft_strtok(NULL, " ");
                    redirect_input(file);
                }
                else if (strcmp(token, ">") == 0)
                {
                    char* file = ft_strtok(NULL, " ");
                    redirect_output(file, 0);
                }
                else if (strcmp(token, ">>") == 0)
                {
                    char* file = ft_strtok(NULL, " ");
                    redirect_output(file, 1);
                }
                else if (strcmp(token, "<<") == 0)
                {
                    // Handle "<<" input redirection
                    char* delimiter = ft_strtok(NULL, " ");
                    if (delimiter != NULL)
                    {
                        // Create a temporary file
                        char temp_file[] = "/tmp/tempfileXXXXXX";
                        int temp_fd = mkstemp(temp_file);
                        if (temp_fd < 0)
                        {
                            perror("mkstemp failed");
                            exit(1);
                        }

                        // Write input to the temporary file until the delimiter is found
                        char* line = NULL;
                        int found_delimiter = 0;

                        while (!found_delimiter)
                        {
                            line = get_next_line(STDIN_FILENO);
                            line[strcspn(line, "\n")] = '\0';  // Read input line using get_next_line
                            if (line == NULL)
                            {
                                perror("get_next_line failed");
                                exit(1);
                            }
                            if (strcmp(line, delimiter) == 0)
                            {
                                found_delimiter = 1;
                            }
                            else
                            {
                                strcat(line, "\n");  // Add newline character
                                write(temp_fd, line, strlen(line));
                            }
                            free(line);
                        }

                        // Close the temporary file
                        close(temp_fd);

                        // Reopen the temporary file for reading
                        temp_fd = open(temp_file, O_RDONLY);
                        if (temp_fd < 0)
                        {
                            perror("open failed");
                            exit(1);
                        }

                        // Set the temporary file as input for the command
                        dup2(temp_fd, STDIN_FILENO);
                        close(temp_fd);

                        // Remove the temporary file
                        unlink(temp_file);
                    }
                }

                else
                {
                    arguments[arg_count++] = token;
                }
                token = ft_strtok(NULL, " ");
            }

            arguments[arg_count] = NULL; // Set last argument to NULL for execve

            // Get the executable path from the PATH environment variable
            char* path = getenv("PATH");
            char* path_copy = strdup(path);
            char* path_token = ft_strtok(path_copy, ":");

            while (path_token != NULL)
            {
                char* executable_path = ft_strjoin(path_token, "/");
                executable_path = ft_strjoin(executable_path, arguments[0]);
                if (access(executable_path, X_OK) == 0)
                {
                    execve(executable_path, arguments, NULL);
                    perror("execve failed");
                    free(executable_path);
                    exit(1);
                }
                free(executable_path);
                path_token = ft_strtok(NULL, ":");
            }

            printf("Command '%s' not found\n", arguments[0]);
            exit(1);
        }
        else
        {
            // Parent process

            // Close the previous pipe's write end
            if (i > 0)
            {
                close(in_fd);
            }

            // Close the current pipe's read end
            if (i < num_commands - 1)
            {
                close(pipe_fd[1]);
                in_fd = pipe_fd[0];
            }
        }
    }

    // Wait for all child processes to finish
    while (num_commands > 0)
    {
        wait(NULL);
        num_commands--;
    }
}

int main(void)
{
    char input[MAX_COMMAND_LENGTH];
    char* commands[MAX_COMMANDS];
    int num_commands = 0;

    printf("Enter commands: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove trailing newline

    // Tokenize the input into commands
    char* token = ft_strtok(input, "|");
    while (token != NULL)
    {
        commands[num_commands] = token;
        num_commands++;
        token = ft_strtok(NULL, "|");
    }

    execute_commands(commands, num_commands);

    return (0);
}