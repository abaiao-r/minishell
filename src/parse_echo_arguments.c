/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_echo_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:38:19 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/04 17:13:33 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int	ft_isquote(char c)
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

void	ft_skip_whitespace(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] != '\0' && ft_isspace((*str)[i]))
	{
		++i;
	}
	*str += i;
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

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
} */

/* utils | */

int	ft_quotes_are_closed(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	count_words_parser(char *str)
{
	int	i;
	int	wc;
	char c;

	wc = 0;
	i = 0;
	while (str[i++])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i] == '\"' || str[i] == '\'')
		{
			i++;
			c = str[i - 1];
			if (!ft_quotes_are_closed(&str[i], str[i - 1]))
				return (-1);
			wc++;
			while (str[i] != c)
				i++;
			i++;
		}
		else if (str[i] && (str[i] != ' ' || str[i] != '\t' || str[i] != '\n'))
			wc++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            i++;
	}
	return (wc);
}

void	remove_quotes(char *str)
{
    int i = 0;
    int j = 0;
    while (str[i])
    {
        if (str[i] != '\"' && str[i] != '\'')
        {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

char	**parse_echo_arguments(char *str)
{
    int		i;
    int		j;
    int		k;
    char	**out;
    bool	in_quote;

    i = 0;
    j = 0;
    k = 0;
    if (count_words_parser(str) == -1)
        return (0);
    out = (char **)malloc(sizeof(char *) * (count_words_parser(str) + 1));
    in_quote = false;
    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        {
            i++;
        }
        if (ft_isquote(str[i]))
        {
            in_quote = true;
            i++;
        }
        j = i;
        while (str[i] && ((in_quote && !ft_isquote(str[i])) || (!in_quote
                    && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')))
        {
            if (ft_isquote(str[i]))
            {
                i--;
                break ;
            }
            i++;
        }

        if (in_quote)
        {
            in_quote = false;
            i++;
        }
        if (i > j)
        {
            out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
            ft_strncpy(out[k], &str[j], i - j);
            remove_quotes(out[k]);
            k++;
        }
    }
    out[k] = NULL;
    return (out);
}

/* main to test char	**parse_echo_arguments(char *string)
to use this main you need few funtions of libft.h. 
the funtions need were pasted below this main */

/* int	main(void)
{
	int		i;
	char	input[] = "Hello \"World is\" ae a \'test. a\' fdsa";
	char	**args;

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
	free_memory(args, i);
	return (EXIT_SUCCESS);
} */
/* main to test count_words_parser*/
/* int main(void)
{
	char input[] = "Hello \"World is\" ae \'a test.\'";

	printf("%d", count_words_parser(input));
} */