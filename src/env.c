/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:32:23 by quackson          #+#    #+#             */
/*   Updated: 2023/04/28 21:04:42 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* add_env_node: adds a new environment node to the end of the environment 
list with the given variable name and value. */
void	add_env_node(char *var_name, char *var_value, t_env **environment)
{
	t_env	*env_node;

	env_node = malloc(sizeof(*env_node));
	env_node->var_name = var_name;
	env_node->var_value = var_value;
	env_node->next = NULL;
	ft_lstadd_back_env(environment, env_node);
}

/* create_env_node: creates a new environment node from a string
 in the format VAR_NAME=VAR_VALUE and adds it to the end of the 
environment list. */
static void	create_env_node(char *env_var_str, t_env **environment)
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
	add_env_node(var_name, var_value, environment);
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
		create_env_node(environ[i], &environment);
		i++;
	}
	return (environment);
}

/* show_env: displays the current environment variables to the user by calling 
parse_env, printing the environment list with print_env, and then freeing the 
environment list. */
int	show_env(char **env)
{
	t_env	*environment;

	environment = parse_env(env);
	print_env(environment);
	free_env_list(environment);
	return (NO_EXIT);
}

/* deprecated code */
/* int	show_env(void)
{
	env = environ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (NO_EXIT);
}
 */