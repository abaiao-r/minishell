/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:31:23 by quackson          #+#    #+#             */
/*   Updated: 2023/06/08 18:03:17 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Adds a new input string (arg->arg) to the linked list (t_input) 
with corresponding index and quote information. If the list is empty, 
the new input becomes the head. Otherwise, it is appended to the end 
of the list.*/
static void	add_token_node(t_arg *arg, t_input **head)
{
	t_input	*current;
	t_input	*new_input;

	arg->arg[arg->arg_len] = '\0';
	new_input = malloc(sizeof(t_input));
	new_input->token = arg->arg;
	new_input->index = arg->arg_index;
	new_input->within_quotes = arg->within_quotes;
	new_input->next = NULL;
	if (*head == NULL)
		*head = new_input;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_input;
	}
	arg->arg_index++;
	arg->arg_len = 0;
}

/* Processes each character in the input string and it adds 
the character to the current argument string (arg->arg) and updates 
the argument length (arg->arg_len), index (arg->arg_index). */
static void	process_argument(t_arg *arg, char *str, int *i, t_input **head)
{
	(void)head;
	arg->operator[0] = arg->c;
	if (arg->c == str[*i + 1])
		arg->operator[1] = str[*i + 1];
	else
		arg->operator[1] = '\0';
	arg->arg[arg->arg_len++] = arg->c;
	(*i)++;
}

/* Iterates over the input string, character by character, and calls 
handle_quotes to handle quotation marks. If the character is not 
within quotes and is a whitespace, it breaks the loop. Otherwise, it 
processes the argument by calling process_argument. After the loop, if 
there is a non-empty argument, it adds it to the linked list using 
add_new_input. If there was no previous pipe, it frees the memory allocated 
for the argument string. */
static void	parse_aux(t_arg *arg, char *str, int *i, t_input **head)
{
	while (*i < arg->string_len && arg->arg_len < arg->string_len)
	{
		arg->c = str[*i];
		if (handle_quotes(arg, arg->c, i))
		{
			if (arg->in_quotes == 1 && arg->within_quotes == 0)
				arg->within_quotes = 1;
			continue ;
		}
		if (!arg->in_quotes && ft_isspace(arg->c))
			break ;
		process_argument(arg, str, i, head);
	}
	if (arg->arg_len > 0)
		add_token_node(arg, head);
}

/* The main function that parses the input string. It initializes variables, 
creates an empty linked list, and iterates through the input string. 
For each iteration, it creates a new argument, skips whitespace, and calls 
parse_aux to process the argument and add it to the linked list. Returns the 
head of the linked list containing parsed arguments. */
t_input	*parse_arguments(char *string)
{
	int		i;
	t_arg	arg;
	t_input	*head;

	head = NULL;
	if (!start_arg(&arg, string))
		return (NULL);
	i = 0;
	while (i < arg.string_len)
	{
		if (!update_arg(&arg, string, &i))
		{
			free_arg(head);
			return (NULL);
		}
		while (i < arg.string_len && ft_isspace(string[i]))
			i++;
		parse_aux(&arg, string, &i, &head);
	}
	return (head);
}
