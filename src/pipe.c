/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:58:20 by quackson          #+#    #+#             */
/*   Updated: 2023/05/10 21:56:17 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

void	execute_pipe(char **cmd1, int cmd1_num_tokens, char **cmd2, int cmd2_num_tokens)
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
}

/* 
int main()
{
	execute_pipe("echo hello", "grep hello");
	//execute_pipe("ls -l", "grep myfile.txt");
} */