/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exe_commands_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:40:17 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/24 17:48:52 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	else if (num_tokens > 2 && write(2, "exit: too many arguments\n", 24))
		status = 1;
	else if (ft_isnumber(tokens[1]))
	{
		status = ft_atoi(tokens[1]);
		if ((tokens[1][0] == '-' && ft_strcmp(tokens[1], LLONG_MIN_STR)) > 0
			|| ft_strcmp(tokens[1], LLONG_MAX_STR) > 0)
		{
			print_error_exit(tokens[1]);
			status = 2;
		}
	}
	else
		print_error_exit(tokens[1]);
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
