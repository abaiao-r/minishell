/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/22 13:17:01 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		num_tokens = count_words(input);
		parsed = ft_split_default(input);
		if (!parsed)
			continue ;
		if (num_tokens >= 0)
		{
			i = 0;
			while (i < num_tokens)
			{
				printf("-> %s\n", parsed[i]);
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
