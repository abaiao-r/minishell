/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_question.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:04:29 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/14 17:23:30 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Updates the flag_single_quotes and flag_double_quotes based on the
current character. */
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

/* Finds the index of the first occurrence of '$' character in input
Skips the '$' if it is within single quotes ('')
Returns the index if found, otherwise returns -1 */
static int	find_dollar(char *input)
{
	int	i;
	int	flag_single_quotes;
	int	flag_double_quotes;

	flag_single_quotes = 0;
	flag_double_quotes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			update_quote_flags(input[i], &(flag_single_quotes),
				&(flag_double_quotes));
		if (input[i] == '$' && flag_single_quotes == 0 && input[i + 1] == '?')
			return (i);
		i++;
	}
	return (-1);
}

/* Replaces "$?" in input with the exit_status value
Returns the modified input string with replaced value
Memory for input, temp, and new_input is properly managed to avoid leaks */
char	*parse_dollar_question(char *input, int exit_status)
{
	char	*temp;
	char	*new_input;
	size_t	new_input_len;
	int		dollar_pos;

	dollar_pos = find_dollar(input);
	if (dollar_pos == -1)
		return (input);
	temp = ft_itoa(exit_status);
	new_input_len = ft_strlen(input) + ft_strlen(temp) - 1;
	new_input = ft_calloc(new_input_len + 1, sizeof(char));
	ft_memcpy(new_input, input, dollar_pos);
	ft_memcpy(new_input + dollar_pos, temp, ft_strlen(temp));
	ft_memcpy(new_input + dollar_pos + ft_strlen(temp), input + dollar_pos + 2,
		ft_strlen(input) - dollar_pos - 1);
	free(input);
	input = NULL;
	free(temp);
	new_input = parse_dollar_question(new_input, exit_status);
	return (new_input);
}

/* main to test parse_dollar question */
/* int	main(void)
{
	char *input = strdup("echo $?3 and goodbye $?$?4");
	int exit_status = 1;

	input = parse_dollar_question(input, exit_status);

	printf("%s\n", input);

	return (0);
} */