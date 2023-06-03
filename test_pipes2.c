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
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

char* ft_strjoin(const char *s1, const char *s2)
{
    char* str;
    size_t len_s1 = strlen(s1);
    size_t len_s2 = strlen(s2);
    size_t total_len = len_s1 + len_s2;
    str = (char*)malloc(total_len + 1);
    if (!str)
    {
        return NULL;
    }
    strcpy(str, s1);
    strcpy(str + len_s1, s2);
    return str;
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

void execute_commands(char** commands, int num_commands) {
    int pipe_fd[2];
    int in_fd = 0; // Input file descriptor for the first command

    int i = 0;
    while(i < num_commands)
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
            execute_command(commands[i]);
            exit(0);  // Exit child process after executing the command
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
        i++;
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