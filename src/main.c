/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/28 17:37:25 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	sigint_handler(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	print_prompt();
}

int	main(void)
{
	char	*input;
	char	**parsed;
	int		num_tokens;
	//int		i;
	int		status;

	signal(SIGINT, sigint_handler);
	status = 0;
	while (1)
	{
		print_prompt();
		input = readline("$ ");
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
		status = exe_cmd(parsed, num_tokens);
		free(input);
		free_parsed(parsed);
		if (status == EXIT)
			break ;
	}
	//printf("Goodbye!");
	return (0);
}
