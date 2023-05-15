/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:58:38 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/12 17:15:54 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export(char **input, int num_tokens, t_env **environment)
{
	char	*find_var;
	char	*new_value;
	int		i;
	int		flag_equal;

	if (num_tokens == 1)
		return (show_export(environment));
	i = 1;
	while (input[i])
	{
		if ((!ft_isalpha(input[i][0]) && !(input[i][0] == '_')))
		{
			printf("bash: export: `%s': not a valid identifier\n", input[i]);
			i++;
			continue ;
		}
		flag_equal = parse_input_export(input[i], &find_var, &new_value);
		if (!update_env_name(environment, find_var, new_value, flag_equal))
			create_env_node(input[i], 100, environment);
		free(find_var);
		i++;
	}
	return (NO_EXIT);
}

/* int	export(char **input, int num_tokens, t_env **environment)
{
	int		i;
	char	*equal_sign;
	char	*find_var;
	char	*new_value;
	size_t	find_var_len;

	if (num_tokens == 1)
		return (show_export(environment));
	i = 1;
	while (input[i])
	{
		if ((!ft_isalpha(input[1][0]) && !(input[1][0] == '_')))
		{
			printf("bash: export: `%s': not a valid identifier\n", input[i]);
			return (NO_EXIT);
		}
		equal_sign = ft_strchr(input[i], '=');
		if (equal_sign)
			find_var_len = equal_sign - input[i];
		else
			find_var_len = ft_strlen(input[i]);
		find_var = malloc(find_var_len + 1);
		ft_strncpy(find_var, input[i], find_var_len);
		find_var[find_var_len] = '\0';
		new_value = equal_sign + 1;
		if (!update_env_name(environment, find_var, new_value))
			create_env_node(input[i], 100, environment);
		free(find_var);
		i++;
	}
	return (NO_EXIT);
} */
