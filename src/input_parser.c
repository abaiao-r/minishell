/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:15:08 by quackson          #+#    #+#             */
/*   Updated: 2023/06/19 15:54:50 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	new_parse_args_aux(t_input **head, char *input, int *i)
{
	int	len;

	len = get_word_len(input + *i);
	if (len > 0)
		add_word(head, input, *i, *i + len);
	*i += len;
}

int	get_word_len(char *input)
{
	int		len;
	char	*tmp;

	len = 0;
	while (*input && !ft_isspace(*input) && !get_redirection_len(input))
	{
		if (*input == '\'' || *input == '\"')
		{
			tmp = ft_strchr(input + 1, *input);
			len += tmp - input + 1;
			input = tmp + 1;
		}
		else
		{
			len++;
			input++;
		}
	}
	return (len);
}

t_input	*new_parse_arguments(char *input, t_minishell *minishell)
{
	int		i;
	t_input	*head;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		else if (get_redirection_len(input + i))
		{
			add_word(&head, input, i, i + get_redirection_len(input + i));
			i += get_redirection_len(input + i);
		}
		else
			new_parse_args_aux(&head, input, &i);
	}
	if (!head)
		free_input_resources(minishell);
	return (head);
}