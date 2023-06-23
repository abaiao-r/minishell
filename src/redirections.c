/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:49:56 by quackson          #+#    #+#             */
/*   Updated: 2023/06/23 23:50:38 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	redirect_output(char *file, int append)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0666);
	if (fd < 0)
	{
		perror("open failed");
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

char	**get_command_without_redirects(t_input *input)
{
	char	**command;
	int		num_args;
	int		redirect_flag;
	int		i;

	num_args = count_arguments(input);
	command = malloc(sizeof(char *) * (num_args + 1));
	if (!command)
		return (NULL);
	redirect_flag = 0;
	i = 0;
	while (input && !(!ft_strncmp(input->token, "|", 1) && !input->in_quotes))
	{
		if (redirect_flag)
			redirect_flag = 0;
		else if (is_redirection(input->token) && !input->in_quotes)
			redirect_flag = 1;
		else
			command[i++] = ft_strdup(input->token);
		if (i > 0 && !command[i - 1])
			return (NULL);
		input = input->next;
	}
	command[i] = NULL;
	return (command);
}

int	handle_redirections(t_input *input, t_minishell *minishell)
{
	int	result;

	result = 1;
	while (input && !(!ft_strncmp(input->token, "|", 1) && !input->in_quotes))
	{
		if (!ft_strncmp(input->token, "<<", 2) && !input->in_quotes)
			result = heredoc(input->next->token, minishell);
		else if (!ft_strncmp(input->token, "<", 1) && !input->in_quotes)
			result = redirect_input(input->next->token);
		else if (!ft_strncmp(input->token, ">>", 2) && !input->in_quotes)
			result = redirect_output(input->next->token, 1);
		else if (!ft_strncmp(input->token, ">", 1) && !input->in_quotes)
			result = redirect_output(input->next->token, 0);
		if (!result)
			return (0);
		input = input->next;
	}
	return (result);
}
