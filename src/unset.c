/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:29:19 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/18 18:59:41 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	delete_env_name(t_env **env_list, char *input)
{
	t_env	*current_node;
	t_env	*prev_node;

	current_node = *env_list;
	prev_node = NULL;
	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->var_name, input) == 0)
		{
			if (prev_node == NULL)
				*env_list = current_node->next;
			else
				prev_node->next = current_node->next;
			free(current_node->var_name);
			free(current_node->var_value);
			free(current_node);
			return (1);
		}
		prev_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

int	ft_unset(int num_tokens, t_minishell **minishell)
{
	int	i;

	if (num_tokens == 1)
	{
		(*minishell)->exit_status = 0;
		return (NO_EXIT);
	}
	i = 1;
	while ((*minishell)->tokens[i])
	{
		delete_env_name(&(*minishell)->environment, (*minishell)->tokens[i]);
		i++;
	}
	(*minishell)->exit_status = 0;
	return (NO_EXIT);
}
