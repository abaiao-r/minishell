/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:06:39 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/19 23:52:32 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Similar to handle_pipe(), but adds the greater-than symbol ">"
and increments the index by 1.*/
static void	handle_greater(t_parsed *args, t_arg *arg, int *i)
{
	if (arg->arg_len > 0)
	{
		arg->arg[arg->arg_len++] = '\0';
		args->args[args->arg_index++] = arg->arg;
		if (!create_arg(args, arg))
			return ;
	}
	args->args[args->arg_index++] = ft_strdup(">");
	(*i)++;
}

/*Similar to handle_pipe(), but adds the double greater-than symbol ">>"
and increments the index by 2 since it occupies two characters. */
static void	handle_double_greater(t_parsed *args, t_arg *arg, int *i)
{
	if (arg->arg_len > 0)
	{
		arg->arg[arg->arg_len++] = '\0';
		args->args[args->arg_index++] = arg->arg;
		if (!create_arg(args, arg))
			return ;
	}
	args->args[args->arg_index++] = ft_strdup(">>");
	(*i)++;
	(*i)++;
}

/* Similar to handle_pipe(), but adds the less-than symbol "<"
and increments the index by 1. */
static void	handle_single_lesser(t_parsed *args, t_arg *arg, int *i)
{
	if (arg->arg_len > 0)
	{
		arg->arg[arg->arg_len++] = '\0';
		args->args[args->arg_index++] = arg->arg;
		if (!create_arg(args, arg))
			return ;
	}
	args->args[args->arg_index++] = ft_strdup("<");
	(*i)++;
}

/* Similar to handle_pipe(), but adds the double less-than symbol "<<"
and increments the index by 2 since it occupies two characters. */
static void	handle_double_lesser(t_parsed *args, t_arg *arg, int *i)
{
	if (arg->arg_len > 0)
	{
		arg->arg[arg->arg_len++] = '\0';
		args->args[args->arg_index++] = arg->arg;
		if (!create_arg(args, arg))
			return ;
	}
	args->args[args->arg_index++] = ft_strdup("<<");
	(*i)++;
	(*i)++;
}

/* Checks if the current character represents a redirection operator
(> or >> for output redirection, < or << for input redirection).
If a redirection operator is found, it calls the appropriate function
(e.g., handle_greater() for >) and returns true.
Otherwise, it returns false. */
bool	handle_redirection(t_parsed *args, t_arg *arg, char *str, int *i)
{
	char	c;

	c = str[*i];
	if (!arg->in_quotes && c == '>' && *i + 1 < args->string_len && str[*i
			+ 1] == '>')
		return (handle_double_greater(args, arg, i), true);
	else if (!arg->in_quotes && c == '>')
		return (handle_greater(args, arg, i), true);
	else if (!arg->in_quotes && c == '<' && *i + 1 < args->string_len && str[*i
			+ 1] == '<')
		return (handle_double_lesser(args, arg, i), true);
	else if (!arg->in_quotes && c == '<')
		return (handle_single_lesser(args, arg, i), true);
	return (false);
}
