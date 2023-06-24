/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:21:02 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/24 18:16:41 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  print_error_cd: prints the error message for cd. */
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

/*  print_error_exit: prints the error message for exit. */
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

/* show_quotes_error: prints the error message for unclosed quotes.
Returns 0. */
int	show_quotes_error(void)
{
	printf("Error: unclosed quotes\n");
	return (0);
}

/* show_special_char_error: prints the error message for special characters.
Returns 0. */
int	show_special_char_error(char c)
{
	printf("bash: syntax error near unexpected token \'%c\'\n", c);
	return (0);
}
