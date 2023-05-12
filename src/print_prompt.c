/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:37:02 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/11 16:09:01 by abaiao-r         ###   ########.fr       */
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
	ft_strlcpy(prompt, "\033[38;5;208m", PROMPT_SIZE);
	ft_strlcat(prompt, username, PROMPT_SIZE);
	ft_strlcat(prompt, "@minishell:", PROMPT_SIZE);
	ft_strlcat(prompt, "\033[1;34m", PROMPT_SIZE);
	ft_strlcat(prompt, cwd, PROMPT_SIZE);
	ft_strlcat(prompt, "\033[0m$ ", PROMPT_SIZE);
	free(cwd);
	return (readline(prompt));
}
