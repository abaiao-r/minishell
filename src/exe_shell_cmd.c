/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_shell_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:24:17 by quackson          #+#    #+#             */
/*   Updated: 2023/06/22 23:07:37 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *cmd, char *path)
{
	char	*path_end;
	char	*executable;

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
		if (!access(executable, X_OK))
			return (executable);
		free(executable);
		path = path_end;
		if (*path == ':')
			path++;
	}
	return (NULL);
}

char	*find_executable(char *cmd, t_env **environment)
{
	char	*path;

	path = ft_getenv("PATH", *environment);
	if (!path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, X_OK))
			return (cmd);
		return (NULL);
	}
	return (get_path(cmd, path));
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

int	exe_bash_args(char **bash_args, t_env **environment, int i)
{
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

int	exe_shell_cmd(char **args, int num_tokens, t_env **environment)
{
	char	**bash_args;
	int		i;

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
	return (exe_bash_args(bash_args, environment, i));
	exit(127);
}
