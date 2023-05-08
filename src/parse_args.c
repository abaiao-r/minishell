/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:31:23 by quackson          #+#    #+#             */
/*   Updated: 2023/05/08 21:48:25 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define MAX_ARGS 1024

typedef struct s_parsed
{
	char	**args;
	int		arg_index;
	int		string_len;
}	t_parsed;

typedef struct s_arg
{
	char	*arg;
	int		arg_len;
	int		in_quotes;
	char	quote_type;
}	t_arg;

static int	create_parsed(t_parsed *parsed, char *str)
{
	parsed->args = malloc(MAX_ARGS * sizeof(char *));
	if (!parsed->args)
		return (0);
	parsed->arg_index = 0;
	parsed->string_len = ft_strlen(str);
	return (1);
}

static int	create_arg(t_parsed *parsed_args, t_arg *arg)
{
	arg->arg = malloc(parsed_args->string_len * sizeof(char));
	if (!arg->arg)
		return (0);
	arg->arg_len = 0;
	arg->in_quotes = 0;
	arg->quote_type = '\0';
	return (1);
}

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
			*i = *i + 1;
			continue ;
		}
		if (arg->in_quotes && c == arg->quote_type)
		{
			arg->in_quotes = 0;
			arg->quote_type = '\0';
			*i = *i + 1;
			continue ;
		}
		if (!arg->in_quotes && isspace(c))
			break ;
		arg->arg[(arg->arg_len)++] = c;
		*i = *i + 1;
	}
}

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
			return (NULL);
		while (i < args.string_len && isspace(string[i]))
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
