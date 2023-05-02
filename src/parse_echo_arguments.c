/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:38:19 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/02 19:09:19 by abaiao-r         ###   ########.fr       */
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

char	**parse_arguments(char *string, char **args, size_t count)
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
			args[count - 1] = strndup(arg, string - arg);
			if (!args[count - 1])
			{
				free_memory(args, count - 1);
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

/* int	main(void)
{
    int i;
	char input[] = "Hello \"World is\" is a test.";
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
} */