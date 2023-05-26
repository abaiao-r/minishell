/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:09:22 by quackson          #+#    #+#             */
/*   Updated: 2023/05/26 14:47:26 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parsed(char **parsed)
{
	int	i;

	i = 0;
	if (!parsed || !parsed[i])
		return ;
	while (parsed[i])
	{
		free(parsed[i]);
		i++;
	}
	free(parsed);
}

void	free_input_list(t_input **head)
{
	t_input	**node;
	t_input	*next_node;

	node = head;
	while (*node != NULL)
	{
		next_node = (*node)->next;
		free((*node)->input);
		free(*node);
		*node = next_node;
	}
	*head = NULL;
}
