/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:31:23 by quackson          #+#    #+#             */
/*   Updated: 2023/05/19 18:51:40 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* This function initializes a parsed structure with a given string. 
It allocates memory for the parsed arguments and sets the initial 
argument index. */
static int	create_parsed(t_parsed *parsed, char *str)
{
	parsed->args = (char **)malloc((MAX_ARGS + 1) * sizeof(char *));
	if (!parsed->args)
		return (0);
	parsed->args[MAX_ARGS] = 0;
	parsed->arg_index = 0;
	parsed->string_len = ft_strlen(str);
	return (1);
}

/* This function initializes an argument structure. It allocates memory for 
the argument string, sets the initial argument length, and initializes the 
quote type. */
static int	create_arg(t_parsed *parsed_args, t_arg *arg)
{
	arg->arg = malloc((parsed_args->string_len + 1) * sizeof(char));
	if (!arg->arg)
		return (0);
	arg->arg_len = 0;
	arg->in_quotes = 0;
	arg->quote_type = '\0';
	return (1);
}

/* This function is a helper function for parse_arguments. It parses a 
string for arguments and updates an argument structure. It handles quotes 
and whitespace, and adds the parsed argument to the parsed arguments 
if it is not empty. */
static void	parse_aux(t_parsed *args, t_arg *arg, char *str, int *i)
{
	char	c;

	while (*i < args->string_len && arg->arg_len < args->string_len
		&& args->arg_index < MAX_ARGS)
	{
		c = str[*i];
		if (!arg->in_quotes && (c == '\'' || c == '\"'))
		{
			arg->in_quotes = 1;
			arg->quote_type = c;
			(*i)++;
			continue ;
		}
		if (arg->in_quotes && c == arg->quote_type)
		{
			arg->in_quotes = 0;
			arg->quote_type = '\0';
			(*i)++;
			continue ;
		}
		if (!arg->in_quotes && ft_isspace(c))
			break ;
		if (!arg->in_quotes && c == '>' && *i + 1 < args->string_len && str[*i + 1] == '>')
		{
			// Handle ">>" as a single token
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
			continue;
		}
		if (!arg->in_quotes && c == '>')
        {
            // Handle ">" as a single token
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len++] = '\0';
                args->args[args->arg_index++] = arg->arg;
                if (!create_arg(args, arg))
                    return;
            }
            args->args[args->arg_index++] = ft_strdup(">");
            (*i)++;
            continue;
        }
		if (!arg->in_quotes && c == '|' && *i + 1 < args->string_len && str[*i + 1] == '|')
        {
            // Handle "|" as a single token
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len++] = '\0';
                args->args[args->arg_index++] = arg->arg;
                if (!create_arg(args, arg))
                    return;
            }
            args->args[args->arg_index++] = ft_strdup("||");
            (*i)++;
            continue;
        }
		if (!arg->in_quotes && c == '|')
        {
            // Handle "|" as a single token
            if (arg->arg_len > 0)
            {
                arg->arg[arg->arg_len++] = '\0';
                args->args[args->arg_index++] = arg->arg;
                if (!create_arg(args, arg))
                    return;
            }
            args->args[args->arg_index++] = ft_strdup("|");
            (*i)++;
            continue;
        }
		arg->arg[arg->arg_len++] = c;
		(*i)++;
	}
}

/* This is the main function for parsing arguments from a string.
It initializes the args struct, creates an iterator i, and starts 
a loop to process the string. Inside the loop, it creates a new arg 
struct, skips leading spaces, calls parse_aux to extract the argument 
from the string, and stores it in the args array. Finally, it sets the 
last element of the args array to NULL and returns the array of parsed 
arguments. */
char	**parse_arguments(char *string)
{
	int			i;
	t_parsed	args;
	t_arg		arg;

	if (!create_parsed(&args, string))
		return (NULL);
	i = 0;
	while (i < args.string_len && args.arg_index < MAX_ARGS)
	{
		if (!create_arg(&args, &arg))
		{
			free(args.args);
			return (NULL);
		}
		while (i < args.string_len && ft_isspace(string[i]))
			i++;
		parse_aux(&args, &arg, string, &i);
		if (arg.arg_len > 0)
		{
			arg.arg[arg.arg_len] = '\0';
			args.args[args.arg_index++] = arg.arg;
		}
		else
			free(arg.arg);
	}
	args.args[args.arg_index] = NULL;
	return (args.args);
}
