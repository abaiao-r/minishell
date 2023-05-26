/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote_parsed_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:42:39 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/26 15:02:30 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* The function show_special_str_error prints a syntax error message 
with a specific format based on the input string, and it returns 0. */
static int	show_special_str_error(char *str)
{
	printf("bash: syntax error near unexpected token \'%s\'\n", str);
	return (0);
}

/* The function is_quote_parsed_valid checks if the given input array
contains valid combinations of special characters and returns 1 if it
is valid. If an invalid combination is found, it calls show_special_str_error
with the corresponding input element and returns 0. */
int	is_quote_parsed_valid(t_input *input)
{
	t_input *current = input;

	while (current)
	{
		if ((ft_strcmp(current->input, ">") == 0 || ft_strcmp(current->input, ">>") == 0
				|| ft_strcmp(current->input, "<") == 0 || ft_strcmp(current->input,
					"<<") == 0 || ft_strcmp(current->input, "|") == 0) && current->within_quotes == 0 && current->next->input == NULL)
			return (show_special_str_error(current->input));
		if (ft_strcmp(current->input, "||") == 0 && current->within_quotes == 0)
			return (show_special_str_error(current->input));
		if ((((ft_strcmp(current->input, ">") == 0 || ft_strcmp(current->input, ">>") == 0
				|| ft_strcmp(current->input, "<") == 0 || ft_strcmp(current->input,
					"<<") == 0 || ft_strcmp(current->input, "|") == 0) && current->within_quotes == 0))
			&& (((ft_strcmp(current->next->input, ">") == 0 || ft_strcmp(current->next->input,
					">>") == 0 || ft_strcmp(current->next->input, "<") == 0
				|| ft_strcmp(current->next->input, "<<") == 0 || ft_strcmp(current->next->input,
					"|") == 0)) && current->next->within_quotes == 0))
			return (show_special_str_error(current->input));
		current = current->next;
	}
	return (1);
}
