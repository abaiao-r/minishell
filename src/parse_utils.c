/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:56:16 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/16 17:24:39 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_dollar_data
{
	int start;
	int end;
	char *find_var;
	char *replacement;
	size_t input_len;
	size_t replacement_len;
	int flag_double_quotes;
	int flag_single_quotes;
} t_dollar_data;

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


char *parse_dollar(char *input, t_env **environment)
{
	size_t i;
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
        if (input[i] == '$')
        {
            dollar_data->start = i;
            i++;
            while (i < dollar_data->input_len && input[i] != ' ' && input[i] != '$'
                   && input[i] != '\"' && input[i] != '\'')
                i++;
            dollar_data->end = i;
            dollar_data->find_var = ft_strndup(&input[dollar_data->start + 1], dollar_data->end - dollar_data->start - 1);
            dollar_data->replacement = search_and_replace_var(environment, dollar_data->find_var,
                                                              dollar_data->flag_single_quotes);
            if (dollar_data->replacement != NULL)
            {
                dollar_data->replacement_len = ft_strlen(dollar_data->replacement);
                size_t new_input_len = dollar_data->input_len + dollar_data->replacement_len - (dollar_data->end - dollar_data->start - 1);
                char *new_input = malloc(new_input_len + 1);
                ft_memcpy(new_input, input, dollar_data->start);
                ft_memcpy(new_input + dollar_data->start, dollar_data->replacement, dollar_data->replacement_len);
                ft_memcpy(new_input + dollar_data->start + dollar_data->replacement_len, &input[dollar_data->end],
                          dollar_data->input_len - dollar_data->end + 1);
                free(input);
                input = new_input;
                dollar_data->input_len = new_input_len;
                i = dollar_data->start + dollar_data->replacement_len;
            }
            free(dollar_data->find_var);
            free(dollar_data->replacement);
        }
        else
            i++;
    }
	free(dollar_data);
	return (input);
}
