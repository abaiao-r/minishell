/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:11:44 by andrefranci       #+#    #+#             */
/*   Updated: 2023/06/08 16:55:13 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

char *ft_getenv(const char *name, t_env *environment)
{
    t_env *temp;
    
    temp = environment;
    while (temp)
    {
        if (ft_strcmp(temp->var_name, name) == 0)
            return(temp->var_value);
        temp = temp->next;
    }
    return(NULL);
}

/* main to test ft_get_env */
/* int main(void)
{
    t_env *env1 = malloc(sizeof(t_env));
    env1->var_name = "VAR1";
    env1->var_value = "Value1";
    env1->rank = 1;
    
    t_env *env2 = malloc(sizeof(t_env));
    env2->var_name = "VAR2";
    env2->var_value = "Value2";
    env2->rank = 2;
    
    t_env *env3 = malloc(sizeof(t_env));
    env3->var_name = "VAR3";
    env3->var_value = "Value3";
    env3->rank = 3;
    
    env1->next = env2;
    env2->next = env3;
    env3->next = NULL;
    
    const char *name = "VAR2";
    char *value = ft_getenv(name, env1);
    
    if (value != NULL)
        printf("Value for %s: %s\n", name, value);
    else
        printf("Variable %s not found.\n", name);
    
    free(env1);
    free(env2);
    free(env3);
    
    return (0);
} */