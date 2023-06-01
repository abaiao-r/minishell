#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void redirect_input(char* file) {
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void redirect_output(char* file, int append) {
    int flags = O_WRONLY | O_CREAT;
    if (append) {
        flags |= O_APPEND;
    } else {
        flags |= O_TRUNC;
    }
    int fd = open(file, flags, 0666);
    if (fd < 0) {
        perror("open failed");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

int main() {
    char input[1000];
    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    char* command = strtok(input, " ");

    char* arguments[100];
    int arg_count = 0;

    while (command != NULL) {
        if (strcmp(command, "<") == 0) {
            char* file = strtok(NULL, " ");
            redirect_input(file);
        } else if (strcmp(command, ">") == 0) {
            char* file = strtok(NULL, " ");
            redirect_output(file, 0);
        } else if (strcmp(command, ">>") == 0) {
            char* file = strtok(NULL, " ");
            redirect_output(file, 1);
        } else {
            arguments[arg_count++] = command;
        }
        command = strtok(NULL, " ");
    }

    arguments[arg_count] = NULL; // Set last argument to NULL for execvp

    execvp(arguments[0], arguments);
    perror("execvp failed");
    exit(1);
}