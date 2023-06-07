/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:41:08 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/07 20:37:33 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		minishell->tokens = create_token_array_2d(minishell->input, minishell);
		if (!minishell->tokens)
			continue ;
		exe_commands(minishell);
		free_input_resources(minishell);
	}
	free_minishell(minishell);
	return (0);
}
