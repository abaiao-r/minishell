/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 00:32:23 by quackson          #+#    #+#             */
/*   Updated: 2023/04/28 19:59:57 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_env_node(char *var_name, char *var_value, t_env **head)
{
	t_env	*env_node;

	env_node = malloc(sizeof(*env_node));
	env_node->var_name = var_name;
	env_node->var_value = var_value;
	env_node->next = NULL;
	ft_lstadd_back_env(head, env_node);
}

t_env	*parse_env(char **environ)
{
	t_env	*head;
	int		i;
	char	*var_name;
	size_t	var_name_len;
	char	*var_value;
	char	*var;
	char	*eq_pos;

	head = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		var = environ[i];
		eq_pos = ft_strchr(var, '=');
		if (eq_pos == NULL)
		{
			perror("Error");
			i++;
			continue ;
		}
		var_name_len = eq_pos - var;
		var_name = malloc(var_name_len + 1);
		ft_strncpy(var_name, var, var_name_len);
		var_name[var_name_len] = '\0';
		var_value = eq_pos + 1;
		add_env_node(var_name, var_value, &head);
		i++;
	}
	return (head);
}

void	print_env(t_env *head)
{
	t_env	*node;

	node = head;
	while (node != NULL)
	{
		printf("%s=%s\n", node->var_name, node->var_value);
		node = node->next;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*node;
	t_env	*next_node;

	node = head;
	while (node != NULL)
	{
		next_node = node->next;
		free(node->var_name);
		free(node);
		node = next_node;
	}
}

int	show_env(char **env)
{
	t_env		*head;

	head = parse_env(env);
	print_env(head);
	free_env_list(head);
	return (NO_EXIT);
}

/* int show_env(void)
{
    extern char **environ;
    char **env;
    char *var;
    char *eq_pos;
    char *var_name;
    char *var_value;
    t_env *head;
    t_env *env_node;
    t_env *node;
    int i;
	size_t		var_name_len;
	t_env		*next_node;
	extern char	**environ;
	char		**env;

	head = NULL;
    env = environ;
	i = 0;
    while (env[i] != NULL)
    {
        var = env[i];
        eq_pos = ft_strchr(var, '=');
        if (eq_pos == NULL)
        {
            perror("Error");
            i++;
            continue ;
        }
        var_name_len = eq_pos - var;
        var_name = malloc(var_name_len + 1);
        ft_strncpy(var_name, var, var_name_len);
        var_name[var_name_len] = '\0';
        var_value = eq_pos + 1;
        env_node = malloc(sizeof(*env_node));
        env_node->var_name = var_name;
        env_node->var_value = var_value;
		env_node->next = head;
        head = env_node;
        i++;
    }
    node = head;
    while (node != NULL)
    {
        printf("%s=%s\n", node->var_name, node->var_value);
        node = node->next;
    }
    node = head;
    while (node != NULL)
    {
        next_node = node->next;
        free(node->var_name);
        free(node);
        node = next_node;
    }
    return (0);
} */
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