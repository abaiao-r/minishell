/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:38:19 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/03 17:12:22 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v')
		return (1);
	else
		return (0);
}

void	ft_skip_whitespace(char **string_ptr)
{
	int	i;

	i = 0;
	while ((*string_ptr)[i] != '\0' && ft_isspace((*string_ptr)[i]))
	{
		++i;
	}
	*string_ptr += i;
}

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
	if (ft_is_quote(arg_str[0]) && arg_str[0] == arg_str[strlen(arg_str) - 1])
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
	while (*string != '\0')
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
		 ++string;
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

static size_t	compute_memory_needed(char *string)
{
	size_t	size;

	size = sizeof(char *);
	while (*string != '\0')
	{
		while (*string != '\0' && ft_isspace(*string))
		{
			++string;
		}
		if (*string != '\0')
		{
			++size;
			while (*string != '\0' && !ft_isspace(*string))
			{
				++size;
				++string;
			}
		}
	}
	return (size);
}

char	**parse_arguments(char *string, char **args, size_t count)
{
	char	*arg;
	int		inside_quote;
	char	quote_type;
	char	*arg_str;

	inside_quote = 0;
	quote_type = '\0';
	while (*string != '\0')
	{
		ft_skip_whitespace(&string);
		if (*string != '\0')
		{
			arg = string;
			++count;
			parse_quote(&string, &inside_quote, &quote_type);
			parse_string(&string, &inside_quote, &quote_type);
			arg_str = process_argument(arg, string, args, count);
			if (!arg_str)
			{
				return (NULL);
			}
		}
	}
	args[count] = NULL;
	return (args);
}

char	**parse_echo_arguments(char *string)
{
	size_t	count;
	char	**args;

	count = 0;
	args = NULL;
	args = malloc(compute_memory_needed(string));
	if (!args)
		return (NULL);
	args = parse_arguments(string, args, count);
	if (!args)
		return (NULL);
	return (args);
}

/* main to test char	**parse_echo_arguments(char *string)
to use this main you need few funtions of libft.h. 
the funtions need were pasted below this main */

int	main(void)
{
	int i;
	char input[] = "Hello World is ae a test.";
	char **args;

	args = parse_echo_arguments(input);
	if (!args)
	{
		fprintf(stderr, "Error: failed to parse input.\n");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (args[i] != NULL)
	{
		printf("Argument %d: %s\n", i, args[i]);
		i++;
	}
	free(args);
	return (EXIT_SUCCESS);
}