/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote_parsed_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:42:39 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/21 19:55:46 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* The function show_special_str_error prints a syntax error message 
with a specific format based on the input string, and it returns 0. */
static int	show_str_error(char *str)
{
	printf("bash: syntax error near unexpected token \'%s\'\n", str);
	return (0);
}

static int	is_special_char(const char *input)
{
	return (ft_strcmp(input, ">") == 0 || ft_strcmp(input, ">>") == 0
		|| ft_strcmp(input, "<") == 0 || ft_strcmp(input, "<<") == 0);
}

static int	is_end_input(const t_input *current)
{
	return (current->next == NULL);
}

static int	is_quotes(const t_input *current)
{
	return (current->in_quotes == 0);
}

/* The function is_quote_parsed_valid checks if the given input array
contains valid combinations of special characters and returns 1 if it
is valid. If an invalid combination is found, it calls show_str_error
with the corresponding input element and returns 0. */
int	is_pipe_or_redirection_valid(t_input *input)
{
	t_input	*current;

	current = input;
	if (ft_strcmp(current->token, "|") == 0 && current->in_quotes == 0)
		return (show_str_error(current->token));
	while (current)
	{
		if ((is_special_char(current->token) || ft_strcmp(current->token,
					"|") == 0) && is_quotes(current) && is_end_input(current))
			return (show_str_error(current->token));
		if (is_special_char(current->token) && is_quotes(current)
			&& ft_strcmp(current->next->token, "|") == 0)
			return (show_str_error(current->token));
		if ((ft_strcmp(current->token, "||") == 0 || ((ft_strcmp(current->token,
							"|") == 0 && is_quotes(current))
					&& (ft_strcmp(current->next->token, "|") == 0)
					&& is_quotes(current))))
			return (show_str_error(current->token));
		if (current->next && is_special_char(current->token)
			&& is_quotes(current) && is_special_char(current->next->token)
			&& is_quotes(current->next))
			return (show_str_error(current->token));
		current = current->next;
	}
	return (1);
}
