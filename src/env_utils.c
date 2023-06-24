/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:36:35 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/24 18:13:35 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* *ft_lstlast_env: returns the last element of the list. If
the list is empty, the function returns NULL. */
t_env	*ft_lstlast_env(t_env *lst)
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

/* ft_lstadd_back_env: adds the element ’new’ at the end of the list. If ’lst’
is NULL, the function creates a new list with ’new’. */
void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast_env(*lst);
			last->next = new;
		}
		else
		{
			*lst = new;
		}
	}
	return ;
}

/*  print_env: prints the environment variables. If the variable has no value,
it is not printed. */
void	print_env(t_env **head)
{
	t_env	*node;

	node = *head;
	while (node != NULL)
	{
		if (node->var_value)
			printf("%s=%s\n", node->var_name, node->var_value);
		node = node->next;
	}
}

/* free_env_list: frees the environment variables list. */
void	free_env_list(t_env **head)
{
	t_env	**node;
	t_env	*next_node;

	node = head;
	while (*node != NULL)
	{
		next_node = (*node)->next;
		free((*node)->var_name);
		free((*node)->var_value);
		free(*node);
		*node = next_node;
	}
	*head = NULL;
}

/* swap_env_nodes: swaps the values of two nodes.
The nodes are swapped by reference, not by value.
The rank is not swapped.
The rank is used to sort the list.
The rank is not swapped because the rank of the nodes
does not change when the nodes are swapped. */
void	swap_env_nodes(t_env *curr)
{
	char	*temp;
	int		temp_rank;

	temp = curr->var_name;
	curr->var_name = curr->next->var_name;
	curr->next->var_name = temp;
	temp = curr->var_value;
	curr->var_value = curr->next->var_value;
	curr->next->var_value = temp;
	temp_rank = curr->rank;
	curr->rank = curr->next->rank;
	curr->next->rank = temp_rank;
}
