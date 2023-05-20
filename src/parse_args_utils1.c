/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:38:59 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/19 23:47:06 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Checks if the current character is a quote (' or ")
and toggles the in_quotes flag accordingly.
Returns true if the quote is handled, false otherwise. */
bool	handle_quotes(t_arg *arg, char c, int *i)
{
	if (!arg->in_quotes && (c == '\'' || c == '\"'))
	{
		arg->in_quotes = 1;
		arg->quote_type = c;
		(*i)++;
		return (true);
	}
	if (arg->in_quotes && c == arg->quote_type)
	{
		arg->in_quotes = 0;
		arg->quote_type = '\0';
		(*i)++;
		return (true);
	}
	return (false);
}