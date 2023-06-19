/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:02:14 by quackson          #+#    #+#             */
/*   Updated: 2023/06/19 18:28:04 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function: ft_lstlast_parser
Returns the last node of a linked list.
lst: The head of the linked list.
returns: The last node of the linked list. */
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

/* Function: ft_lstadd_back_parser
Adds a new node at the end of a linked list.
lst: A pointer to the head of the linked list.
new: The new node to be added. */
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

/* Function: new_node
Creates a new node for the linked list.
str: The string to be assigned to the new node.
returns: The newly created node. */
t_input	*new_node(char *str)
{
	t_input	*node;

	node = (t_input *)malloc(sizeof(t_input));
	node->token = ft_strdup(str);
	node->next = NULL;
	free(str);
	return (node);
}

/* Function: add_node
Adds a new node with the specified string to the end of the linked list.
head: A pointer to the head of the linked list.
str: The string to be assigned to the new node. */
void	add_node(t_input **head, char *str)
{
	t_input	*node;

	node = new_node(str);
	ft_lstadd_back_parser(head, node);
}

/* Function: free_list
Frees the memory allocated for a linked list.
head: The head of the linked list to be freed. */
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
