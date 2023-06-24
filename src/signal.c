/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:34:29 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/24 19:28:15 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* sig_handler: handles the SIGINT and SIGQUIT signals.
SIGINT: if the minishell is not in a command, it prints a new line and
replaces the line with an empty string. If the minishell is in a command,
it prints a new line and replaces the line with an empty string. It also
redisplay the prompt.
SIGQUIT: if the minishell is in a command, it prints a new line and
replaces the line with an empty string. */
void	sig_handler(int signum)
{
	if (signum == SIGINT || (signum == SIGQUIT && g_minishell.in_command))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_minishell.in_command)
			rl_redisplay();
		g_minishell.minishell->exit_status = 130;
	}
}
