/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:35:09 by quackson          #+#    #+#             */
/*   Updated: 2023/04/21 15:44:50 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char	*input;
	char	**parsed;
	int	 	num_tokens;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		add_history(input);
		num_tokens = 0;
		parsed = ft_split(input, &num_tokens);
		if (!parsed)
			continue ;
		/* if (num_tokens >= 0)
		{
			for (int i = 0; i < num_tokens; i++) {
				printf("-> %s\n", parsed[i]);
			}
		} */
		exe_cmd(parsed, num_tokens);
		//exe_command(parsed);
		free(input);
		//free(parsed);
		//free(args);
	}
	printf("Goodbye!\n");
	return (0);
}
