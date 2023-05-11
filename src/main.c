/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/11 14:15:55 by abaiao-r         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**quote_parsed;
	int		i;
	int		status;
	t_env	*environment;

	(void) argc;
	(void) argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	environment = parse_env(env);
	//execute_pipe((char*[]){"echo", "hello", NULL}, 2, (char*[]){"/bin/grep", "h", NULL}, 2);
	//exit(0);
	while (1)
	{
		input = print_prompt();
		if (!input)
		{
			free_env_list(&environment);
			return (0);
		}
		add_history(input);
		if (!is_valid_input(input))
			continue ;
		quote_parsed = parse_arguments(input);
		i = 0;
		while (quote_parsed[i] != NULL)
		{
			printf("Echoed string %d: %s\n", i, quote_parsed[i]);
			i++;
		}
		status = exe_cmd(quote_parsed, input, i, &environment);
		free(input);
		free_parsed(quote_parsed);
		if (status == EXIT)
			break ;
	}
	rl_clear_history();
	free_env_list(&environment);
	return (0);
}
