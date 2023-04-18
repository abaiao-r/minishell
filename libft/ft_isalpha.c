/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:05:20 by abaiao-r          #+#    #+#             */
/*   Updated: 2022/10/29 17:15:43 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z' ))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*int main(void)
{
	char c;
	c = 'Q';
	printf("\nResult when uppercase alphabet is passed: %d", ft_isalpha(c));

	c = 'q';
	printf("\nResult when lowercase alphabet is passed: %d", ft_isalpha(c));

	c='2';
	printf("\nResult when non-alphabetic character is passed: %d", ft_isalpha(c));

	return (0);
}*/