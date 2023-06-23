/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:58:38 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/19 15:25:39 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process_export_tokens(t_minishell **minishell, int *flag, int *i)
{
	char	*find_var;
	char	*new_value;
	int		flag_equal;

	(*i) = 1;
	while ((*minishell)->tokens[(*i)] && !is_redirection((*minishell)->tokens[(*i)]))
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
