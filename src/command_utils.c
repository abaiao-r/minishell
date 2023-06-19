/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:24:17 by quackson          #+#    #+#             */
/*   Updated: 2023/06/19 15:16:00 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * The function finds the executable path of a given command by searching through the directories
 * listed in the PATH environment variable.
 * 
 * param cmd The command to search for in the system's PATH directories.
 * 
 * return The function `find_executable` returns a pointer to a string that represents the path to the
 * executable file for the given command `cmd`. If the command is not found or cannot be executed, the
 * function returns `NULL`.
 */

char	*find_executable(char *cmd, t_env **environment)
{
	char	*path;
	char	*path_end;
	char	*executable;

	path = ft_getenv("PATH", *environment);
	if (!path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, X_OK))
			return (cmd);
		return (NULL);
	}
	while (*path)
	{
		path_end = ft_strchr(path, ':');
		if (!path_end)
			path_end = path + ft_strlen(path);
		executable = malloc(path_end - path + ft_strlen(cmd) + 2);
		if (!executable)
			return (NULL);
		ft_strncpy(executable, path, path_end - path);
		executable[path_end - path] = '/';
		ft_strcpy(executable + (path_end - path) + 1, cmd);
		//printf("executable: %s\n", executable);
		if (!access(executable, X_OK))
			return (executable);
		free(executable);
		path = path_end;
		if (*path == ':')
			path++;
	}
	return (NULL);
}

/* Isto e uma tentative de pegar num conjunto de strings
 e extrair aquelas que estao antes do proximo simbolo "|" ou ">", etc
 Nao esta funcional
 */
char	**get_cmd(char **input, char c)
{
	int		i;
	int		n;
	char	**cmd;

	i = 0;
	while (input[i] && input[i][0] != c)
		i++;
	if (!input[i])
		return (input);
	n = i;
	i = 0;
	cmd = malloc(n * sizeof(char *));
	if (!cmd)
		return (NULL);
	while (input[i] && input[i][0] != c)
	{
		cmd[i] = input[i];
		i++;
	}
	return (cmd);
}

int	exe_shell_cmd(char **args, int num_tokens, t_env **environment)
{
	char	**bash_args;
	int i;

	if (!args || !*args)
		return (NO_EXIT);
	bash_args = malloc(sizeof(char *) * (num_tokens + 1));
	if (!bash_args)
		return (NO_EXIT);
	i = 0;
	while (i < num_tokens)
	{
		bash_args[i] = args[i];
		i++;
	}
	bash_args[i] = NULL;
	bash_args[0] = find_executable(bash_args[0], environment);
	if (!bash_args[0])
	{
		free(bash_args);
		perror("Command not found");
		exit(127);
	}
	if (access(bash_args[0], X_OK) == 0)
	{
		execve(bash_args[0], bash_args, NULL);
		perror("execve failed");
		exit(126);
	}
	free(bash_args);
	perror("Command not found");
	exit(127);
}

int	exe_cmd(char **tokens, int num_tokens, t_minishell *minishell)
{
	if (!tokens || !*tokens || num_tokens <= 0)
		return (-1);
	if (ft_strcmp(tokens[0], "echo") == 0)
		return (echo(&(minishell), num_tokens));
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
		return (EXIT);
	else
		return (-1);
}
