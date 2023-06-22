/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:49:34 by quackson          #+#    #+#             */
/*   Updated: 2023/06/22 23:06:52 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void	redirect_child(t_input *input, int num_commands, t_minishell *minishell,
t_redirect_info redirect_info)
{
	char	**cmds;
	int		num_tokens;

	cmds = get_command_without_redirects(input);
	minishell->cmd_without_redirects = cmds;
	if (redirect_info.i != 0)
	{
		dup2(redirect_info.in_fd, STDIN_FILENO);
		close(redirect_info.in_fd);
	}
	if (redirect_info.i < num_commands - 1)
	{
		dup2(redirect_info.pipe_fd_1, STDOUT_FILENO);
		close(redirect_info.pipe_fd_0);
		close(redirect_info.pipe_fd_1);
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

void	wait_for_children(int num_commands, t_redirect_info redirect_info,
t_minishell *minishell)
{
	int	status;

	while (num_commands > 0)
	{
		wait(&status);
		if (redirect_info.pid != -1 && WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		num_commands--;
	}
}

void	redirect_parent(int num_commands, t_redirect_info *redirect_info)
{
	if (redirect_info->i > 0)
		close(redirect_info->in_fd);
	if (redirect_info->i < num_commands - 1)
	{
		close(redirect_info->pipe_fd_1);
		redirect_info->in_fd = redirect_info->pipe_fd_0;
	}
}

void	print_error(char *str)
{
	perror(str);
	exit(1);
}

// TODO set follow-fork-mode child
void	redirect_3(t_input *input, int num_commands, t_minishell *minishell)
{
	int				pipe_fd[2];
	int				i;
	t_redirect_info	redirect_info;

	i = 0;
	redirect_info.in_fd = 0;
	while (i < num_commands)
	{
		if (i < num_commands - 1 && (pipe(pipe_fd) < 0))
			print_error("pipe failed");
		redirect_info.i = i;
		redirect_info.pipe_fd_0 = pipe_fd[0];
		redirect_info.pipe_fd_1 = pipe_fd[1];
		redirect_info.pid = fork();
		if (redirect_info.pid < 0)
			print_error("fork failed");
		else if (redirect_info.pid == 0)
			redirect_child(input, num_commands, minishell, redirect_info);
		else
			redirect_parent(num_commands, &redirect_info);
		input = get_next_cmd(input);
		i++;
	}
	wait_for_children(num_commands, redirect_info, minishell);
}
