/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/05 17:45:32 by quackson         ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->environment = parse_env(env);
	minishell->prompt = ft_calloc(1, sizeof(t_prompt));
	while (1)
	{

		input = print_prompt(&minishell->prompt);
		if (!input)
		{
			free_env_list(&minishell->environment);
			free(minishell->prompt->prompt_full);
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (!*input || !is_quotes_special_char_valid(input))
		{	
			free(input);
			free(minishell->prompt->prompt_full);
			continue ;
		}
		input = parse_dollar(input, &minishell->environment);
		input = parse_pipe_or_redirection(input);
		minishell->input = parse_arguments(input);
		if (!is_pipe_or_redirection_valid(minishell->input))
		{
			free(input);
			free_parsed(token_2d);
			free_token_list(&minishell->input);
			free(minishell->prompt->prompt_full);
			continue ;
		}
		t_input *teste = minishell->input;
		while (teste)
		{
			printf("token[%d] and within_quotes[%d]: %s\n", teste->index, teste->within_quotes, teste->token);
			teste = teste->next;
		}
		/* status = exe_commands(&minishell->input->token); */
		token_2d = create_token_array_2d(minishell->input);
		if(token_2d)
		{
			int i=0;
			while (token_2d[i])
			{
				printf("token_2d[%d]: %s\n", i, token_2d[i]);
				i++;
			}
		}
		minishell->tokens = token_2d;
		status = exe_commands(minishell);
		free(input);
		free_parsed(token_2d);
		free_token_list(&minishell->input);
		free(minishell->prompt->prompt_full);
		if (status == EXIT)
		{
			printf("exit\n");
			break ;
		}
	}
	rl_clear_history();
	free_env_list(&minishell->environment);
	free(minishell->prompt);
	free(minishell);
	return (0);
}
