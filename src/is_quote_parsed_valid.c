/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote_parsed_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:42:39 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/28 18:32:48 by andrefranci      ###   ########.fr       */
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
static int	is_special_character(const char *input)
{
	return (ft_strcmp(input, ">") == 0 || ft_strcmp(input, ">>") == 0 || \
			ft_strcmp(input, "<") == 0 || ft_strcmp(input, "<<") == 0 || \
			ft_strcmp(input, "|") == 0);
}

static int	is_end_of_input(const t_input *current)
{
	return (current->next == NULL);
}

static int	is_within_quotes(const t_input *current)
{
	return (current->within_quotes == 0);
}

int	is_pipe_or_redirection_valid(t_input *input)
{
	t_input	*current;

	current = input;
	while (current)
	{
		if (is_special_character(current->token) && is_within_quotes(current)
			&& is_end_of_input(current))
			return (show_special_str_error(current->token));
		if (ft_strcmp(current->token, "||") == 0 && is_within_quotes(current))
			return (show_special_str_error(current->token));
		if (current->next && is_special_character(current->token)
			&& is_within_quotes(current) && \
			is_special_character(current->next->token)
			&& is_within_quotes(current->next))
			return (show_special_str_error(current->token));
		current = current->next;
	}
	return (1);
}
