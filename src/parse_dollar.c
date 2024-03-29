/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:56:16 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/21 00:08:30 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Replaces a portion of the input string with the given
replacement string. */
static void	replace_input(char **input, t_dollar_data *dollar_data)
{
	size_t	new_input_len;
	char	*new_input;

	dollar_data->replacement_len = ft_strlen(dollar_data->replacement);
	new_input_len = dollar_data->input_len + dollar_data->replacement_len
		- (dollar_data->end - dollar_data->start - 1);
	new_input = ft_calloc(new_input_len + 1, sizeof(char));
	ft_memcpy(new_input, *input, dollar_data->start);
	ft_memcpy(new_input + dollar_data->start, dollar_data->replacement,
		dollar_data->replacement_len);
	ft_memcpy(new_input + dollar_data->start + dollar_data->replacement_len,
		&(*input)[dollar_data->end],
		dollar_data->input_len - dollar_data->end + 1);
	free(*input);
	*input = new_input;
	dollar_data->input_len = new_input_len;
}

/* Searches for a variable in the environment list and returns
its value if found. If flag_single_quotes is 0 and the variable
is found, the value is duplicated and returned. */
static char	*search_and_replace_var(t_env **env_list, char *find_var,
		int flag_single_quotes)
{
	t_env	*current_node;
	char	*var_value;

	current_node = *env_list;
	while (current_node != NULL)
	{
		if ((ft_strcmp(current_node->var_name, find_var) == 0)
			&& flag_single_quotes == 0)
		{
			var_value = ft_strndup((const char *)current_node->var_value,
					ft_strlen(current_node->var_value));
			return (var_value);
		}
		current_node = current_node->next;
	}
	if (flag_single_quotes == 0)
	{
		var_value = ft_strndup((const char *) "", 0);
		return (var_value);
	}
	return (NULL);
}

/* Replaces a dollar variable in the input string with its corresponding
value from the environment. */
static void	replace_dollar_var(char **input, t_env **environment,
		t_dollar_data *dollar_data, size_t *i)
{
	size_t	flag;

	dollar_data->start = *i;
	(*i)++;
	flag = *i;
	while (*i < dollar_data->input_len && (ft_isalnum((*input)[*i])
		|| (*input)[*i] == '_' ))
		(*i)++;
	if (ft_isdigit((*input)[flag]))
		dollar_data->end = flag + 1;
	else
		dollar_data->end = *i;
	dollar_data->find_var = ft_strndup(&(*input)[dollar_data->start + 1],
			dollar_data->end - dollar_data->start - 1);
	dollar_data->replacement = search_and_replace_var(environment,
			dollar_data->find_var,
			dollar_data->flag_single_quotes);
	if (dollar_data->replacement != NULL)
	{
		replace_input(input, dollar_data);
		*i = dollar_data->start + dollar_data->replacement_len;
	}
	free(dollar_data->find_var);
	free(dollar_data->replacement);
}

/* Updates the flag_single_quotes and flag_double_quotes based on the
current character. */
static void	update_quote_flags(char current_char, int *flag_single_quotes,
		int *flag_double_quotes)
{
	if (current_char == '\'' && *flag_double_quotes == 0)
	{
		if (*flag_single_quotes == 0)
			*flag_single_quotes = 1;
		else
			*flag_single_quotes = 0;
	}
	else if (current_char == '\"' && *flag_single_quotes == 0)
	{
		if (*flag_double_quotes == 0)
			*flag_double_quotes = 1;
		else
			*flag_double_quotes = 0;
	}
}

/* Parses the input string and replaces dollar variables with
their values from the environment. Handles single and double 
quotes to determine whether variable replacement should occur. */
char	*parse_dollar(char *input, t_env **environment)
{
	size_t			i;
	t_dollar_data	*dollar_data;

	i = 0;
	dollar_data = malloc(sizeof(t_dollar_data));
	dollar_data->input_len = ft_strlen(input);
	dollar_data->flag_single_quotes = 0;
	dollar_data->flag_double_quotes = 0;
	while (i < dollar_data->input_len)
	{
		if (input[i] == '\'' || input[i] == '\"')
			update_quote_flags(input[i], &(dollar_data->flag_single_quotes),
				&(dollar_data->flag_double_quotes));
		if (input[i] == '$' && input[i + 1] != '?' && input[i + 1] != '\0'
			&& !ft_isspace(input[i + 1]) && input[i + 1] != '\''
			&& input[i + 1] != '\"')
			replace_dollar_var(&input, environment, dollar_data, &i);
		else
			i++;
	}
	free(dollar_data);
	return (input);
}
