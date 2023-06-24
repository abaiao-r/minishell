/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:21:02 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/24 13:16:30 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_cd(char *token)
{
	char	*error_tmp;
	char	*error;

	error_tmp = ft_strjoin(": '", token);
	error = ft_strjoin(error_tmp, ": No such file or directory\n");
	free(error_tmp);
	write(2, error, ft_strlen(error));
	free(error);
	g_minishell.minishell->exit_status = 1;
}

void	print_error_exit(char *token)
{
	char	*error_tmp;
	char	*error;

	error_tmp = ft_strjoin("bash: exit: ", token);
	error = ft_strjoin(error_tmp, ": numeric argument required\n");
	free(error_tmp);
	write(2, error, ft_strlen(error));
	free(error);
}
