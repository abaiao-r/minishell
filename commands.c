/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:12:33 by quackson          #+#    #+#             */
/*   Updated: 2023/04/22 13:45:51 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_aux(char **args, int num_args, int flag)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (i + 1 != num_args)
			printf(" ");
		i++;
	}
	if (flag == NO_FLAG)
		printf("\n");
}

void	echo(char **input, int num_tokens)
{
	if (num_tokens == 1)
		printf("\n");
	else if (num_tokens > 1 && ft_strcmp(input[1], "-n") != 0)
		echo_aux(input + 1, num_tokens - 1, NO_FLAG);
	else if (num_tokens > 2 && ft_strcmp(input[1], "-n") == 0)
		echo_aux(input + 2, num_tokens - 2, FLAG);
}

void	pwd(void)
{
	char	cwd[PWD_SIZE];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
	{
		perror("pwd error");
		return ;
	}
	return ;
}

void	change_dir(char **input, int num_tokens)
{
	char	*dir_path;
	char	*home_path;

	if (num_tokens > 2)
		return ;
	home_path = getenv("HOME"); // get the path of the user's home directory
	if (home_path == NULL)
	{
		printf("Could not get home directory path\n");
		return ;
	}
	if (num_tokens == 1 || (num_tokens == 2 && ft_strcmp(input[1], "~") == 0
			&& ft_strcmp(input[1], "~/")))
		dir_path = home_path;
	else
		dir_path = input[1];
	chdir(dir_path);
}