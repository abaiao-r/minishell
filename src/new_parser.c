/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 00:15:08 by quackson          #+#    #+#             */
/*   Updated: 2023/06/13 15:13:39 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_input	*ft_lstlast_parser(t_input *lst)
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

void	ft_lstadd_back_parser(t_input **lst, t_input *new)
{
	t_input	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast_parser(*lst);
			last->next = new;
		}
		else
		{
			*lst = new;
		}
	}
	return ;
}

t_input	*new_node(char *str)
{
	t_input	*node;

	node = (t_input *)malloc(sizeof(t_input));
	node->token = ft_strdup(str);
	node->next = NULL;
	free(str);
	return (node);
}

void	add_node(t_input **head, char *str)
{
	t_input	*node;

	node = new_node(str);
	ft_lstadd_back_parser(head, node);
}

void	print_input(t_input *head)
{
	while (head)
	{
		printf("%s\n", (char *) head->token);
		head = head->next;
	}
}

void	free_list(t_input *head)
{
	t_input	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

//check if char in str is between quotes
int	is_between_quotes(char *input, int index)
{
	int		single_quote;
	int		double_quote;
	int		i;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (single_quote == 0 && double_quote == 0)
			{
				if (input[i] == '\'')
					single_quote = 1;
				else if (input[i] == '\"')
					double_quote = 1;
				if (i == index)
					return (-1);
			}
			else if (single_quote == 1 && input[i] == '\'')
			{
				if (i == index)
					return (-1);
				single_quote = 0;
			}
			else if (double_quote == 1 && input[i] == '\"')
			{
				double_quote = 0;
				if (i == index)
					return (-1);
			}
		}
		if (i == index)
			return (single_quote || double_quote);
	}
	printf("Error: is_between_quotes\n");
	return (0);
}

int	get_redirection_len(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	return (0);
}

int	has_redirection(char *str)
{
	int	i;
	int	symbol_len;

	symbol_len = 0;
	i = 0;
	while (str[i])
	{
		symbol_len = get_redirection_len(str + i);
		if (symbol_len)
			return (i);
		i++;
	}
	return (-1);
}

void	add_word(t_input **head, char *input, int start, int end)
{
	char	*word;
	t_input	*node;
	int		quote_flag;
	int		in_quotes;
	int		i;
	int		j;

	if (start == end)
		return ;
	//printf("sub len: %d %d\n", end - start, ft_strcmp(input + start, "\"\""));
	//printf("start: %d\n", start);
	//printf("end: %d\n", end);
	char *sub = ft_substr(input, start, end - start);
	//printf("sub: %s len:%ld\n", sub, ft_strlen(sub));
	free(sub);
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return ;
	i = 0;
	j = 0;
	quote_flag = 0;
	in_quotes = 0;
	while (input[start + i] && start + i < end)
	{
		in_quotes = is_between_quotes(input, start + i);

		if (in_quotes == 1)
			quote_flag = 1;
		if (in_quotes == 1 || in_quotes == 0)
		{
			word[j] = input[start + i];
			j++;
		}
		i++;
	}
	word[j] = '\0';
	node = new_node(word);
	node->within_quotes = quote_flag;
	ft_lstadd_back_parser(head, node);
}

int	get_word_len(char *input)
{
	int		len;
	char	*tmp;

	len = 0;
	// "hello"
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
	int len;
	t_input	*head;

	head = NULL;
	i = 0;
	len = 0;
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
		{
			len = get_word_len(input + i);
			if (len > 0 && !(len == 2 && (!ft_strncmp(input + i, "\"\"", 2) || !ft_strncmp(input + i, "\'\'", 2))))
				add_word(&head, input, i, i + len);
			i += len;
		}
	}
	if (!head)
		free_input_resources(minishell);
	return (head);
}
