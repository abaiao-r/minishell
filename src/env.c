/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:32:23 by quackson          #+#    #+#             */
/*   Updated: 2023/04/24 00:35:54 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	show_env(void)
{
	char	**env;

	env = environ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (NO_EXIT);
}
