
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
    char    *str;
    size_t  i;
    size_t  j;

    str = (char *)malloc(sizeof(*s1) * (strlen(s1) + strlen(s2) + 1));
    if (!str)
    {
        return (NULL);
    }
    i = 0;
    j = 0;
    while (s1[i])
    {
        str[j++] = s1[i];
        i++;
    }
    i = 0;
    while (s2[i])
    {
        str[j++] = s2[i];
        i++;
    }
    str[j] = '\0';
    return (str);
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
    char* path_token = strtok(path_env, ":");
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
        path_token = strtok(NULL, ":");
    }

    return path;
}

void execute_command(char* command)
{
    char* arguments[MAX_ARGS];
    int arg_count = 0;

    // Tokenize the command string
    char* token = strtok(command, " \t\n");
    while (token != NULL) {
        arguments[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " \t\n");
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
        } else if (pid == 0)
        {
            // Child process
            char* envp[] = {NULL}; // Empty environment array
            execve(command_path, arguments, envp);
            perror("execve failed");
            free(command_path);
            exit(1);
        } else
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

    for (int i = 0; i < num_commands; i++) {
        // Create pipe for inter-process communication
        if (i < num_commands - 1) {
            if (pipe(pipe_fd) < 0) {
                perror("pipe failed");
                exit(1);
            }
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process

            // Redirect input from the previous command or file
            if (i != 0) {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            // Redirect output to the next command or file
            if (i < num_commands - 1) {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            char* command = commands[i];
            char* arguments[100];
            int arg_count = 0;

            char* token = strtok(command, " ");
            while (token != NULL) {
                if (strcmp(token, "<") == 0) {
                    char* file = strtok(NULL, " ");
                    redirect_input(file);
                } else if (strcmp(token, ">") == 0) {
                    char* file = strtok(NULL, " ");
                    redirect_output(file, 0);
                } else if (strcmp(token, ">>") == 0) {
                    char* file = strtok(NULL, " ");
                    redirect_output(file, 1);
                } else {
                    arguments[arg_count++] = token;
                }
                token = strtok(NULL, " ");
            }

            arguments[arg_count] = NULL; // Set last argument to NULL for execve

            // Get the executable path from the PATH environment variable
            char* path = getenv("PATH");
            char* path_copy = strdup(path);
            char* path_token = strtok(path_copy, ":");

            while (path_token != NULL) {
                char* executable_path = ft_strjoin(path_token, "/");
                executable_path = ft_strjoin(executable_path, arguments[0]);
                if (access(executable_path, X_OK) == 0) {
                    execve(executable_path, arguments, NULL);
                    perror("execve failed");
                    free(executable_path);
                    exit(1);
                }
                free(executable_path);
                path_token = strtok(NULL, ":");
            }

            printf("Command '%s' not found\n", arguments[0]);
            exit(1);
        } else {
            // Parent process

            // Close the previous pipe's write end
            if (i > 0) {
                close(in_fd);
            }

            // Close the current pipe's read end
            if (i < num_commands - 1) {
                close(pipe_fd[1]);
                in_fd = pipe_fd[0];
            }
        }
    }

    // Wait for all child processes to finish
    while (num_commands > 0) {
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
    char* token = strtok(input, "|");
    while (token != NULL)
    {
        commands[num_commands] = token;
        num_commands++;
        token = strtok(NULL, "|");
    }

    execute_commands(commands, num_commands);

    return (0);
}
