/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:58:20 by quackson          #+#    #+#             */
/*   Updated: 2023/05/18 21:59:16 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

/* void run_commands(char** commands) {
    int num_commands = 1;
    char* command;
    char** commands_copy = commands;
    char* token = strtok(commands_copy, "|");

    while (token != NULL) {
        num_commands++;
        token = strtok(NULL, "|");
    }
	printf("num_commands: %d\n", num_commands);
    int pipes[num_commands - 1][2];
    int i, j = 0;
    int input_fd = 0;
    pid_t pid;

    for (i = 0; i < num_commands; i++) {
        if (pipe(pipes[i]) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        command = commands[j];
        j++;

        char** args = malloc(sizeof(char*) * 100);
        int k = 0;
        char* token = strtok(command, " ");

        while (token != NULL) {
            if (strcmp(token, "<") == 0) {
                token = strtok(NULL, " ");
                input_fd = open(token, O_RDONLY);
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }
            else if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " ");
                int output_fd = open(token, O_CREAT|O_WRONLY|O_TRUNC, 0644);
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }
            else if (strcmp(token, ">>") == 0) {
                token = strtok(NULL, " ");
                int output_fd = open(token, O_CREAT|O_WRONLY|O_APPEND, 0644);
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }
            else {
                args[k] = strdup(token);
                k++;
            }
            token = strtok(NULL, " ");
        }
        args[k] = NULL;

        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            if (i == 0 && num_commands > 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][0]);
                close(pipes[i][1]);
            }
            else if (i == num_commands - 1 && num_commands > 1) {
                dup2(input_fd, STDIN_FILENO);
                close(pipes[i - 1][1]);
                close(pipes[i - 1][0]);
            }
            else {
                dup2(pipes[i][1], STDOUT_FILENO);
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i][0]);
                close(pipes[i][1]);
                close(pipes[i - 1][0]);
                close(pipes[i - 1][1]);
            }
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else {
            if (i == num_commands - 1 && num_commands > 1) {
                waitpid(pid, NULL, 0);
            }
        }

        for (k = 0; k < 100; k++) {
            if (args[k] != NULL) {
                free(args[k]);
            }
            else {
                break;
            }
        }
        free(args);
    }
} */


char	**get_next_cmd(char **args)
{
	while (*args)
	{
		if (is_redirection(*args))
			return (args + 1);
		args++;
	}
	return (args);
}

int	count_tokens(char **args)
{
	int		i;

	i = 0;
	while (*args)
	{
		if (is_redirection(*args))
			return (i);
		args++;
		i++;
	}
	return (i);
}

void	print_command(char **args, int n_tokens)
{
	int	i;

	i = 0;
	while (args[i] && n_tokens--)
	{
		//printf("%s ", args[i]);
		i++;
	}
	//printf("\n");
}

char	*get_next_redirection(char **args)
{
	while (*args)
	{
		if (is_redirection(*args))
			return (*args);
		args++;
	}
	return (NULL);
}

/* void	handle_pipe(char *strs, int n_tokens)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exe_cmd(args, NULL, n_tokens, NULL);
	}
	else
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid2 == 0)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO); 
			close(pipe_fd[0]);
			exe_cmd(args + n_tokens + 1, NULL, count_tokens(args + n_tokens + 1), NULL);
		}
		else
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
} */

int	exe_commands(char **args)
{
	int		n_tokens;
	int		status;
	//int		pipe[2];
	char	*symbol;

		
	while (*args)
	{
		n_tokens = count_tokens(args);
		print_command(args, n_tokens);
		printf("n_tokens: %d\n", n_tokens);
		symbol = get_next_redirection(args);
		if (symbol)
		{
			printf("next redirection: %s\n", symbol);
			//status = handle_pipe(args, n_tokens);
		}
		else
			status = exe_cmd(args, NULL, n_tokens, NULL);
		if (n_tokens == 1 && status == EXIT)
			return (EXIT);
		args = get_next_cmd(args);
	}
	return (NO_EXIT);
}

/* void	execute_pipe(char **cmd1, int cmd1_num_tokens, char **cmd2, int cmd2_num_tokens)
{
	int		pipe_fd[2];
	pid_t	pid1;

	(void) cmd1;
	(void) cmd1_num_tokens;
	(void) cmd2;
	(void) cmd2_num_tokens;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		printf("exe cmd1\n");
		exe_cmd(cmd1, NULL, cmd1_num_tokens, NULL);
		exit(0);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	waitpid(pid1, NULL, 0);
	printf("exe cmd2\n");
	for (int i = 0; cmd2[i] != NULL; i++)
		printf("str: %s\n", cmd2[i]);
	exe_cmd(cmd2, NULL, cmd2_num_tokens, NULL);
	close(pipe_fd[0]);
} */

/* 
int main()
{
	execute_pipe("echo hello", "grep hello");
	//execute_pipe("ls -l", "grep myfile.txt");
} */