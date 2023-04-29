/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:58:38 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/28 22:09:05 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_error(char *input)
{
	printf("export: not an identifier: %s\n", input);
	return (NO_EXIT);
}

void	print_export(t_env *head)
{
	t_env	*node;

	node = head;
	while (node != NULL)
	{
		printf("declare -x %s=\"%s\"\n", node->var_name, node->var_value);
		node = node->next;
	}
}

int	show_export(char **env)
{
	t_env	*environment;

	environment = parse_env(env);
	print_export(environment);
	free_env_list(environment);
	return (NO_EXIT);
}

int	export(char **input, int num_tokens, char **env)
{
	int i;

	if (num_tokens == 1)
		return (show_export(env));
	if (num_tokens != 2 || input[1][0] == '_')
		return (NO_EXIT);
	if (input[1][0] == '_')
			return (NO_EXIT);
	if (!ft_isalpha(input[1][0]))
		return (export_error(input[1]));
	i = 0;
	while (input[1][i] && input[1][i] != '=')
	{
		if (!ft_isalnum(input[1][i]) && input[1][i] != '_')
			return (export_error(input[1]));
		i++;
	}
	if (ft_strchr(input[1], '='))
		printf("putenv success\n");
		//ft_putenv(input, env);
	return (NO_EXIT);
}
