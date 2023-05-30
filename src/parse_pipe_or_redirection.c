/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_or_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:59:45 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/30 20:14:57 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* replace_input: Replaces a section of the input string with
a replacement string, adjusting the length of the input 
accordingly by allocating a new string, copying the necessary
parts, and updating the input pointer and length variables. */
static void	replace_input(char **input, t_por_data *por_data)
{
	size_t	new_input_len;
	char	*new_input;

	por_data->replacement_len = ft_strlen(por_data->replacement);
	new_input_len = por_data->input_len + por_data->replacement_len
		- (por_data->end - por_data->start - 1);
	new_input = ft_calloc(new_input_len + 1, sizeof(char));
	ft_memcpy(new_input, *input, por_data->start);
	ft_memcpy(new_input + por_data->start, por_data->replacement,
		por_data->replacement_len);
	ft_memcpy(new_input + por_data->start + por_data->replacement_len,
		&(*input)[por_data->end],
		por_data->input_len - por_data->end + 1);
	free(*input);
	*input = new_input;
	por_data->input_len = new_input_len;
}

/* add_space: Inserts a space before and after a specific character in the
input string, creating a new replacement string and using the replace_input
function to perform the replacement, updating the input pointer and length
variables accordingly. */
static void	add_space(char **input, t_por_data *por_data, size_t *i)
{
	char	c;
	char	*before_space;
	char	*before_after_space;

	c = (*input)[*i];
	por_data->start = *i;
	if (c == (*input)[*i + 1])
		(*i)++;
	por_data->end = *i + 1;
	before_space = ft_strndup(&(*input)[por_data->start],
			por_data->end - por_data->start);
	before_after_space = ft_strjoin(" ", before_space);
	por_data->replacement = ft_strjoin(before_after_space, " ");
	if (por_data->replacement)
	{
		replace_input(input, por_data);
		*i = por_data->start + por_data->replacement_len;
	}
	free(por_data->replacement);
	free(before_space);
	free(before_after_space);
}

/* update_quote_flags: Updates flags that track whether the current character
is within single quotes, double quotes, or outside of quotes. */
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

/* parse_pipe_or_redirection: Parses the input string,
iterating through each character, updating quote flags,
and calling add_space when encountering specific characters
(pipe, greater than, and less than signs) that are not within
quotes, ultimately returning the modified input string. */
char	*parse_pipe_or_redirection(char *input)
{
	size_t		i;
	t_por_data	*por_data;

	i = 0;
	por_data = malloc(sizeof(t_por_data));
	por_data->input_len = ft_strlen(input);
	por_data->flag_single_quotes = 0;
	por_data->flag_double_quotes = 0;
	while (i < por_data->input_len)
	{
		if (input[i] == '\'' || input[i] == '\"')
			update_quote_flags(input[i], &(por_data->flag_single_quotes),
				&(por_data->flag_double_quotes));
		if ((input[i] == '|' || input[i] == '>' || input[i] == '<')
			&& ((por_data->flag_single_quotes == 0)
				&& (por_data->flag_double_quotes == 0)))
			add_space(&input, por_data, &i);
		else
			i++;
	}
	free(por_data);
	return (input);
}

/* test parse_pipe_or_redirection */
/* int main(void)
{
    char *str = "HELLO|||World |\">'<<<hh\"";
    char *input;

    input = (char *)calloc(strlen(str) + 1, sizeof(char));
    strcpy(input, str);

    printf("%s", input);

    input = parse_pipe_or_redirection(input);

    printf("\n\n%s\n", input);

    free(input);

    return (0);
} */