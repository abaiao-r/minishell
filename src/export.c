/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:58:38 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/24 03:07:27 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* print_error: This function takes a token as input and
generates an error message indicating that the token is 
not a valid identifier. The error message is written to the 
standard error stream. */
static void	print_error(char *token)
{
	char	*error_tmp;
	char	*error;

	error_tmp = ft_strjoin("export: '", token);
	error = ft_strjoin(error_tmp, "': not a valid identifier\n");
	free(error_tmp);
	write(2, error, ft_strlen(error));
	free(error);
}

/* check_token: This function checks if the first character
of the token is a valid identifier. If the token starts with
a non-alphabetic character (except underscore) or a digit, it
sets a flag and calls the print_error function to display the
error message. It returns 1 if the token is invalid, otherwise 0. */
static int	check_token(char *token, int *flag)
{
	if (((ft_isalpha(token[0]) == 0) && (token[0] != '_'))
		|| ft_isdigit(token[0]) == 1)
	{
		*flag = 1;
		print_error(token);
		return (1);
	}
	return (0);
}

/* check_token_characters: This function checks if the token
contains any invalid characters. If the token contains any
non-alphanumeric characters (except underscore), it sets a flag
and calls the print_error function to display the error message.
It returns 1 if the token is invalid, otherwise 0. */
static int	check_token_characters(char *token, int *flag)
{
	int	j;

	j = 1;
	while (token[j] && token[j] != '=')
	{
		if (ft_isalnum(token[j]) == 0 && token[j] != '_')
		{
			*flag = 1;
			print_error(token);
			return (1);
		}
		j++;
	}
	return (0);
}

/* process_export_tokens: This function processes the tokens
passed to the export command. It iterates through the tokens
and calls the check_token and check_token_characters functions
to check if the tokens are valid. If the tokens are valid, it
calls the parse_input_export function to parse the tokens and
update the environment variables. If the tokens are invalid, it
sets a flag and continues to the next token. */
static void	process_export_tokens(t_minishell **minishell, int *flag, int *i)
{
	char	*find_var;
	char	*new_value;
	int		flag_equal;

	(*i) = 1;
	while ((*minishell)->tokens[(*i)]
		&& !is_redirection((*minishell)->tokens[(*i)]))
	{
		if (check_token((*minishell)->tokens[(*i)], flag)
			|| check_token_characters((*minishell)->tokens[(*i)], flag))
		{
			(*i)++;
			continue ;
		}
		flag_equal = parse_input_export((*minishell)->tokens[(*i)], &find_var,
				&new_value);
		if (!update_env_name(&(*minishell)->environment, find_var, new_value,
				flag_equal))
			create_env_node((*minishell)->tokens[(*i)], 100,
				&(*minishell)->environment);
		free(find_var);
		(*i)++;
	}
}

/* export: This function is the entry point for the export command.
It takes the number of tokens and the minishell structure as input.
If the number of tokens is 1, it calls the show_export function to
display the environment variables. If the number of tokens is greater
than 1, it calls the process_export_tokens function to process the
tokens and update the environment variables. It returns NO_EXIT if
the command is successful, otherwise it returns 1. */
int	export(int num_tokens, t_minishell **minishell)
{
	int	flag;
	int	i;

	flag = 0;
	if (num_tokens == 1)
	{
		(*minishell)->exit_status = 0;
		return (show_export(&(*minishell)->environment));
	}
	process_export_tokens(minishell, &flag, &i);
	if (flag == 1)
		(*minishell)->exit_status = 1;
	else
		(*minishell)->exit_status = 0;
	return (NO_EXIT);
}
