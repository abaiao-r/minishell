/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:16:25 by quackson          #+#    #+#             */
/*   Updated: 2023/06/18 20:54:32 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	minishell->input_str = parse_dollar_question(minishell->input_str, minishell->exit_status);
	minishell->input_str = parse_dollar(minishell->input_str, &minishell->environment);
	minishell->input = new_parse_arguments(minishell->input_str, minishell);
	if (!is_pipe_or_redirection_valid(minishell->input))
	{
		free_input_resources(minishell);
		return (INVALID);
	}
	return (VALID);
}

t_minishell	*init_minishell(char **env)
{
	t_minishell	*minishell;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	//signal(SIGQUIT, SIG_IGN);
	g_minishell.in_command = 0;
	g_minishell.sigint = 0;
	g_minishell.sigquit = 0;
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->environment = parse_env(env);
	//minishell->prompt = ft_calloc(1, sizeof(t_prompt));
	//minishell->prompt->prompt_full = NULL;
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
	//free(minishell->prompt->prompt_full);
	minishell->input_str = NULL;
	minishell->tokens = NULL;
	minishell->input = NULL;
	//minishell->prompt->prompt_full = NULL;
}

void	free_minishell(t_minishell *minishell)
{
	rl_clear_history();
	free_input_resources(minishell);
	free_env_list(&minishell->environment);
	//free(minishell->prompt);
	free(minishell);
}
