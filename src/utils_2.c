/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:06:34 by quackson          #+#    #+#             */
/*   Updated: 2023/05/02 19:16:53 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

int	count_words(char *str)
{
	int	i;
	int	wc;

	wc = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
	}
	return (wc);
}

char	**ft_split_default(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**out;

	i = 0;
	j = 0;
	k = 0;
	out = (char **)malloc(sizeof(char *) * (count_words(str) + 1));
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		j = i;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}

int	show_cmd_error(char *str)
{
	printf("%s: command not found\n", str);
	return (NO_EXIT);
}

int	show_special_char_error(char c)
{
	printf("bash: syntax error near unexpected token \'%c\'\n", c);
	return (0);
}

int	show_quotes_error(void)
{
	printf("Error: unclosed quotes\n");
	return (0);
}

int	is_valid_input(char *input)
{
	char	stack[1024];
	int		stack_size;
	int		i;

	i = -1;
	stack_size = 0;
	while (input[++i])
	{
		if (input[i] == ';' || input[i] == '\\')
			return (show_special_char_error(input[i]));
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (stack_size != 0 && stack[stack_size - 1] == input[i])
				stack_size--;
			else
			{
				stack_size++;
				stack[stack_size - 1] = input[i];
			}
		}
	}
	if (stack_size != 0)
		return (show_quotes_error());
	return (1);
}

#define MAX_ARGS 1024

char** parse_echo_arguments(char* string)
{
    char **args = malloc(MAX_ARGS * sizeof(char *));
    int arg_index = 0;
    int string_len = ft_strlen(string);
    int i = 0;
    
    while (i < string_len && arg_index < MAX_ARGS) {
        char *arg = malloc(string_len * sizeof(char));
        int arg_len = 0;
        int in_quotes = 0;
        char quote_type = '\0';
        
        while (i < string_len && isspace(string[i])) {
            i++;
        }
        
        while (i < string_len && arg_len < string_len && arg_index < MAX_ARGS) {
            char c = string[i];
            
            if (!in_quotes && (c == '\'' || c == '\"')) {
                in_quotes = 1;
                quote_type = c;
                i++;
                continue;
            }
            
            if (in_quotes && c == quote_type) {
                in_quotes = 0;
                quote_type = '\0';
                i++;
                continue;
            }
            
            if (!in_quotes && isspace(c)) {
                break;
            }
            
            arg[arg_len++] = c;
            i++;
        }
        
        if (arg_len > 0) {
            arg[arg_len] = '\0';
            args[arg_index++] = arg;
        } else {
            free(arg);
        }
    }
    
    args[arg_index] = NULL;
    
    return args;

}

/* main to test parse_echo_arguments */
/* int main(void)
{
    char input[] = "Hello \"world, this\" is a test.";
    char **args = parse_echo_arguments(input);
    if (!args)
    {
        fprintf(stderr, "Error: failed to parse input.\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; args[i] != NULL; i++)
    {
        printf("Argument %d: %s\n", i, args[i]);
    }
    free(args);
    return EXIT_SUCCESS;
} */

/* main para testar o ft_split_default */
/* int	main(void)
{
	char str[] = "  andre francisco i ";
	int i;
	char **split;

	int wc = count_words(str);
	split = ft_split_default(str);
	i = 0;
	while (i < wc)
	{
		printf("%s\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
} */
