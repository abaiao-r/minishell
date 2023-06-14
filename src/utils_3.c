/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:49:22 by quackson          #+#    #+#             */
/*   Updated: 2023/06/07 20:48:14 by quackson        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	show_quotes_error(void)
{
	printf("Error: unclosed quotes\n");
	return (0);
}

int	is_quotes_special_char_valid(char *input)
{
	int		flag_quote;
	char	quote_type;
	int		i;

	i = -1;
	flag_quote = 0;
	while (input[++i])
	{
		if ((input[i] == ';' || input[i] == '\\') && !flag_quote)
			return (show_special_char_error(input[i]));
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (flag_quote == 0)
			{
				quote_type = input[i];
				flag_quote = 1;
			}
			else if (flag_quote == 1)
				if (quote_type == input[i])
					flag_quote = 0;
		}
	}
	if (flag_quote != 0)
		return (show_quotes_error());
	return (1);
}

int	is_redirection(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (1);
	if (ft_strcmp(str, "<") == 0)
		return (1);
	if (ft_strcmp(str, "<<") == 0)
		return (1);
	if (ft_strcmp(str, "|") == 0)
		return (1);
	return (0);
}

void	show_redirection_error(char *symbol)
{
	printf("minishell: syntax error near unexpected token `%s\"\n", symbol);
}

int	has_valid_redirections(char **args)
{
	int	i;

	if (!args)
	{
		printf("error: args is NULL\n");
		return (0);
	}
	i = 0;
	if (args[i] && is_redirection(args[i]))
	{
		show_redirection_error(args[i]);
		return (0);
	}
	while (args[i])
	{
		if (is_redirection(args[i]) && (!args[i + 1]
				|| is_redirection(args[i + 1])))
		{
			show_redirection_error(args[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
