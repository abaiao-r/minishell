/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/18 19:47:41 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int main(int ac, char **av, char **envp)
{
    char *str;
    char *out;
    t_prompt    prompt;
	char	*input;

    prompt = prompt_init(av, envp);
} */

int	main(int ac,char **av, char **envp)
{
    char *input;

	while (1)
	{
		print_prompt();
		input = readline("");
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		add_history(input);
		// process input here
		free(input);
	}
	return (0);
}
