/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:58:38 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/28 22:09:05 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_error(char *input)
{
	printf("export: not an identifier: %s\n", input);
}

int	export(char **input, int num_tokens, char **env)
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
			ft_putenv(input, env);
		i++;
	}
	return (NO_EXIT);
}
