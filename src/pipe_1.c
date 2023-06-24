/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:49:34 by quackson          #+#    #+#             */
/*   Updated: 2023/06/24 19:14:38 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void	redirect_child_aux(char **cmds, t_minishell *minishell)
{
	int		num_tokens;

	num_tokens = count_tokens_str(cmds);
	if (is_builtin(cmds))
		exe_cmd(cmds, num_tokens, minishell);
	else
		exe_shell_cmd(cmds, num_tokens, &(minishell->environment));
}

/* redirect_child: redirects the input and output of the child process.
If the child process is not the first process, it redirects the input
to the pipe. If the child process is not the last process, it redirects
the output to the pipe. If the redirections are successful, it executes
the command. Otherwise, it frees the tokens and exits the program. */
void	redirect_child(t_input *input, int num_commands, t_minishell *minishell,
t_redirect_info redirect_info)
{
	char	**cmds;
	int		redirection_success;

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
	redirection_success = handle_redirections(input, minishell);
	if (redirection_success)
		redirect_child_aux(cmds, minishell);
	free_parsed(cmds);
	free_minishell(minishell);
	exit(!redirection_success);
}

/* wait_for_children: waits for the children to finish.
It waits for the number of commands times. If the child process
is the last process, it waits for the last process to finish
and sets the exit status to the exit status of the last process. */
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

/*  redirect_parent: redirects the input and output of the parent process.
If the child process is not the first process, it closes the input file
descriptor. If the child process is not the last process, it closes the
output file descriptor and sets the input file descriptor to the output
file descriptor of the pipe. */
static void	redirect_parent(int num_commands, t_redirect_info *redirect_info)
{
	if (redirect_info->i > 0)
		close(redirect_info->in_fd);
	if (redirect_info->i < num_commands - 1)
	{
		close(redirect_info->pipe_fd_1);
		redirect_info->in_fd = redirect_info->pipe_fd_0;
	}
}

/* redirect_3: redirects the input and output of the parent process.
It creates a pipe, forks the process and calls redirect_child in the child
process. In the parent process, it calls redirect_parent and gets the next
command. */
void	redirect(t_input *input, int num_commands, t_minishell *minishell)
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
