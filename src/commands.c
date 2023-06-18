/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:12:33 by quackson          #+#    #+#             */
/*   Updated: 2023/06/18 20:02:14 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_aux(char **args, int num_args, int flag)
{
	int	i;

	i = 0;
	while (args[i] && i < num_args)
	{
		printf("%s", args[i]);
		if (i + 1 != num_args)
			printf(" ");
		i++;
	}
	if (flag == NO_FLAG)
		printf("\n");
}

int	echo(t_minishell **minishell, int num_tokens)
{
	if (num_tokens == 1)
		printf("\n");
	else if (num_tokens > 1 && ft_strcmp((*minishell)->tokens[1], "-n") != 0)
		echo_aux((*minishell)->tokens + 1, num_tokens - 1, NO_FLAG);
	else if (num_tokens > 2 && ft_strcmp((*minishell)->tokens[1], "-n") == 0)
		echo_aux((*minishell)->tokens + 2, num_tokens - 2, FLAG);
	(*minishell)->exit_status = 0;
	return (NO_EXIT);
}

int	pwd(t_minishell **minishell)
{
	char	cwd[PWD_SIZE];

	if (getcwd(cwd, sizeof(cwd)))
	{
		(*minishell)->exit_status = 0;
		printf("%s\n", cwd);
	}
	else
	{
		(*minishell)->exit_status = 1;
		perror("pwd error");
	}
	return (NO_EXIT);
}

int	change_dir(char **input, int num_tokens, t_env **environment)
{
	char	*dir_path;
	char	*home_path;

	if (num_tokens > 2)
	{
		printf("bash: cd: too many arguments\n");
		return (NO_EXIT);
	}
	home_path = ft_getenv("HOME", *environment);
	if (home_path == NULL)
	{
		printf("Could not get home directory path\n");
		return (NO_EXIT);
	}
	if (num_tokens == 1 || (num_tokens == 2 && (ft_strcmp(input[1], "~") == 0
				|| ft_strcmp(input[1], "~/") == 0)))
		dir_path = home_path;
	else
		dir_path = input[1];
	if (chdir(dir_path) != 0)
		printf("bash: cd: %s: No such file or directory\n", dir_path);
	return (NO_EXIT);
}
