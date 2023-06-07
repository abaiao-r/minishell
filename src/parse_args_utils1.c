/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:38:59 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/07 19:47:06 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Initializes the t_arg structure with default values, 
such as setting the argument index to 0 and calculating the 
length of the input string. Returns 1 to indicate success. */
int	start_arg(t_arg *arg, char *str)
{
	arg->arg_index = 0;
	arg->string_len = ft_strlen(str);
	return (1);
}

/* Allocates memory for the arg->arg string based on the length 
of the input string. Sets various members of the t_arg structure 
to their initial values. Returns 1 if memory allocation is successful, 
0 otherwise. */
int	update_arg(t_arg *arg)
{
	arg->arg = malloc((arg->string_len + 1) * sizeof(char));
	if (!arg->arg)
		return (0);
	arg->arg_len = 0;
	arg->in_quotes = 0;
	arg->within_quotes = 0;
	arg->quote_type = '\0';
	arg->c = '\0';
	arg->operator[0] = '\0';
	arg->operator[1] = '\0';
	arg->operator[2] = '\0';
	return (1);
}

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

/* Frees the memory allocated for each node in the linked list by 
traversing through it and freeing each node. */
void	free_arg(t_input *head)
{
	t_input	*current;
	t_input	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
}
