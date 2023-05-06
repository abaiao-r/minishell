/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:36:35 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/05 17:20:06 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	print_env(t_env **head)
{
	t_env	*node;

	node = *head;
	while (node != NULL)
	{
		printf("%s=%s\n", node->var_name, node->var_value);
		node = node->next;
	}
}

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
