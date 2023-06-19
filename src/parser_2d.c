/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:09:22 by quackson          #+#    #+#             */
/*   Updated: 2023/06/19 18:23:48 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function: ft_token_lstsize
Calculates the size of a linked list of tokens.
lst: The head of the token list.
returns: The size of the token list. */
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

/* Function: create_token_array_2d
Creates a 2D array of tokens from a linked list of input tokens.
input: The head of the token list.
minishell: The minishell instance (unused in the function).
returns: A 2D array of tokens, or NULL if memory allocation fails. */
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
