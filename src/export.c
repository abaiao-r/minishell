/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:58:38 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/18 19:41:35 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process_export_tokens(t_minishell **minishell, int *flag, int *i)
{
	char	*find_var;
	char	*new_value;
	int		flag_equal;

	(*i) = 1;
	while ((*minishell)->tokens[(*i)])
	{
		if ((!ft_isalpha((*minishell)->tokens[(*i)][0])
			&& !((*minishell)->tokens[(*i)][0] == '_')))
		{
			*flag = 1;
			printf("bash: export: `%s': not a valid identifier\n",
				(*minishell)->tokens[(*i)]);
			(*i)++;
			continue ;
		}
		flag_equal = parse_input_export((*minishell)->tokens[(*i)], &find_var,
				&new_value);
		if (!update_env_name(&(*minishell)->environment, find_var, new_value,
				flag_equal))
			create_env_node((*minishell)->tokens[(*i)], 100,
				&(*minishell)->environment);
		free(find_var);
		(*i)++;
	}
}

int	export(int num_tokens, t_minishell **minishell)
{
	int	flag;
	int	i;

	flag = 0;
	if (num_tokens == 1)
	{
		(*minishell)->exit_status = 0;
		return (show_export(&(*minishell)->environment));
	}
	process_export_tokens(minishell, &flag, &i);
	if (flag == 1)
		(*minishell)->exit_status = 1;
	else
		(*minishell)->exit_status = 0;
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
