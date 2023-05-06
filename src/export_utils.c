/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:49:51 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/06 18:51:36 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_env_name(t_env **env_list, char *find_var, char *new_value)
{
	t_env	*current_node;

	current_node = *env_list;
	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->var_name, find_var) == 0)
		{
			free(current_node->var_value);
			current_node->var_value = ft_strndup((const char *)new_value,
					ft_strlen(new_value));
			return (1);
		}
		current_node = current_node->next;
	}
	return (0);
}

void	parse_input_export(char *input, char **find_var, char **new_value)
{
	char	*equal_sign;
	size_t	find_var_len;

	equal_sign = ft_strchr(input, '=');
	if (equal_sign)
		find_var_len = equal_sign - input;
	else
		find_var_len = ft_strlen(input);
	*find_var = malloc(find_var_len + 1);
	ft_strncpy(*find_var, input, find_var_len);
	(*find_var)[find_var_len] = '\0';
	*new_value = equal_sign + 1;
}

t_env	*sort_alphabet_env_list(t_env **head)
{
	t_env	*curr;
	int		swapped;

	swapped = 1;
	if (!head || !(*head)->next)
		return (*head);
	while (swapped)
	{
		swapped = 0;
		curr = *head;
		while (curr->next)
		{
			if (ft_strcmp(curr->var_name, curr->next->var_name) > 0)
			{
				swap_env_nodes(curr);
				swapped = 1;
			}
			curr = curr->next;
		}
	}
	return (*head);
}

void	print_export(t_env **head)
{
	t_env	*node;
	t_env	*sorted_head;

	sorted_head = sort_alphabet_env_list(head);
	node = sorted_head;
	while (node != NULL)
	{
		if (node->var_value)
			printf("declare -x %s=\"%s\"\n", node->var_name, node->var_value);
		else
			printf("declare -x %s\n", node->var_name);
		node = node->next;
	}
}

int	show_export(t_env **environment)
{
	print_export(environment);
	return (NO_EXIT);
}
