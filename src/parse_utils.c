/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:56:16 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/15 19:54:26 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*search_and_replace_var(t_env **env_list, char *find_var)
{
	t_env	*current_node;
	char	*var_value;

	current_node = *env_list;
	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->var_name, find_var) == 0)
		{
			var_value = ft_strndup((const char *)current_node->var_value,
					ft_strlen(current_node->var_value));
			return (var_value);
		}
		current_node = current_node->next;
	}
	return (NULL);
}

char	*parse_dollar(char *input, t_env **environment)
{
	size_t	i;
	int		start;
	int		end;
	char	*find_var;
	char	*replacement;
	size_t	input_len;
	size_t	replacement_len;

	i = 0;
	input_len = ft_strlen(input);
	while (i < input_len)
	{
		if (input[i] == '$')
		{
			start = i;
			i++;
			while (i < input_len && input[i] != ' ' && input[i] != '$')
				i++;
			end = i;
			find_var = ft_strndup(&input[start + 1], end - start - 1);
			replacement = search_and_replace_var(environment, find_var);
			if (replacement != NULL)
			{
				replacement_len = ft_strlen(replacement);
				ft_memmove(&input[start], replacement, replacement_len);
				ft_memmove(&input[start + replacement_len], &input[end], input_len
						- end + 1);
				input_len += replacement_len - (end - start - 1);
				i = start + replacement_len;
			}
			free(find_var);
			free(replacement);
		}
		else
			i++;
	}
    return(input);
}

/* void	*parse_dollar(char *input, t_env **enviroment)
{
	int		i;
	int		start;
	int		end;
	char	*find_var;
    char *replace;

	start = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			start = i;
			while (input[i] != '\0' && input[i] != ' ' && input[i] != '$')
				i++;
			end = i;
			find_var = ft_strndup((const char *)&input[start + 1], end - start
					- 1);
			input[start] = search_and_replace_var(enviroment, find_var);
			if(!find_var)
            i = start;
        }
        i++;
    }
}*/

