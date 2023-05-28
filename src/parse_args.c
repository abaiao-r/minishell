/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:31:23 by quackson          #+#    #+#             */
/*   Updated: 2023/05/28 20:59:27 by andrefranci      ###   ########.fr       */
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
	//arg->arg = malloc(arg->string_len * sizeof(char));
	arg->arg_len = 0;
}

/* Handles the special case when encountering a < operator. Creates 
a new input node with the operator as the input string and adds it to 
the linked list. Increments the argument index and updates the current 
index (i) accordingly. Handles the case when the operator is a double 
symbol (e.g., <<) by incrementing i an extra time. */
static void	add_tokken_node_pipex(t_arg *arg, t_input **head, int *i,
		const char *operator)
{
	t_input	*new_input;
	t_input	*current;

	if (arg->arg_len > 0)
		add_token_node(arg, head);
	new_input = malloc(sizeof(t_input));
	new_input->token = ft_strdup(operator);
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
	(*i)++;
	if (ft_strlen(operator) == 2)
		(*i)++;
	arg->prev_was_pipe = 1;
}

/* Processes each character in the input string by checking if it
is an operator. If the character is within quotes and matches an 
operator, it calls add_tokken_node_pipex. Otherwise, it adds 
the character to the current argument string (arg->arg) and updates 
the argument length (arg->arg_len), index (arg->arg_index), and 
the previous pipe flag (arg->prev_was_pipe). */
static void	process_argument(t_arg *arg, char *str, int *i, t_input **head)
{
	arg->operator[0] = arg->c;
	if (arg->c == str[*i + 1])
		arg->operator[1] = str[*i + 1];
	else
		arg->operator[1] = '\0';
	if (!arg->in_quotes && is_operator(arg->operator))
	{
		add_tokken_node_pipex(arg, head, i, arg->operator);
		return ;
	}
	arg->arg[arg->arg_len++] = arg->c;
	(*i)++;
	arg->prev_was_pipe = 0;
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
	else if (!arg->prev_was_pipe)
		free(arg->arg);
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
		if (!update_arg(&arg))
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
