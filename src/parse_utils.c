/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:56:16 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/16 15:08:46 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	return (NULL);
}

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

char	*parse_dollar(char *input, t_env **environment)
{
	size_t i;
	int start;
	int end;
	char *find_var;
	char *replacement;
	size_t input_len;
	size_t replacement_len;
	int flag_double_quotes;
	int flag_single_quotes;

	i = 0;
	input_len = ft_strlen(input);
	flag_single_quotes = 0;
	flag_double_quotes = 0;
	while (i < input_len)
	{
		if (input[i] == '\'' || input[i] == '\"')
			update_quote_flags(input[i], &flag_single_quotes,
					&flag_double_quotes);
		if (input[i] == '$')
		{
			start = i;
			i++;
			while (i < input_len && input[i] != ' ' && input[i] != '$'
				&& input[i] != '\"' && input[i] != '\'')
				i++;
			end = i;
			find_var = ft_strndup(&input[start + 1], end - start - 1);
			replacement = search_and_replace_var(environment, find_var,
					flag_single_quotes);
			if (replacement != NULL)
			{
				replacement_len = ft_strlen(replacement);
				size_t new_input_len = input_len + replacement_len - (end
						- start - 1);
				char *new_input = malloc(new_input_len + 1);
				ft_memcpy(new_input, input, start);
				ft_memcpy(new_input + start, replacement, replacement_len);
				ft_memcpy(new_input + start + replacement_len, &input[end],
						input_len - end + 1);
				free(input);
				input = new_input;
				input_len = new_input_len;

				i = start + replacement_len;
			}
			free(find_var);
			free(replacement);
		}
		else
			i++;
	}
	return (input);
}