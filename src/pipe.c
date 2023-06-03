/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:58:20 by quackson          #+#    #+#             */
/*   Updated: 2023/06/03 23:00:08 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

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

char	**get_next_cmd(char **args)
{
	while (*args)
	{
		if (!ft_strncmp(*args, "|", 1))
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

int	count_commands(char **args)
{
	int	n_commands;

	n_commands = 0;
	while (*args)
	{
		if (!strncmp(*args, "|", 1))
			n_commands++;
		args++;
	}
	return (n_commands + 1);
}
/* 
void redirect_2(char** commands, t_minishell *minishell) {
	static int pipe_fd[2];
	static int in_fd = 0; // Input file descriptor for the first command
	static int i = 0;
	//int	has_pipe;


	while (*commands)
	{
		//has_pipe = cmd_has_pipe(commands);
		// Create pipe for inter-process communication
		if (!*(commands + 1))
		{
			if (pipe(pipe_fd) < 0)
			{
				perror("pipe failed");
				exit(1);
			}
		}
		printf("%s %d\n", *commands, count_tokens(commands));
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
			if (!*(commands + 1))
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			exe_cmd(NULL, count_tokens(commands), &(minishell->environment));
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
			if (!*(commands + 1))
			{
				close(pipe_fd[1]);
				in_fd = pipe_fd[0];
			}
			wait(NULL);
		}
		i++;
		commands = get_next_cmd(commands);
		printf("next command: %s\n", *(commands));
	}
}
 */

int	count_arguments(char **args)
{
	int		num_args;
	int		redirect_flag;

	num_args = 0;
	redirect_flag = 0;
	while (*args && ft_strncmp(*args, "|", 1))
	{
		if (redirect_flag)
			redirect_flag = 0;
		else if (is_redirection(*args))
			redirect_flag = 1;
		else
			num_args++;
		args++;
	}
	return (num_args);
}

char	**get_command_without_redirects(char **tokens)
{
	char	**command;
	int		num_args;
	int		redirect_flag;
	int		i;

	num_args = count_arguments(tokens);
	command = malloc(sizeof(char *) * (num_args + 1));
	if (!command)
		return (NULL);
	num_args = 0;
	redirect_flag = 0;
	i = 0;
	while (*tokens && ft_strncmp(*tokens, "|", 1))
	{
		if (redirect_flag)
			redirect_flag = 0;
		else if (is_redirection(*tokens))
			redirect_flag = 1;
		else
		{
			command[i++] = *tokens;
			num_args++;
		}
		tokens++;
	}
	command[i] = NULL;
	return (command);
}

void	handle_redirections(char **tokens)
{
	char	*file;
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!ft_strncmp(tokens[i], "<", 1))
		{
			file = tokens[i + 1];
			redirect_input(file);
		}
		else if (!ft_strncmp(tokens[i], ">>", 2))
		{
			file = tokens[i + 1];

			redirect_output(file, 1);
		}
		else if (!ft_strncmp(tokens[i], ">", 1))
		{
			file = tokens[i + 1];
			redirect_output(file, 0);
		}
		i++;
	}
}

void redirect_3(char** commands, int num_commands, t_minishell *minishell)
{
	int pipe_fd[2];  // Pipe file descriptors
	int in_fd = 0;   // Input file descriptor for the first command

	(void) minishell;
	//printf("num_commands: %d\n", num_commands);
	for (int i = 0; i < num_commands; i++) {
		// Create pipe for inter-process communication
		if (i < num_commands - 1) {
			if (pipe(pipe_fd) < 0) {
				perror("pipe failed");
				exit(1);
			}
		}

		
		//printf("n_args: %d\n", count_arguments(commands));
		char **cmds = get_command_without_redirects(commands);
		/* for (int j = 0; cmds[j]; j++)
			printf("cmd: %s\n", cmds[j]); */

			
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
			handle_redirections(commands);
			exe_cmd(cmds, count_arguments(cmds), minishell);
			exit(1);
		}
		else
		{
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
		commands = get_next_cmd(commands);
	}
	while (num_commands > 0) {
		wait(NULL);
		num_commands--;
	}
}

int	exe_commands(t_minishell *minishell)
{
	/* int		num_tokens;
	int		status;
	char	*symbol;
	char	**args;

	args = minishell->tokens;
	while (*(args))
	{
		num_tokens = count_tokens(args);
		print_command((args), num_tokens);
		//printf("n_tokens: %d\n", num_tokens);
		symbol = get_next_redirection(args);
		if (symbol && !ft_strncmp(symbol, "|", 1))
		{
			printf("next pipe: %s\n", symbol);
			redirect_2(args, minishell);
			//args = get_next_cmd(args);
		}
		else
		{
			// grep h
			//printf("no redirection\n");
			// execve(grep h)
			status = exe_cmd(minishell, num_tokens, &(minishell->environment));
		}
		if (num_tokens == 1 && status == EXIT)
			return (EXIT);
		args = get_next_cmd(args);
		//printf("next command: %s\n", *(args));
	} */
	//redirect_2(args);
	//exe_cmd(args, NULL, count_tokens(args), NULL);
	int		num_commands;
	
	num_commands = count_commands(minishell->tokens);
	redirect_3(minishell->tokens, num_commands, minishell);
	return (NO_EXIT);
}
