/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:38:11 by quackson          #+#    #+#             */
/*   Updated: 2023/05/01 00:26:05 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* char	*find_executable(char *cmd)
{
	char	*path;
	char	*path_end;
	char	*executable;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	path = path;
	while (*path)
	{
		path_end = ft_strchr(path, ':');
		if (!path_end)
			path_end = path + ft_strlen(path);
		executable = malloc(path_end - path + ft_strlen(cmd) + 2);
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

Apenas executa um comando. Ainda nao aceita redirecionamento de input/output
void	exe_executable(char **input)
{
	pid_t	pid;
	int		status;
	char	*executable;

	// Procura o comando
	executable = find_executable(input[0]);
	if (executable == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", input[0]);
		return ;
	}
	//execute_pipe(input);
	pid = fork();
	if (pid == 0)
	{
		// child process
		execve(executable, input, NULL);
		// if execve returns, an error occurred
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		// parent process
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
} */

/* int	exe_executable(char *input)
{
	char	*args[2];
	char	*env[1];
	int		fd[2];
	pid_t	pid;

	printf("Executing another program...\n");
	args[0] = input;
	args[1] = NULL;
	env[0] = NULL;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		execve(args[0], args, env);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		close(fd[0]);
	}
	printf("Program executed.\n");
	return (NO_EXIT);
}
 */