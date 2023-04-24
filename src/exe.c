/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:38:11 by quackson          #+#    #+#             */
/*   Updated: 2023/04/24 17:48:06 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exe_executable(char *input)
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
