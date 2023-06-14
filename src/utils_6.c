/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:18:59 by quackson          #+#    #+#             */
/*   Updated: 2023/06/14 13:29:53 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char **tokens)
{
	if (!tokens || !tokens[0])
		return (0);
	if (ft_strcmp(tokens[0], "echo") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "cd") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "export") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "unset") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "env") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "exit") == 0)
		return (1);
	return (0);
}
