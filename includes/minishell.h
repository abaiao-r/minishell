/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:10:00 by quackson          #+#    #+#             */
/*   Updated: 2023/04/21 16:11:24 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NO_FLAG 0
# define FLAG 1
# define PWD_SIZE 1024

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
void	exe_cmd(char **input, int num_tokens);
char	*ft__strchr(const char *s, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);

void	echo(char **input, int num_tokens);
void	echo_aux(char **args, int num_args, int flag);
void	pwd(void);
void	change_dir(char **input, int num_tokens);

#endif