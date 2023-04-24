/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:32:23 by quackson          #+#    #+#             */
/*   Updated: 2023/04/24 19:33:40 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	show_env(void)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (NO_EXIT);
}
