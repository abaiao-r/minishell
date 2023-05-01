/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:37:02 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/01 00:04:51 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*print_prompt(void)
{
	char	*cwd;
	char	*username;
	char	prompt[1024];

	username = getenv("USER");
	cwd = getcwd(NULL, 0);
	ft_strlcpy(prompt, "\033[38;5;208m", 1024);
	ft_strlcat(prompt, username, 1024);
	ft_strlcat(prompt, "@minishell:", 1024);
	ft_strlcat(prompt, "\033[1;34m", 1024);
	ft_strlcat(prompt, cwd, 1024);
	ft_strlcat(prompt, "\033[0m", 1024);
	ft_strlcat(prompt, "$ ", 1024);
	free(cwd);
	return (readline(prompt));
}
