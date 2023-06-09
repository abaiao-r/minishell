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

int	validate_and_load_data(t_minishell *minishell, char *input)
{
	if (!input)
	{
		free_minishell(minishell);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (*input)
		add_history(input);
	if (!*input || !is_quotes_special_char_valid(input)
		|| ft_is_input_quotes_and_whitespaces(input))
	{
		free(input);
		free(minishell->prompt->prompt_full);
		return (INVALID);
	}
	input = parse_dollar_question(input, minishell->exit_status);
	input = parse_dollar(input, &minishell->environment);
	input = parse_pipe_or_redirection(input);
	minishell->input = parse_arguments(input);
	if (!is_pipe_or_redirection_valid(minishell->input))
	{
		free_input_resources(minishell);
		return (INVALID);
	}
	minishell->input_str = input;
	return (VALID);
}

t_minishell	*init_minishell(char **env)
{
	t_minishell	*minishell;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->environment = parse_env(env);
	minishell->prompt = ft_calloc(1, sizeof(t_prompt));
	minishell->input_str = NULL;
	minishell->tokens = NULL;
	minishell->input = NULL;
	return (minishell);
}

void	free_input_resources(t_minishell *minishell)
{
	free(minishell->input_str);
	free_parsed(minishell->tokens);
	free_token_list(&minishell->input);
	free(minishell->prompt->prompt_full);
	minishell->input_str = NULL;
	minishell->tokens = NULL;
	minishell->input = NULL;
	minishell->prompt->prompt_full = NULL;
}

void	free_minishell(t_minishell *minishell)
{
	rl_clear_history();
	free_input_resources(minishell);
	free_env_list(&minishell->environment);
	free(minishell->prompt);
	free(minishell);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
