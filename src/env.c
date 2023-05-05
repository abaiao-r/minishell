/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:32:23 by quackson          #+#    #+#             */
/*   Updated: 2023/05/05 17:11:53 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* add_env_node: adds a new environment node to the end of the environment 
list with the given variable name and value. */
void	add_env_node(char *var_name, char *var_value, int rank,
		t_env **environment)
{
	t_env	*env_node;

	env_node = malloc(sizeof(*env_node));
	env_node->var_name = var_name;
	env_node->var_value = var_value;
	env_node->rank = rank;
	env_node->next = NULL;
	ft_lstadd_back_env(environment, env_node);
}

/* create_env_node: creates a new environment node from a string
 in the format VAR_NAME=VAR_VALUE and adds it to the end of the 
environment list. */
void	create_env_node(char *env_var_str, int i, t_env **environment)
{
	char	*eq_pos;
	char	*var_name;
	char	*var_value;
	size_t	var_name_len;

	eq_pos = ft_strchr(env_var_str, '=');
	if (eq_pos == NULL)
	{
		perror("Error");
		return ;
	}
	var_name_len = eq_pos - env_var_str;
	var_name = malloc(var_name_len + 1);
	ft_strncpy(var_name, env_var_str, var_name_len);
	var_name[var_name_len] = '\0';
	var_value = eq_pos + 1;
	add_env_node(var_name, var_value, i, environment);
}

/* parse_env: parses the environment variables from the array of strings 
passed in and creates a linked list of environment nodes. */
t_env	*parse_env(char **environ)
{
	t_env	*environment;
	int		i;

	environment = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		create_env_node(environ[i], i, &environment);
		i++;
	}
	return (environment);
}

/* This function uses a simple bubble sort algorithm to sort a 
linked list of type t_env by the rank member of each node in 
ascending order. It returns the head of the sorted list. */
t_env	*sort_rank_env_list(t_env **head)
{
	t_env	*curr;
	int		swapped;

	swapped = 1;
	if (!head || !(*head)->next)
		return (*head);
	while (swapped)
	{
		swapped = 0;
		curr = *head;
		while (curr->next)
		{
			if (curr->rank > curr->next->rank)
			{
				swap_env_nodes(curr);
				swapped = 1;
			}
			curr = curr->next;
		}
	}
	return (*head);
}

/* show_env: displays the current environment variables to the user by calling 
parse_env, printing the environment list with print_env, and then freeing the 
environment list. */
int	show_env(t_env **environment)
{
	sort_rank_env_list(environment);
	print_env(environment);
	return (NO_EXIT);
}
