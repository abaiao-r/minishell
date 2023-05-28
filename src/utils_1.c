/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:09:22 by quackson          #+#    #+#             */
/*   Updated: 2023/05/28 19:55:47 by andrefranci      ###   ########.fr       */
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

void	free_token_list(t_input **head)
{
	t_input	**node;
	t_input	*next_node;

	node = head;
	while (*node != NULL)
	{
		next_node = (*node)->next;
		free((*node)->token);
		free(*node);
		*node = next_node;
	}
	*head = NULL;
}

char	**create_token_array_2d(t_input *input)
{
	t_input	*temp;
	int		i;
	int		count;
	char	**token_2d;

	temp = input;
	count = ft_lstsize(temp) + 1;
	token_2d = (char **)malloc(sizeof(char *) * count);
	i = 0;
	while (temp)
	{
		token_2d[i] = temp->token;
		i++;
		temp = temp->next;
	}
	token_2d[i] = NULL;
	return (token_2d);
}