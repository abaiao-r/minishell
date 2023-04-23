/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:37:02 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/23 21:43:47 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*print_prompt(void)
{
	char	*cwd;
	char	*username;
	char	*input;

	username = getenv("USER");
	cwd = getcwd(NULL, 0);
	//printf("%s@minishell:%s", username, cwd);
	printf("\033[38;5;208m%s@minishell:", username);  // bright green username
    printf("\033[1;34m%s", cwd);  // blue cwd
    printf("\033[0m");  // reset color
	input = readline("$ ");
	free(cwd);
	return (input);
}
