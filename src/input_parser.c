/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:15:08 by quackson          #+#    #+#             */
/*   Updated: 2023/06/19 18:30:30 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function: new_parse_args_aux
Helper function for new_parse_arguments. Handles parsing of words
and redirection symbols.
head: A pointer to the head of the linked list.
input: The input string.
i: A pointer to the current index in the input string. */
void	new_parse_args_aux(t_input **head, char *input, int *i)
{
	int	len;

	len = get_word_len(input + *i);
	if (len > 0)
		add_word(head, input, *i, *i + len);
	*i += len;
}

/* Function: get_word_len
Determines the length of a word in the input string, considering quotes.
input: The input string.
returns: The length of the word. */
int	get_word_len(char *input)
{
	int		len;
	char	*tmp;

	len = 0;
	while (*input && !ft_isspace(*input) && !get_redirection_len(input))
	{
		if (*input == '\'' || *input == '\"')
		{
			tmp = ft_strchr(input + 1, *input);
			len += tmp - input + 1;
			input = tmp + 1;
		}
		else
		{
			len++;
			input++;
		}
	}
	return (len);
}

/* Function: new_parse_arguments
Parses the input string into a linked list of tokens,
considering quotes and redirection symbols.
input: The input string to be parsed.
minishell: The minishell instance (unused in the function).
returns: The head of the linked list of tokens. */
t_input	*new_parse_arguments(char *input, t_minishell *minishell)
{
	int		i;
	t_input	*head;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		else if (get_redirection_len(input + i))
		{
			add_word(&head, input, i, i + get_redirection_len(input + i));
			i += get_redirection_len(input + i);
		}
		else
			new_parse_args_aux(&head, input, &i);
	}
	if (!head)
		free_input_resources(minishell);
	return (head);
}
