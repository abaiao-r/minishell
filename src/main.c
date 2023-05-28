/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/28 19:23:02 by andrefranci      ###   ########.fr       */
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
	char	*input;
/* 	int		status; */
	t_minishell	*minishell;
	//t_env	*environment;

	(void) argc;
	(void) argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->environment = parse_env(env);
	minishell->prompt = ft_calloc(1, sizeof(t_prompt));
	//execute_pipe((char*[]){"echo", "hello", NULL}, 2, (char*[]){"/bin/grep", "h", NULL}, 2);
	//exit(0);
	while (1)
	{
		minishell->input = ft_calloc(1, sizeof(t_input));
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
		/*if (!is_quote_parsed_valid(minishell->input))
		{
			free(minishell->prompt->prompt_full);
			free(input);
			free_input_list(&minishell->input);
			continue ;
		}*/
/* 		if (has_valid_redirections(&minishell->input->input) == 0)
		{
			free(input);
			free_input_list(&minishell->input);
			continue ;
		} */
		while (minishell->input)
		{
			printf("arg[%d] and within_quotes[%d]: %s\n", minishell->input->index, minishell->input->within_quotes, minishell->input->token);
			minishell->input = minishell->input->next;
		}
		/* status = exe_commands(&minishell->input->token); */
		//status = exe_cmd(quote_parsed, input, i, &minishell->environment);
    	free(minishell->prompt->prompt_full);
		free(input);
		free_token_list(&minishell->input);
		/* if (status == EXIT)
		{
			printf("\nexit");
			break ;
		} */
	}
	rl_clear_history();
	free_env_list(&minishell->environment);
	free(minishell->prompt);
	free(minishell);
	return (0);
}
