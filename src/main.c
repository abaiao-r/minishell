/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:35:09 by quackson          #+#    #+#             */
/*   Updated: 2023/04/20 19:26:58 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char	*input;
	char	**parsed;
	int	 	num_args;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		add_history(input);
		num_args = 0;
		parsed = ft_split(input, &num_args);
		if (!parsed)
			continue ;
		if (num_args >= 0)
		{
			for (int i = 0; i < num_args; i++) {
				printf("-> %s\n", parsed[i]);
			}
		}
		exe_command(parsed);
		free(input);
		free(parsed);
		//free(args);
	}
	printf("Goodbye!\n");
	return (0);
}
