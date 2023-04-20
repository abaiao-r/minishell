/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:10:00 by quackson          #+#    #+#             */
/*   Updated: 2023/04/20 15:58:43 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*ft_strncpy(char *s1, char *s2, int n);
int		count_words(char *str);
char	**ft_split(char *str, int *wc);
void	free_parsed(char **parsed);
void	exe_command(char **parsed);
char	*ft__strchr(const char *s, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);

#endif