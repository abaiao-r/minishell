/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:25:13 by abaiao-r          #+#    #+#             */
/*   Updated: 2022/11/19 16:11:56 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*connect;

	connect = (t_list *)malloc(sizeof(t_list));
	if (!connect)
	{
		return (NULL);
	}
	connect->content = (void *)content;
	connect->next = NULL;
	return (connect);
}

/* int main(void)
{
	char str[] = "teste123teste";
	t_list *teste;
	teste = ft_lstnew((void *)str);
	printf("\n%s\n", (char *)teste->content);
} */