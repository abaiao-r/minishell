/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/08 00:10:38 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_input *input)
{
	t_input	*temp;

	temp = input;
	while (temp != NULL)
	{
		printf("lst: %s  ", temp->token);
		printf("size:%ld len:%ld\n", sizeof(input->token), ft_strlen(input->token));
		temp = temp->next;
	}
}

void	print_array_of_strings(char ** strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		printf("string[%d]: %s  ", i, strings[i]);
		printf("size:%ld len:%ld\n", sizeof(strings[i]), ft_strlen(strings[i]));
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	int			response;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = init_minishell(env);
	while (1)
	{
		input = print_prompt(&minishell->prompt);
		response = validate_and_load_data(minishell, input);
		if (response == INVALID)
			continue ;
		//print_list(minishell->input);
		minishell->tokens = create_token_array_2d(minishell->input, minishell);
		//print_array_of_strings(minishell->tokens);
		if (!minishell->tokens)
			continue ;
		exe_commands(minishell);
		free_input_resources(minishell);
	}
	free_minishell(minishell);
	return (0);
}
