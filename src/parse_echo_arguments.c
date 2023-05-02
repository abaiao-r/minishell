/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:38:19 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/02 19:46:08 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	compute_memory_needed(char *string)
{
	size_t	size;

	size = sizeof(char *);
	while (*string != '\0')
	{
		while (*string != '\0' && isspace(*string))
		{
			++string;
		}
		if (*string != '\0')
		{
			++size;
			while (*string != '\0' && !isspace(*string))
			{
				++size;
				++string;
			}
		}
	}
	return (size);
}

char	**allocate_memory(size_t size)
{
	return (malloc(size * sizeof(char *)));
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

/* char	**parse_arguments(char *string, char **args, size_t count)
{
	char	*arg;

	while (*string != '\0')
	{
		while (*string != '\0' && isspace(*string))
			++string;
		if (*string != '\0')
		{
			arg = string;
			++count;
			while (*string != '\0' && !isspace(*string))
				++string;
			args[count - 1] = ft_strndup(arg, string - arg);
			if (!args[count - 1])
			{
				free_memory(args, count - 1);
				return (NULL);
			}
		}
	}
	args[count] = NULL;
	return (args);
} */
int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
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
		while (*string != '\0' && isspace(*string))
			++string;
		if (*string != '\0')
		{
			arg = string;
			++count;
			if (is_quote(*string))
			{
				inside_quote = 1;
				quote_type = *string;
				++string;
			}
			while (*string != '\0')
			{
				if (inside_quote && *string == quote_type)
				{
					inside_quote = 0;
					quote_type = '\0';
					++string;
					break ;
				}
				else if (!inside_quote && isspace(*string))
				{
					++string;
					break ;
				}
				++string;
			}
			if (arg != string)
			{
				arg_str = strndup(arg, string - arg);
				if (!arg_str)
				{
					free_memory(args, count - 1);
					return (NULL);
				}
				if (is_quote(arg_str[0])
					&& arg_str[0] == arg_str[strlen(arg_str) - 1])
				{
					arg_str[strlen(arg_str) - 1] = '\0';
					++arg_str;
				}
				args[count - 1] = arg_str;
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
	args = allocate_memory(compute_memory_needed(string));
	if (!args)
	{
		return (NULL);
	}
	args = parse_arguments(string, args, count);
	if (!args)
	{
		return (NULL);
	}
	return (args);
}

int	main(void)
{
	int i;
	char input[] = "Hello \'World is is a test.";
	char **args = parse_echo_arguments(input);

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