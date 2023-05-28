/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/28 23:03:54 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	main(int argc, char **argv, char **env)
{
	char		*input;
	int			status;
	char		**token_2d;
	t_minishell	*minishell;

	//t_env	*environment;
	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->environment = parse_env(env);
	minishell->prompt = ft_calloc(1, sizeof(t_prompt));
	minishell->input = ft_calloc(1, sizeof(t_input));
	//execute_pipe((char*[]){"echo", "hello", NULL}, 2, (char*[]){"/bin/grep","h", NULL}, 2);
	//exit(0);
	while (1)
	{
		input = print_prompt(minishell->prompt);
		if (!input)
		{
			free_env_list(&minishell->environment);
			free(minishell->prompt->prompt_full);
			free(minishell->prompt);
			free_token_list(&minishell->input);
			free(minishell->input);
			printf("exit\n");
			return (0);
		}
		add_history(input);
		if (!is_valid_input(input))
			continue ;
		input = parse_dollar(input, &minishell->environment);
		minishell->input = parse_arguments(input);
		if (!is_quote_parsed_valid(minishell->input))
		{
			free(minishell->prompt->prompt_full);
			free(input);
			free_token_list(&minishell->input);
			continue ;
		}
		/* 		if (has_valid_redirections(&minishell->input->input) == 0)
		{
			free(input);
			free_input_list(&minishell->input);
			continue ;
		} */
		t_input *teste = minishell->input;
		while (teste)
		{
			printf("arg[%d] and within_quotes[%d]: %s\n", teste->index, teste->within_quotes, teste->token);
			teste = teste->next;
		}
		/* status = exe_commands(&minishell->input->token); */
		token_2d = create_token_array_2d(minishell->input);
		int i=0;
		while (token_2d[i])
		{
			printf("arg[%d]: %s\n", i, token_2d[i]);
			i++;
		}
		status = exe_cmd(token_2d, input, 4, &minishell->environment);
		free(minishell->prompt->prompt_full);
		free(input);
		free_token_list(&minishell->input);
		if (status == EXIT)
		{
			printf("\nexit");
			break ;
		}
	}
	rl_clear_history();
	free_env_list(&minishell->environment);
	free(minishell->prompt);
	free(minishell);
	return (0);
}
