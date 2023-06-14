/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:02:14 by quackson          #+#    #+#             */
/*   Updated: 2023/06/14 13:07:03 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_input	*ft_lstlast_parser(t_input *lst)
{
	if (!lst)
	{
		return (0);
	}
	while (lst != NULL)
	{
		if (!lst->next)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_parser(t_input **lst, t_input *new)
{
	t_input	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast_parser(*lst);
			last->next = new;
		}
		else
		{
			*lst = new;
		}
	}
	return ;
}

t_input	*new_node(char *str)
{
	t_input	*node;

	node = (t_input *)malloc(sizeof(t_input));
	node->token = ft_strdup(str);
	node->next = NULL;
	free(str);
	return (node);
}

void	add_node(t_input **head, char *str)
{
	t_input	*node;

	node = new_node(str);
	ft_lstadd_back_parser(head, node);
}

void	free_list(t_input *head)
{
	t_input	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}
