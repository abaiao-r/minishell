/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:37:02 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/29 17:16:35 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*print_prompt(t_prompt **prompt)
{
	char	*cwd;
	char	*username;
	char	*prompt_pre;
	char	*prompt_mid;

	username = getenv("USER");
	cwd = getcwd(NULL, 0);
	prompt_pre = ft_strjoin(username, ":");
	prompt_mid = ft_strjoin(prompt_pre, cwd);
	(*prompt)->prompt_full = ft_strjoin(prompt_mid, "$ ");
	free(prompt_pre);
	free(prompt_mid);
	free(cwd);
	return (readline((*prompt)->prompt_full));
}
