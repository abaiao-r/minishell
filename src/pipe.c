/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:58:20 by quackson          #+#    #+#             */
/*   Updated: 2023/06/03 17:51:26 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

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

/* void	redirect(char **args, int num_tokens, int *in_fd, t_minishell *minishell)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("Error");
		exit(1);
	}
	//exe cmd

	close(pipefd[1]);
	if (*in_fd != 0)
		close(*in_fd);
	*in_fd = pipefd[0];
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(pipefd[0]);
		printf("EXECUTED 1\n");
		dup2(pipefd[1], STDOUT_FILENO);
		// echo hello 
		// write(pipefd[1], input, strlen(input)); 
		exe_cmd(minishell, args, num_tokens, *in_fd, pipefd[1]);
		exit(0);
		// grep h 
		// execve(grep h) -> 
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
} */

int	cmd_has_pipe(char **args)
{
	while (*args)
	{
		if (!strncmp(*args, "|", 1))
			return (1);
		args++;
	}
	return (0);
}

void redirect_2(char** commands) {
    int pipe_fd[2];
    int in_fd = 0; // Input file descriptor for the first command
    int i = 0;
	int	has_pipe;

    while (*commands)
    {
		has_pipe = cmd_has_pipe(commands);
        // Create pipe for inter-process communication
        if (has_pipe)
        {
            if (pipe(pipe_fd) < 0)
            {
                perror("pipe failed");
                exit(1);
            }
        }
		printf("pipe tokens: %d\n", count_tokens(commands));
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
            if (has_pipe)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            exe_cmd(commands, NULL, count_tokens(commands), NULL);
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
            if (has_pipe)
            {
                close(pipe_fd[1]);
                in_fd = pipe_fd[0];
            }
			wait(NULL);
        }
        i++;
		commands = get_next_cmd(commands);
    }
}

int	exe_commands(t_minishell *minishell)
{
	//int		num_tokens;
	//int		status;
	//int		in_fd;
	//char	*symbol;
	char	**args;

	args = minishell->tokens;
	//in_fd = STDIN_FILENO;
	/* while (*(args))
	{
		num_tokens = count_tokens(args);
		print_command((args), num_tokens);
		printf("n_tokens: %d\n", num_tokens);
		symbol = get_next_redirection(args);
		if (symbol)
		{
			printf("next redirection: %s\n", symbol);
			redirect(args, num_tokens, &in_fd, minishell);
		}
		else
		{
			// grep h
			printf("no redirection\n");
			// execve(grep h)
			status = exe_cmd(minishell, args, num_tokens);
		}
		if (num_tokens == 1 && status == EXIT)
			return (EXIT);
		args = get_next_cmd(args);
		printf("next command: %s\n", *(args));
	} */
	//redirect_2(args);
	exe_cmd(args, NULL, count_tokens(args), NULL);
	return (NO_EXIT);
}
