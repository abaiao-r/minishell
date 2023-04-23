
#include "../includes/minishell.h"

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
	return (s1);
}

int	ft_count_words(char *str)
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

/* static int	ft_find_word(char *str, int i)
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
} */


char	**ft_split_default(char *str)
{
	int		i;
	int		j;
	char	**split;
	int		count_words;
	int		start;
	int		end;

	count_words = ft_count_words(str);
	split = (char **)malloc(sizeof(char *) * (count_words + 1));
	i = 0;
	start = -1;
	j = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (!(str[i] == ' ' || str[i] == '\t') && (start == -1))
		{
			start = i;
		}
		if ((!(str[i] == ' ' || str[i] == '\t')) && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
		{
			end = i;
			split[j] = (char *)malloc(sizeof(char) * (end - start + 2));
			ft_strncpy(split[j], &str[start], end - start + 1);
            start = -1;
            j++;
		}
		i++;
	}
	split[j] = '\0';
	return (split);
}
/* main para testar o ft_split_default */
/* int	main(void)
{
	char str[] = "  andre francisco i ";
	int i;
	char **split;

	i = 0;
	split = ft_split_default(str);
	while (i < ft_Scount_words(str))
	{
		printf("%s\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
} */
