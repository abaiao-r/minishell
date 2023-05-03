/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_arguments_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:17:29 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/03 13:22:19 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_memory(char **args, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	*parse_argument_string(char *arg_start, char *arg_end)
{
	char	*arg_str;

	arg_str = strndup(arg_start, arg_end - arg_start);
	if (!arg_str)
	{
		return (NULL);
	}
	if (ft_is_quote(arg_str[0]) && arg_str[0] == arg_str[strlen(arg_str)
			- 1])
	{
		arg_str[strlen(arg_str) - 1] = '\0';
		++arg_str;
	}
	return (arg_str);
}

char	*process_argument(char *arg, char *string, char **args, int count)
{
	char	*arg_str;

	arg_str = NULL;
	if (arg != string)
	{
		arg_str = parse_argument_string(arg, string);
		if (!arg_str)
		{
			free_memory(args, count - 1);
			return (NULL);
		}
		args[count - 1] = arg_str;
	}
	return (arg_str);
}

void	parse_string(char **string_ptr, int *inside_quote_ptr,
		char *quote_type_ptr)
{
	char	*string;
	int		inside_quote;
	char	quote_type;

	string = *string_ptr;
	inside_quote = *inside_quote_ptr;
	quote_type = *quote_type_ptr;
	while (*string++ != '\0')
	{
		if (inside_quote && *string == quote_type)
		{
			inside_quote = 0;
			quote_type = '\0';
			++string;
			break ;
		}
		else if (!inside_quote && ft_isspace(*string))
		{
			++string;
			break ;
		}
	}
	*string_ptr = string;
	*inside_quote_ptr = inside_quote;
	*quote_type_ptr = quote_type;
}

void	parse_quote(char **string_ptr, int *inside_quote_ptr,
		char *quote_type_ptr)
{
	char	*string;
	int		inside_quote;
	char	quote_type;

	string = *string_ptr;
	inside_quote = *inside_quote_ptr;
	quote_type = *quote_type_ptr;
	if (ft_is_quote(*string))
	{
		inside_quote = 1;
		quote_type = *string;
		++string;
	}
	*string_ptr = string;
	*inside_quote_ptr = inside_quote;
	*quote_type_ptr = quote_type;
}
