/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:09:22 by quackson          #+#    #+#             */
/*   Updated: 2023/06/14 00:59:15 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parsed(char **parsed)
{
	int	i;

	i = 0;
	if (!parsed)
		return ;
	while (parsed[i])
	{
		free(parsed[i]);
		i++;
	}
	free(parsed[i]);
	free(parsed);
}

void	free_token_list(t_input **head)
{
	t_input	*node;
	t_input	*next_node;

	node = *head;
	while (node != NULL)
	{
		next_node = (node)->next;
		free((node)->token);
		free(node);
		node = next_node;
	}
}

int	ft_token_lstsize(t_input *lst)
{
	int		i;
	t_input	*temp;

	temp = lst;
	i = 0;
	if (!temp)
		return (0);
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

char	**create_token_array_2d(t_input *input, t_minishell *minishell)
{
	t_input	*temp;
	int		i;
	char	**token_2d;

	(void) minishell;
	if (!input)
		return (NULL);
	token_2d = (char **) malloc(sizeof(char *) * (ft_token_lstsize(input) + 1));
	if (!token_2d)
		return (NULL);
	temp = input;
	i = 0;
	while (temp)
	{
		token_2d[i++] = ft_strdup(temp->token);
		if (!token_2d[i - 1])
			return (NULL);
		temp = temp->next;
	}
	token_2d[i] = NULL;
	return (token_2d);
}
