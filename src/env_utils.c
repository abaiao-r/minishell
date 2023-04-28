/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:36:35 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/28 20:54:22 by abaiao-r         ###   ########.fr       */
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

void	print_env(t_env *head)
{
	t_env	*node;

	node = head;
	while (node != NULL)
	{
		printf("%s=%s\n", node->var_name, node->var_value);
		node = node->next;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*node;
	t_env	*next_node;

	node = head;
	while (node != NULL)
	{
		next_node = node->next;
		free(node->var_name);
		free(node);
		node = next_node;
	}
}
