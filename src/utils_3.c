/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:18:59 by quackson          #+#    #+#             */
/*   Updated: 2023/06/23 00:02:50 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char **tokens)
{
	if (!tokens || !tokens[0])
		return (0);
	if (ft_strcmp(tokens[0], "echo") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "cd") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "export") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "unset") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "env") == 0)
		return (1);
	if (ft_strcmp(tokens[0], "exit") == 0)
		return (1);
	return (0);
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

	status = 2;
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
		printf("minishell: exit: %s: enumeric argument required\n", tokens[1]);
	free_parsed(tokens);
	free_minishell(minishell);
	exit(status);
}

int	count_commands_lst(t_input *input)
{
	int	n_commands;

	n_commands = 0;
	while (input)
	{
		if (!ft_strncmp(input->token, "|", 1) && !input->in_quotes)
			n_commands++;
		input = input->next;
	}
	return (n_commands + 1);
}
