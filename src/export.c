/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:58:38 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/24 02:22:40 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void print_error(char *token)
{
	char *error_tmp;
	char *error;

	error_tmp = ft_strjoin("export: '", token);
	error = ft_strjoin(error_tmp, "': not a valid identifier\n");
	free(error_tmp);
	write(2, error, ft_strlen(error));
	free(error);
}

static void	process_export_tokens(t_minishell **minishell, int *flag, int *i)
{
	char	*find_var;
	char	*new_value;
	int		flag_equal;
	int j;
	int flag_continue;

	flag_continue = 0;
	(*i) = 1;
	while ((*minishell)->tokens[(*i)] && !is_redirection((*minishell)->tokens[(*i)]))
	{
		if (((ft_isalpha((*minishell)->tokens[(*i)][0]) == 0) && ((*minishell)->tokens[(*i)][0] != '_')) || ft_isdigit((*minishell)->tokens[(*i)][0]) == 1)
		{
			*flag = 1;
			print_error((*minishell)->tokens[(*i)]);
			(*i)++;
			continue ;
		}
		j = 1;
		while ((*minishell)->tokens[(*i)][j] && (*minishell)->tokens[(*i)][j] != '=')
		{
			if(ft_isalnum((*minishell)->tokens[(*i)][j]) == 0 && (*minishell)->tokens[(*i)][j] != '_')
			{
				*flag = 1;
				print_error((*minishell)->tokens[(*i)]);
				flag_continue = 1;
				break ;
			}
			j++;
		}	
		if (flag_continue == 1)
		{
			(*i)++;
			flag_continue = 0;
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
