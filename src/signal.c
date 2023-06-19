/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:34:29 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/19 16:37:29 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
