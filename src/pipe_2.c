/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:05:56 by quackson          #+#    #+#             */
/*   Updated: 2023/06/22 23:06:19 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
