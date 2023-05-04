/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:58:20 by quackson          #+#    #+#             */
/*   Updated: 2023/05/05 00:17:12 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

void execute_pipe(char* cmd1, char* cmd2) {
    // Create the pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child process
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Child process 1: redirect stdout to the write end of the pipe
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        // Parse and execute the first command
        char* cmd1_args[] = { "/bin/sh", "-c", cmd1, NULL };
        if (execve(cmd1_args[0], cmd1_args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }

    // Fork the second child process
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Child process 2: redirect stdin to the read end of the pipe
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);

        // Parse and execute the second command
        char* cmd2_args[] = { "/bin/sh", "-c", cmd2, NULL };
        if (execve(cmd2_args[0], cmd2_args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }

    // Close the pipe ends in the parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

/* int main()
{
	execute_pipe("echo hello", "grep hello");
	//execute_pipe("ls -l", "grep myfile.txt");
} */