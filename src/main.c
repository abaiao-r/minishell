/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 22:55:59 by quackson          #+#    #+#             */
/*   Updated: 2023/06/17 18:30:22 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_in_command;

void	print_list(t_input *input)
{
	t_input	*temp;

	temp = input;
	while (temp != NULL)
	{
		printf("lst: %s  ", temp->token);
		printf("size:%ld len:%ld\n", sizeof(temp->token), ft_strlen(temp->token));
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

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		clear_history();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_in_command)
			rl_redisplay();
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
		input = readline("\033[1;33mminishell$ \033[0m");
		g_in_command = 1;
		response = validate_and_load_data(minishell, input);
		if (response == INVALID)
			continue ;
		minishell->tokens = create_token_array_2d(minishell->input, minishell);
		if (!minishell->tokens)
		{
			free_input_resources(minishell);
			continue ;
		}
		//print_array_of_strings(minishell->tokens);
		//free(input);
		//input = NULL;
		exe_commands(minishell);
		free_input_resources(minishell);
		g_in_command = 0;
	}
	free_minishell(minishell);
	return (0);
}
