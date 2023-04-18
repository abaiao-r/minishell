/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:11:35 by abaiao-r          #+#    #+#             */
/*   Updated: 2022/11/19 16:11:26 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
	{
		return (0);
	}
	while (lst != NULL)
	{
		if (!lst->next)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (lst);
}
/* int main(void)
{
	t_list *teste;
	teste = malloc(sizeof(t_list));
	teste -> content = "abc";
	teste -> next = malloc(sizeof(t_list));
	teste -> next -> content = "def";
	teste -> next -> next = NULL;
	teste = ft_lstlast(teste);
	printf("%s\n", (char *)teste->content);
} */