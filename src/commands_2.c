/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:46:39 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/24 18:12:13 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_error(char *input)
{
	printf("export: not an identifier: %s\n", input);
}

int	export(char **input, int num_tokens)
{
	int i;
	int output;

	i = 0;
	output = 0;
	/* if (num_tokens == 0)
        return() */
	while (input[i])
	{
		if (!ft_isalpha(input[i][0]) && input[i][0] != '_')
			output = export_error(input[i]);
		else if (str_alnum(input[i]))
			output = export_error(input[i]);
		else if (ft_strchr(input[i], '='))
			ft_putenv(input[i]);
		i++;
	}
	return (output);
}
