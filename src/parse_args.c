/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:31:23 by quackson          #+#    #+#             */
/*   Updated: 2023/05/26 19:50:38 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_quote_flags(char current_char, int *flag_single_quotes,
		int *flag_double_quotes)
{
	if (current_char == '\'' && *flag_double_quotes == 0)
	{
		if (*flag_single_quotes == 0)
			*flag_single_quotes = 1;
		else
			*flag_single_quotes = 0;
	}
	else if (current_char == '\"' && *flag_single_quotes == 0)
	{
		if (*flag_double_quotes == 0)
			*flag_double_quotes = 1;
		else
			*flag_double_quotes = 0;
	}
}

int	ft_count_args(char *str)
{
	int		i;
	int		wc;
	int		flag_single_quotes;
	int		flag_double_quotes;

	flag_single_quotes = 0;
	flag_double_quotes = 0;
	wc = 0;
	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			update_quote_flags(str[i], &flag_single_quotes, &flag_double_quotes);
			i++;
		}
		if (str[i])
			wc++;
		while (flag_single_quotes == 1 || flag_double_quotes == 1)
		{
			if (str[i] == '\'' || str[i] == '\"')
				update_quote_flags(str[i], &flag_single_quotes, &flag_double_quotes);
			i++;
		}
		while (str[i] && !ft_isspace(str[i]))
		{
			if((str[i] == '|' || str[i] == '>' || str[i] == '<') && flag_double_quotes == 0 && flag_single_quotes == 0)
			{
				wc++;
				i++;
			}
			if(((str[i] == '|' && str[i + 1] == '|') || (str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')) && (flag_double_quotes == 0 && flag_single_quotes == 0))
			{
				wc++;
				i++;
				i++;
			}
			i++;
		}
	}
	return (wc);
}

/* main to test ft_count_args */
/* int	main(void)
{
	char	str1[] = " echo \"a'|'\"echo b";
	
	printf("%d\n", ft_count_args(str1));
} */

static int	create_parsed(t_parsed *parsed, char *str)
{
	parsed->arg_index = 0;
	parsed->string_len = ft_strlen(str);
	return (1);
}

/* This function initializes an argument structure. It allocates memory for 
the argument string, sets the initial argument length, and initializes the 
quote type. */
int	create_arg(t_parsed *parsed_args, t_arg *arg)
{
	arg->arg = malloc((parsed_args->string_len + 1) * sizeof(char));
	if (!arg->arg)
		return (0);
	arg->arg_len = 0;
	arg->in_quotes = 0;
	arg->within_quotes = 0;
	arg->quote_type = '\0';
	return (1);
}

/* Parses the string character by character.
It handles quotes, whitespace, redirection operators,
and pipe operators by calling the respective functions.
It stores the parsed arguments and operators in the args struct. */
static void parse_aux(t_parsed *args, t_arg *arg, char *str, int *i, t_input **head, t_input **tail)
{
    char c;
    int prev_was_pipe = 0;

    while (*i < args->string_len && arg->arg_len < args->string_len)
    {
        c = str[*i];
        if (handle_quotes(arg, c, i))
        {
            if (arg->in_quotes == 1 && arg->within_quotes == 0)
                arg->within_quotes = 1;
            continue;
        }
        if (!arg->in_quotes && ft_isspace(c))
            break;
        if (!arg->in_quotes && handle_redirection(args, arg, str, i))
            continue;
        if (!arg->in_quotes && c == '|')
        {
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len] = '\0';

                t_input *new_input = malloc(sizeof(t_input));
                new_input->input = arg->arg;
                new_input->index = args->arg_index;
                new_input->within_quotes = arg->within_quotes;
                new_input->next = NULL;

                if (*head == NULL)
                {
                    *head = new_input;
                    *tail = new_input;
                }
                else
                {
                    (*tail)->next = new_input;
                    *tail = new_input;
                }

                args->arg_index++;
                arg->arg = malloc(args->string_len * sizeof(char));
                arg->arg_len = 0;
            }

            // Create a separate node for the pipe character
            t_input *new_input = malloc(sizeof(t_input));
            new_input->input = ft_strdup("|");
            new_input->index = args->arg_index;
            new_input->within_quotes = arg->within_quotes;
            new_input->next = NULL;

            if (*head == NULL)
            {
                *head = new_input;
                *tail = new_input;
            }
            else
            {
                (*tail)->next = new_input;
                *tail = new_input;
            }

            args->arg_index++;
            (*i)++;
            prev_was_pipe = 1;
            continue;
        }
        arg->arg[arg->arg_len++] = c;
        (*i)++;
        prev_was_pipe = 0;
    }

    if (arg->arg_len > 0)
    {
        arg->arg[arg->arg_len] = '\0';

        t_input *new_input = malloc(sizeof(t_input));
        new_input->input = arg->arg;
        new_input->index = args->arg_index;
        new_input->within_quotes = arg->within_quotes;
        new_input->next = NULL;

        if (*head == NULL)
        {
            *head = new_input;
            *tail = new_input;
        }
        else
        {
            (*tail)->next = new_input;
            *tail = new_input;
        }

        args->arg_index++;
    }
    else if (!prev_was_pipe)
        free(arg->arg);
}

/* This is the main function for parsing arguments from a string.
It initializes the args struct, creates an iterator i, and starts 
a loop to process the string. Inside the loop, it creates a new arg 
struct, skips leading spaces, calls parse_aux to extract the argument 
from the string, and stores it in the linked list. Finally, it returns the head of the linked list. */
t_input	*parse_arguments(char *string)
{
	int			i;
	t_parsed	args;
	t_arg		arg;
	t_input		*head = NULL;
	t_input		*tail = NULL;

	if (!create_parsed(&args, string))
		return (NULL);

	i = 0;
	while (i < args.string_len)
	{
		if (!create_arg(&args, &arg))
		{
			// Clean up the allocated memory before returning NULL
			t_input *current = head;
			while (current != NULL)
			{
				t_input *next = current->next;
				free(current);
				current = next;
			}
			return (NULL);
		}

		while (i < args.string_len && ft_isspace(string[i]))
			i++;

		parse_aux(&args, &arg, string, &i, &head, &tail);
	}

	return (head);
}
