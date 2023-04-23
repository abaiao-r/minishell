/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/23 23:03:42 by andrefranci      ###   ########.fr       */
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
		printf("%s\n", input);
		add_history(input);
		i = 0;
		num_tokens = count_words(input);
		parsed = ft_split_default(input);
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
		//free(parsed);
		//free(args);
	}
	printf("Goodbye!\n");
	return (0);
}
