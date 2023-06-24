/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_shell_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedgonca <pedgonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:24:17 by quackson          #+#    #+#             */
/*   Updated: 2023/06/24 19:22:22 by pedgonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* get_path: returns the path of the executable.
Tries to find the executable file for the command in 
the paths. It iterates through each path, constructs
the full path by concatenating the path and the command name,
and checks if the constructed path is a valid executable file.
If a valid executable is found, it returns the dynamically
allocated executable path; otherwise, it returns NULL. */
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

/* find_executable: returns the path of the executable.
If the command contains a slash, it checks if the command
is a valid executable file. If it is, it returns the command;
otherwise, it returns NULL.
If the command does not contain a slash, it calls get_path. */
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

/* exe_bash_args: executes the command.
It assigns the first argument to the executable path.
If the executable path is NULL, it frees the arguments,
prints the error message and exits the program.
If the executable path is valid, it executes the command. */
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

/* exe_shell_cmd: executes the command.
It allocates memory for the arguments, copies the arguments
to the allocated memory and calls exe_bash_args. */
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
