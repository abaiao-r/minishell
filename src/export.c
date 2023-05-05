/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:58:38 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/05 21:47:51 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	export_error(char *input)
{
	printf("export: not an identifier: %s\n", input);
	return (NO_EXIT);
}

void	print_export(t_env **head)
{
	t_env	*node;
	t_env	*sorted_head;

	sorted_head = sort_alphabet_env_list(head);
	node = sorted_head;
	while (node != NULL)
	{
		printf("declare -x %s=\"%s\"\n", node->var_name, node->var_value);
		node = node->next;
	}
}

int	show_export(t_env **environment)
{
	print_export(environment);
	return (NO_EXIT);
}

int	update_env_name(t_env *env_list, char *find_var, char *new_value)
{
	t_env	*current_node;

	current_node = env_list;
	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->var_name, find_var) == 0)
		{
			current_node->var_value = new_value;
			return (1);
		}
		current_node = current_node->next;
	}
	return (0);
}

int	export(char **input, int num_tokens, t_env **environment)
{
	int	i;
	char *equal_sign;

	i = 1;
	if (num_tokens == 1)
		return (show_export(environment));
	if ((!ft_isalpha(input[1][0]) && !(input[1][0] == '_')))
	{
		printf("export: `%s': not a valid identifier \n", input[i]);
		return ;
	}
	if (!ft_strchr(input[i], '='))
		return ;
	char *equal_sign = strchr(input, '=');
	find_var = 
	new_value = 
	update_env_name(environment, find_var, new_value);
	
	/* if (ft_strchr(input[1], '='))
		ft_setenv(input[1], environment); */
	//ft_putenv(input, env);
	return (NO_EXIT);
}
