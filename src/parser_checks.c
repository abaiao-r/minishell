/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:57:01 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/19 18:15:27 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function: is_special_character
Checks if a given character is a special character used for command parsing.
c: The character to be checked.
returns: 1 if the character is a special character, 0 otherwise. */
static int	is_special_character(char c)
{
	return (c == ';' || c == '\\' || c == '[' || c == ']' || c == '{'
		|| c == '}' || c == '(' || c == ')');
}

/* Function: toggle_flag_quote
Toggles the flag_quote based on the current character and quote type.
flag_quote: A pointer to the flag_quote variable.
c: The current character being checked.
quote_type: A pointer to the quote_type variable. */
static void	toggle_flag_quote(int *flag_quote, char c, char *quote_type)
{
	if (*flag_quote == 0)
	{
		*quote_type = c;
		*flag_quote = 1;
	}
	else if (*flag_quote == 1)
	{
		if (*quote_type == c)
			*flag_quote = 0;
	}
}

/* Function: is_quotes_special_char_valid
Validates the input for special characters and quotes,
returning an error if invalid.
input: The input string to be validated.
returns: 1 if the input is valid, 0 otherwise. */
int	is_quotes_special_char_valid(char *input)
{
	int		flag_quote;
	char	quote_type;
	int		i;

	flag_quote = 0;
	i = 0;
	while (input[i])
	{
		if (is_special_character(input[i]) && !flag_quote)
			return (show_special_char_error(input[i]));
		if (input[i] == '\'' || input[i] == '\"')
		{
			toggle_flag_quote(&flag_quote, input[i], &quote_type);
		}
		i++;
	}
	if (flag_quote != 0)
		return (show_quotes_error());
	return (1);
}
