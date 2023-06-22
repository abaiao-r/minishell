/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:07:42 by quackson          #+#    #+#             */
/*   Updated: 2023/06/23 00:02:40 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	save_fds(t_minishell *minishell)
{
	minishell->in = dup(STDIN_FILENO);
	minishell->out = dup(STDOUT_FILENO);
}

void	reset_fds(t_minishell *minishell)
{
	dup2(minishell->in, STDIN_FILENO);
	dup2(minishell->out, STDOUT_FILENO);
	close(minishell->in);
	close(minishell->out);
}

int	exe_builtin(char **tokens, t_minishell *minishell)
{
	save_fds(minishell);
	if (!handle_redirections(minishell->input, minishell))
	{
		reset_fds(minishell);
		free_parsed(tokens);
		return (0);
	}
	exe_cmd(tokens, count_tokens_str(tokens), minishell);
	return (1);
}

void	exe_command_no_pipes(int num_commands, t_minishell *minishell)
{
	char	**tokens;

	tokens = get_command_without_redirects(minishell->input);
	if (!tokens)
		ft_exit(minishell, (char *[]){"exit", NULL}, 1);
	if (!tokens[0])
	{
		save_fds(minishell);
		handle_redirections(minishell->input, minishell);
	}
	else if (is_builtin(tokens))
	{
		if (!exe_builtin(tokens, minishell))
			return ;
	}
	else
	{
		free_parsed(tokens);
		redirect_3(minishell->input, num_commands, minishell);
		return ;
	}
	reset_fds(minishell);
	free_parsed(tokens);
}

int	exe_commands(t_minishell *minishell)
{
	int		num_commands;

	g_minishell.in_command = 1;
	num_commands = count_commands_lst(minishell->input);
	if (num_commands > 1)
		redirect_3(minishell->input, num_commands, minishell);
	if (num_commands == 1)
		exe_command_no_pipes(num_commands, minishell);
	return (NO_EXIT);
}
