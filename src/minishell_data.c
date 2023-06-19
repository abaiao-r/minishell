/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:16:25 by quackson          #+#    #+#             */
/*   Updated: 2023/06/19 18:22:54 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function: init_minishell: Initializes a minishell instance
by setting up signal handlers, allocating memory,
and initializing the necessary variables and data structures.
env: The environment variables passed to the minishell.
returns: A pointer to the initialized minishell instance. */
t_minishell	*init_minishell(char **env)
{
	t_minishell	*minishell;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	g_minishell.in_command = 0;
	g_minishell.sigint = 0;
	g_minishell.sigquit = 0;
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->environment = parse_env(env);
	minishell->input_str = NULL;
	minishell->tokens = NULL;
	minishell->input = NULL;
	return (minishell);
}

/* Function: parse_input
Parses the input by performing necessary substitutions and
tokenizing the input string.
minishell: The minishell instance containing the input string. */
static void	parse_input(t_minishell *minishell)
{
	minishell->input_str = parse_dollar_question(minishell->input_str,
			minishell->exit_status);
	minishell->input_str = parse_dollar(minishell->input_str,
			&minishell->environment);
	minishell->input = new_parse_arguments(minishell->input_str, minishell);
}

/* Function: validate_and_load_data
Validates the input, adds it to history, performs input
parsing and checks for pipe/redirect validity.
minishell: The minishell instance containing the input
string and data structures.
input: The input string to be validated and processed.
returns: VALID if the input is valid, INVALID otherwise */
int	validate_and_load_data(t_minishell *minishell, char *input)
{
	minishell->input_str = input;
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
		free_input_resources(minishell);
		return (INVALID);
	}
	parse_input(minishell);
	if (!is_pipe_or_redirection_valid(minishell->input))
	{
		free_input_resources(minishell);
		return (INVALID);
	}
	return (VALID);
}
