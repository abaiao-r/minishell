/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/30 23:56:11 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	sigint_handler(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	//print_prompt();
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**parsed;
	int		num_tokens;
	//int		i;
	int		status;
	(void) ac;
	(void) av;
	
	signal(SIGINT, sigint_handler);
	status = 0;
	while (1)
	{
		input = print_prompt();
		add_history(input);
		//i = 0;
		num_tokens = count_words(input);
		parsed = ft_split_default(input);
		if (!parsed)
			continue ;
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
		status = exe_cmd(parsed, num_tokens, env);
		free(input);
		free_parsed(parsed);
		if (status == EXIT)
			break ;
	}
	rl_clear_history();
	return (0);
}
