/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:07:42 by quackson          #+#    #+#             */
/*   Updated: 2023/06/24 18:33:19 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* save_fds: saves the file descriptors. */
void	save_fds(t_minishell *minishell)
{
	minishell->in = dup(STDIN_FILENO);
	minishell->out = dup(STDOUT_FILENO);
}

/* reset_fds: assigns the file descriptors to the standard input and output. */
void	reset_fds(t_minishell *minishell)
{
	dup2(minishell->in, STDIN_FILENO);
	dup2(minishell->out, STDOUT_FILENO);
	close(minishell->in);
	close(minishell->out);
}

/* exe_builtin: saves the file descriptors, handles the redirections. 
If does not handle redirections successfully, it resets the file descriptors,
frees the tokens and returns 0. If the command is a builtin, it
executes it. */
int	exe_builtin(char **tokens, t_minishell *minishell)
{
	save_fds(minishell);
	if (!handle_redirections(minishell->input, minishell))
	{
		reset_fds(minishell);
		free_parsed(tokens);
		minishell->exit_status = 1;
		return (0);
	}
	exe_cmd(tokens, count_tokens_str(tokens), minishell);
	return (1);
}

/* exe_command_no_pipes: initializes the tokens by calling
get_command_without_redirects. 
If the tokens are NULL, it exits the program. If the first token is NULL,
it saves the file descriptors, handles the redirections. If does not handle
redirections successfully, it resets the file descriptors, frees the tokens
and returns 0.
If the command is a builtin, it executes it. If the command is not a builtin,
it frees the tokens, calls redirect_3 and returns. */
void	exe_command_no_pipes(int num_commands, t_minishell *minishell)
{
	char	**tokens;

	tokens = get_command_without_redirects(minishell->input);
	if (!tokens)
		ft_exit(minishell, (char *[]){"exit", NULL}, 1);
	if (!tokens[0])
	{
		save_fds(minishell);
		if (!handle_redirections(minishell->input, minishell))
			minishell->exit_status = 1;
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

/* exe_commands: if there is more than one command, it calls redirect_3.
If there is only one command, it calls exe_command_no_pipes. */
int	exe_commands(t_minishell *minishell)
{
	int	num_commands;

	g_minishell.in_command = 1;
	num_commands = count_commands_lst(minishell->input);
	if (num_commands > 1)
		redirect_3(minishell->input, num_commands, minishell);
	if (num_commands == 1)
		exe_command_no_pipes(num_commands, minishell);
	return (NO_EXIT);
}
