/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:58:18 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/05 17:20:57 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* int ft_setenv(const char* name, const char* value, int overwrite)
{
    if (!name || !value) {
        return -1;
    }

    size_t name_len = ft_strlen(name);
    size_t value_len = ft_strlen(value);

    char* new_var = malloc(name_len + value_len + 2);
    if (!new_var) {
        return -1;
    }
    ft_memcpy(new_var, name, name_len);
    new_var[name_len] = '=';
    ft_memcpy(new_var + name_len + 1, value, value_len);
    new_var[name_len + value_len + 1] = '\0';

    char* existing_var = getenv(name);
    if (existing_var && !overwrite) {
        free(new_var);
        return 0;
    }

    int ret = ft_setenv(name, value, overwrite);
    if (ret != 0) {
        free(new_var);
        return -1;
    }

    return 0;
} */