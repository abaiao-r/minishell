/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:09:22 by quackson          #+#    #+#             */
/*   Updated: 2023/04/29 10:21:59 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*d;

	d = dest;
	while (*src)
	{
		*d++ = *src++;
	}
	*d = '\0';
	return (dest);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((const unsigned char) s1[i] - (const unsigned char) s2[i]);
}

void	free_parsed(char **parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		free(parsed[i]);
		i++;
	}
	free(parsed[i]);
	free(parsed);
}
