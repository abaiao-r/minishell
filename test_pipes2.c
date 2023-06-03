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

char* get_command_path(char* command)
{
    char* path = NULL;
    //printf("which %s", command);

    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    } else if (pid == 0)
    {
        // Child process

        // Close the read end of the pipe
        close(fd[0]);

        // Redirect output to the pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        // Execute the "which" command
        char* arguments[] = {"which", command, NULL};
        char* envp[] = {NULL}; // Empty environment array
        execve("/usr/bin/which", arguments, envp);
        perror("execve failed");
        exit(1);
    } 
    else
    {
        // Parent process

        // Close the write end of the pipe
        close(fd[1]);

        // Read the output of the command from the pipe
        char result[MAX_COMMAND_LENGTH];
        ssize_t bytes_read = read(fd[0], result, sizeof(result) - 1);
        if (bytes_read > 0)
        {
            // Null-terminate the result string
            result[bytes_read] = '\0';

            // Remove the trailing newline character
            result[strcspn(result, "\n")] = '\0';

            // Allocate memory for the path and copy the result
            path = (char*)malloc(strlen(result) + 1);
            strcpy(path, result);
        }

        // Close the read end of the pipe
        close(fd[0]);

        // Wait for the child process to finish
        wait(NULL);
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