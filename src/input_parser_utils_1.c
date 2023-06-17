/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:02:44 by quackson          #+#    #+#             */
/*   Updated: 2023/06/17 17:16:48 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_quote(int *single_quote, int *double_quote, int *i, char *input)
{
	if (input[*i] == '\'')
		*single_quote = 1;
	else if (input[*i] == '\"')
		*double_quote = 1;
}

int	is_between_quotes(char *input, int index)
{
	int		single_quote;
	int		double_quote;
	int		i;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (single_quote == 0 && double_quote == 0)
				start_quote(&single_quote, &double_quote, &i, input);
			else if (single_quote == 1 && input[i] == '\'')
				single_quote = 0;
			else if (double_quote == 1 && input[i] == '\"')
				double_quote = 0;
			if (!(double_quote == 1 && input[i] != '\"')
				&& !(single_quote == 1 && input[i] != '\'') && i == index)
				return (-1);
		}
		if (i == index)
			return (single_quote || double_quote);
	}
	return (0);
}

int	get_redirection_len(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	return (0);
}

char	*get_word(char *input, int start, int end, int *quote_flag)
{
	int		in_quotes;
	int		i;
	int		j;
	char	*word;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	while (input[start + i] && start + i < end)
	{
		in_quotes = is_between_quotes(input, start + i);
		if (in_quotes == 1)
			*quote_flag = 1;
		if (in_quotes == 1 || in_quotes == 0)
		{
			word[j] = input[start + i];
			j++;
		}
		i++;
	}
	word[j] = '\0';
	return (word);
}

void	add_word(t_input **head, char *input, int start, int end)
{
	char	*word;
	t_input	*node;
	int		quote_flag;

	quote_flag = 0;
	word = get_word(input, start, end, &quote_flag);
	if (!word)
		return ;
	node = new_node(word);
	node->within_quotes = quote_flag;
	ft_lstadd_back_parser(head, node);
}
