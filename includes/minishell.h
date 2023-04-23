/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:34:43 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/23 23:14:27 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NO_FLAG 0
# define FLAG 1
# define PWD_SIZE 1024

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* commands.c */
void	echo_aux(char **args, int num_args, int flag);
void	echo(char **input, int num_tokens);
void	pwd(void);
void	change_dir(char **input, int num_tokens);

/* command_utils.c */
char	*find_executable(char *cmd);
char	**get_cmd(char **input, char c);
void	exe_cmd(char **input, int num_tokens);
void	exe_command(char **parsed);

/* print_prompt.c */
char	*print_prompt(void);

/* utils_1.c */
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
void	free_parsed(char **parsed);

/* utils_2.c */
int		count_words(char *str);
char	*ft_strncpy(char *s1, char *s2, size_t n);
char	**ft_split_default(char *str);

#endif
