/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:28:43 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/19 18:19:08 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function: free_parsed
Frees the memory allocated for the parsed array and its elements.
parsed: The array of parsed strings to be freed. */
void	free_parsed(char **parsed)
{
	int	i;

	if (!parsed)
		return ;
	i = 0;
	while (parsed[i])
	{
		free(parsed[i]);
		i++;
	}
	free(parsed[i]);
	free(parsed);
	parsed = NULL;
}

/* Function: free_token_list
Frees the memory allocated for the linked list of input tokens.
head: A pointer to the head of the token list. */
void	free_token_list(t_input **head)
{
	t_input	*node;
	t_input	*next_node;

	node = *head;
	while (node != NULL)
	{
		next_node = (node)->next;
		free((node)->token);
		free(node);
		node = next_node;
	}
}

/* Function: free_input_resources
Frees the memory allocated for input-related resources in the minishell instance.
minishell: The minishell instance containing the input
resources to be freed. */
void	free_input_resources(t_minishell *minishell)
{
	free(minishell->input_str);
	free_parsed(minishell->tokens);
	free_token_list(&minishell->input);
	minishell->input_str = NULL;
	minishell->tokens = NULL;
	minishell->input = NULL;
}

/* Function: free_minishell
Frees the memory allocated for the minishell instance and
its associated resources.
minishell: The minishell instance to be freed. */
void	free_minishell(t_minishell *minishell)
{
	rl_clear_history();
	free_input_resources(minishell);
	free_env_list(&minishell->environment);
	free(minishell);
}
