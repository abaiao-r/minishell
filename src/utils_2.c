
#include "../includes/minishell.h"

char	*ft_strncpy(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
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

static int	ft_find_word(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	return (i);
}

static int	ft_find_end(char *str, int i)
{
	while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
		i++;
	return (i);
}

char	**ft_split_default(char *str)
{
	int		i;
	int		j;
	int		k;
	int		wc;
	char	**out;

	i = 0;
	j = 0;
	k = 0;
	wc = count_words(str);
	out = (char **)malloc(sizeof(char *) * (wc + 1));
	while (str[i])
	{
		j = ft_find_word(str, i);
		i = ft_find_end(str, j);
		if (i > j)
		{
			out[k] = NULL;
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}

/* main para testar o ft_split_default */
/* int	main(void)
{
	char str[] = "  andre francisco i ";
	int i;
	char **split;

	i = 0;
	split = ft_split_default(str);
	while (i < count_words(str))
	{
		printf("%s\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
} */
