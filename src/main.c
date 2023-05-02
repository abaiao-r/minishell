/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/02 17:13:52 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**parsed;
	char	**quote_parsed;
	int		i;
	int		status;

	(void) ac;
	(void) av;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	status = 0;
	while (1)
	{
		input = print_prompt();
		add_history(input);
		//i = 0;
		if (!is_valid_input(input))
			continue ;
		//num_tokens = count_words(input);
		parsed = ft_split_default(input);
		if (!parsed)
			continue ;
		quote_parsed = parse_echo_arguments(input);
		i = 0;
		while (quote_parsed[i] != NULL)
		{
			//printf("Echoed string %d: %s\n", i, quote_parsed[i]);
			i++;
		}
		/* printf("num_tokens: %d\n", num_tokens);
		if (num_tokens >= 0)
		{
			i = 0;
			while (i < num_tokens)
			{
				printf("-> %s\n", parsed[i]);
				i++;
			}
		} */
		status = exe_cmd(quote_parsed, input, i, env);
		free(input);
		free_parsed(parsed);
		free_parsed(quote_parsed);
		if (status == EXIT)
			break ;
	}
	rl_clear_history();
	return (0);
}
