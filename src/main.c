/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/23 22:59:16 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;
	char	**parsed;
	int		num_tokens;
	int		i;

	while (1)
	{
		input = print_prompt();
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		add_history(input);
		i = 0;
		num_tokens = count_words(input);
		parsed = ft_split_1(input);
		if (!parsed)
			continue ;
		printf("num_tokens: %d\n", num_tokens);
		if (num_tokens >= 0)
		{
			i = 0;
			while (i < num_tokens)
			{
				printf("-> %s--------\n", parsed[i]);
				i++;
			}
		}
		exe_cmd(parsed, num_tokens);
		//exe_command(parsed);
		free(input);
		free(parsed);
		//free(args);
	}
	printf("Goodbye!\n");
	return (0);
}
