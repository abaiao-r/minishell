/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:09:22 by quackson          #+#    #+#             */
/*   Updated: 2023/05/17 23:24:07 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parsed(char **parsed)
{
	int	i;

	i = 0;
	if (!parsed || parsed[i])
		return ;
	while (parsed[i])
	{
		free(parsed[i]);
		i++;
	}
	free(parsed[i]);
	free(parsed);
}
