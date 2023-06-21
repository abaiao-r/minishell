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
		if (is_redirection(args[i]) && (!args[i + 1] || is_redirection(args[i
					+ 1])))
		{
			show_redirection_error(args[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_minishell *minishell, char **tokens, int num_tokens)
{
	unsigned char	status;

	if (num_tokens == 1)
		status = 0;
	else if (num_tokens > 2 && printf("exit: too many arguments\n"))
		status = 1;
	else if (ft_isnumber(tokens[1]))
	{
		status = ft_atoi(tokens[1]);
		if ((tokens[1][0] == '-' && ft_strcmp(tokens[1], LLONG_MIN_STR)) > 0
			|| ft_strcmp(tokens[1], LLONG_MAX_STR) > 0)
		{
			printf("minishell: exit: %s: numeric argument required\n",
				tokens[1]);
			status = 2;
		}
	}
	else
	{
		printf("minishell: exit: %s: enumeric argument required\n", tokens[1]);
		status = 2;
	}
	free_parsed(tokens);
	free_minishell(minishell);
	exit(status);
}
