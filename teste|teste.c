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

char* get_command_path(char* command) {
    char* path = NULL;
    FILE* pipe = NULL;
    char command_string[MAX_COMMAND_LENGTH + 10];  // Additional space for "which " and null terminator
    sprintf(command_string, "which %s", command);

    // Open a pipe to the command
    pipe = popen(command_string, "r");
    if (pipe != NULL) {
        char result[MAX_COMMAND_LENGTH];
        // Read the output of the command
        if (fgets(result, sizeof(result), pipe) != NULL) {
            // Remove the trailing newline character
            result[strcspn(result, "\n")] = '\0';
            // Allocate memory for the path and copy the result
            path = (char*)malloc(strlen(result) + 1);
            strcpy(path, result);
        }
        // Close the pipe
        pclose(pipe);
    }

    return path;
}

void execute_command(char* command) {
    char* arguments[MAX_ARGS];
    int arg_count = 0;

    // Tokenize the command string
    char* token = strtok(command, " \t\n");
    while (token != NULL) {
        arguments[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " \t\n");
    }

    arguments[arg_count] = NULL; // Set last argument to NULL for execv

    char* command_path = get_command_path(arguments[0]);
    if (command_path != NULL) {
        execv(command_path, arguments);
        perror("execv failed");
        free(command_path);
    } else {
        printf("Command '%s' not found\n", arguments[0]);
        exit(1);
    }
}

void execute_commands(char** commands, int num_commands) {
    int pipe_fd[2];
    int in_fd = 0; // Input file descriptor for the first command

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

            // Check for input/output redirection
            char* input_redir = strchr(commands[i], '<');
            char* output_redir = strchr(commands[i], '>');
            if (input_redir != NULL) {
                char* file = strtok(input_redir + 1, " \t\n");
                int fd = open(file, O_RDONLY);
                if (fd < 0) {
                    perror("open failed");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            if (output_redir != NULL) {
                char* file = strtok(output_redir + 1, " \t\n");
                int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (fd < 0) {
                    perror("open failed");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            execute_command(commands[i]);
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
    for (int i = 0; i < num_commands; i++) {
        wait(NULL);
    }
}

int main() {
    char input[MAX_COMMAND_LENGTH];
    char* commands[MAX_COMMANDS];
    int num_commands = 0;

    printf("Enter commands: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove trailing newline

    // Tokenize the input into commands
    char* token = strtok(input, "|");
    while (token != NULL) {
        commands[num_commands] = token;
        num_commands++;
        token = strtok(NULL, "|");
    }

    execute_commands(commands, num_commands);

    return 0;
}

