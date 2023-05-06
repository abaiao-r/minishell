/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:29:19 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/06 20:08:09 by abaiao-r         ###   ########.fr       */
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

int	ft_unset(char **input, int num_tokens, t_env **environment)
{
	int	i;

	if (num_tokens == 1)
		return (NO_EXIT);
	i = 1;
	while (input[i])
	{
		delete_env_name(environment, input[i]);
		i++;
	}
	return (NO_EXIT);
}
