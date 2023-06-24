/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:12:33 by quackson          #+#    #+#             */
/*   Updated: 2023/06/24 18:06:03 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* echo_aux: prints the arguments of echo. If flag is 0, it prints a new line
at the end. If flag is 1, it does not print a new line at the end. */
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

/* echo: prints the arguments of echo. If flag is 0, it prints a new line
at the end. If flag is 1, it does not print a new line at the end. */
int	echo(t_minishell **minishell, char **tokens, int num_tokens)
{
	if (num_tokens == 1)
		printf("\n");
	else if (num_tokens > 1 && ft_strcmp(tokens[1], "-n") != 0)
		echo_aux(tokens + 1, num_tokens - 1, NO_FLAG);
	else if (num_tokens > 2 && ft_strcmp(tokens[1], "-n") == 0)
		echo_aux(tokens + 2, num_tokens - 2, FLAG);
	(*minishell)->exit_status = 0;
	return (NO_EXIT);
}

/* pwd: prints the current working directory. */
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

/* change_dir: changes the current working directory to the given path. If
the given path is NULL, it changes the current working directory to the
home directory. */
int	change_dir(char **input, int num_tokens, t_env **environment)
{
	char	*dir_path;
	char	*home_path;

	if (num_tokens > 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		g_minishell.minishell->exit_status = 1;
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
		print_error_cd(dir_path);
	return (NO_EXIT);
}

/* exe_cmd: executes the given command. If the command is a built-in command,
it executes it and returns 0. If the command is not a built-in command, it
returns -1. */
int	exe_cmd(char **tokens, int num_tokens, t_minishell *minishell)
{
	if (!tokens || !*tokens || num_tokens <= 0)
		return (-1);
	if (ft_strcmp(tokens[0], "echo") == 0)
		return (echo(&(minishell), tokens, num_tokens));
	else if (ft_strcmp(tokens[0], "cd") == 0)
		return (change_dir(tokens, num_tokens, &(minishell->environment)));
	else if (ft_strcmp(tokens[0], "pwd") == 0)
		return (pwd(&(minishell)));
	else if (ft_strcmp(tokens[0], "export") == 0)
		return (export(num_tokens, &(minishell)));
	else if (ft_strcmp(tokens[0], "unset") == 0)
		return (ft_unset(num_tokens, &(minishell)));
	else if ((ft_strcmp(tokens[0], "env") == 0))
		return (show_env(&(minishell), num_tokens));
	else if (ft_strcmp(tokens[0], "exit") == 0)
		return (ft_exit(minishell, tokens, num_tokens));
	else
		return (-1);
}
