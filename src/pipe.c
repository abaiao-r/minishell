/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:49:34 by quackson          #+#    #+#             */
/*   Updated: 2023/06/22 21:43:11 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

t_input	*get_next_cmd(t_input *input)
{
	while (input)
	{
		if (!ft_strncmp(input->token, "|", 1) && !input->in_quotes)
			return (input->next);
		input = input->next;
	}
	return (input);
}

int	count_tokens_str(char **args)
{
	int		i;

	i = 0;
	while (*args)
	{
		args++;
		i++;
	}
	return (i);
}

int	count_arguments(t_input *input)
{
	int		num_args;
	int		redirect_flag;

	num_args = 0;
	redirect_flag = 0;
	while (input && !(!ft_strncmp(input->token, "|", 1) && !input->in_quotes))
	{
		if (redirect_flag)
			redirect_flag = 0;
		else if (is_redirection(input->token) && !input->in_quotes)
			redirect_flag = 1;
		else
			num_args++;
		input = input->next;
	}
	return (num_args);
}

void	redirect_child(t_input *input, int num_commands,
t_minishell *minishell, t_redirect_info *redirect_info)
{
	char	**cmds;
	int		num_tokens;

	cmds = get_command_without_redirects(input);
	minishell->cmd_without_redirects = cmds;
	if (redirect_info->i != 0)
	{
		dup2(redirect_info->in_fd, STDIN_FILENO);
		close(redirect_info->in_fd);
	}
	// Redirect output to the next command or file
	if (redirect_info->i < num_commands - 1)
	{
		dup2(redirect_info->pipe_fd_out, STDOUT_FILENO);
		close(redirect_info->pipe_fd_in);
		close(redirect_info->pipe_fd_out);
	}
	handle_redirections(input, minishell);
	num_tokens = count_tokens_str(cmds);
	if (is_builtin(cmds))
		exe_cmd(cmds, num_tokens, minishell);
	else
		exe_shell_cmd(cmds, num_tokens, &(minishell->environment));
	free_parsed(cmds);
	free_minishell(minishell);
	exit(EXIT_FAILURE);
}

// TODO set follow-fork-mode child
void	redirect_3(t_input *input, int num_commands, t_minishell *minishell)
{
	int pipe_fd[2];  // Pipe file descriptors
	int in_fd = 0;   // Input file descriptor for the first command
	char **cmds;
	int status;
	pid_t pid;

	cmds = NULL;
	(void) minishell;
	for (int i = 0; i < num_commands; i++)
	{
		if (i < num_commands - 1) {
			if (pipe(pipe_fd) < 0) {
				perror("pipe failed");
				exit(1);
			}
		}
		pid = fork();
		if (pid < 0) {
			perror("fork failed");
			exit(1);
		} else if (pid == 0)
		{
			// Redirect input from the previous command or file
			cmds = get_command_without_redirects(input);
			minishell->cmd_without_redirects = cmds;
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
			handle_redirections(input, minishell);
			int	num_tokens = count_tokens_str(cmds);
			if (is_builtin(cmds))
				exe_cmd(cmds, num_tokens, minishell);
			else
				exe_shell_cmd(cmds, num_tokens, &(minishell->environment));
			free_parsed(cmds);
			free_minishell(minishell);
			exit(EXIT_FAILURE);
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
		input = get_next_cmd(input);
	}
	while (num_commands > 0)
	{
		wait(&status);
		if(pid != -1 && WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		num_commands--;
	}
}
