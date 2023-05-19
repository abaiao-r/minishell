/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:42:20 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/19 23:58:04 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* This function is a helper function for parse_arguments. It parses a 
string for arguments and updates an argument structure. It handles quotes 
and whitespace, and adds the parsed argument to the parsed arguments 
if it is not empty. */
static void	handle_pipe(t_parsed *args, t_arg *arg, int *i)
{
	if (arg->arg_len > 0)
	{
		arg->arg[arg->arg_len++] = '\0';
		args->args[args->arg_index++] = arg->arg;
		if (!create_arg(args, arg))
			return ;
	}
	args->args[args->arg_index++] = ft_strdup("|");
	(*i)++;
}

/*Similar to handle_pipe(), but adds the double pipe symbol "||"
and increments the index by 2 since it occupies two characters. */
static void	handle_double_pipe(t_parsed *args, t_arg *arg, int *i)
{
	if (arg->arg_len > 0)
	{
		arg->arg[arg->arg_len++] = '\0';
		args->args[args->arg_index++] = arg->arg;
		if (!create_arg(args, arg))
			return ;
	}
	args->args[args->arg_index++] = ft_strdup("||");
	(*i)++;
	(*i)++;
}

/* Checks if the current character represents a pipe operator (| or ||).
If a pipe operator is found, it calls the appropriate function
(e.g., handle_pipe() for |) and returns true.
Otherwise, it returns false. */
bool	handle_piping(t_parsed *args, t_arg *arg, char *str, int *i)
{
	char	c;

	c = str[*i];
	if (!arg->in_quotes && c == '|' && *i + 1 < args->string_len && str[*i
			+ 1] == '|')
	{
		handle_double_pipe(args, arg, i);
		return (true);
	}
	else if (!arg->in_quotes && c == '|')
	{
		handle_pipe(args, arg, i);
		return (true);
	}
	return (false);
}
