/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:38:59 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/08 18:05:06 by andrefranci      ###   ########.fr       */
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
int update_arg(t_arg *arg, char *str, int *i)
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

    // Check if there are more printable characters after the current position
    int j = (*i) + 1;
    while (j < arg->string_len && ft_isspace(str[j]))
        j++;
    if (j == arg->string_len)
    {
        free(arg->arg); // Free the allocated memory
        arg->arg = NULL;
    }

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
