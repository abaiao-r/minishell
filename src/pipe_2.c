/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:05:56 by quackson          #+#    #+#             */
/*   Updated: 2023/06/24 19:22:28 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* *get_next_cmd: returns the next command.
If the input is NULL, it returns NULL. If the input is not NULL,
it iterates through the input until it finds a pipe token. If it
finds a pipe token, it returns the next input; otherwise, it returns
NULL. */
t_input	*get_next_cmd(t_input *input)
{
	while (input)
	{
		if (!ft_strncmp(input->token, "|", 1) && !input->in_quotes)
			return (input->next);
		input = input->next;
	}
	return (input);
}

/* count_tokens_str: returns the number of tokens in the array of tokens. */
int	count_tokens_str(char **args)
{
	int		i;

	i = 0;
	while (*args)
	{
		args++;
		i++;
	}
	return (i);
}

/* count_arguments: returns the number of arguments in the input.
It iterates through the input until it finds a pipe token. If it
finds a pipe token, it returns the number of arguments; otherwise,
it returns 0. */
int	count_arguments(t_input *input)
{
	int		num_args;
	int		redirect_flag;

	num_args = 0;
	redirect_flag = 0;
	while (input && !(!ft_strncmp(input->token, "|", 1) && !input->in_quotes))
	{
		if (redirect_flag)
			redirect_flag = 0;
		else if (is_redirection(input->token) && !input->in_quotes)
			redirect_flag = 1;
		else
			num_args++;
		input = input->next;
	}
	return (num_args);
}

/*print_error: prints the error message and exits the program. */
void	print_error_shell(char *str)
{
	perror(str);
	exit(1);
}
