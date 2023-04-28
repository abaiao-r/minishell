/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:34:43 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/04/28 16:40:03 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NO_FLAG 0
# define FLAG 1
# define PWD_SIZE 1024
# define EXIT 0
# define NO_EXIT 1

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
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

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}					t_env;


/* commands.c */
void				echo_aux(char **args, int num_args, int flag);
int					echo(char **input, int num_tokens);
int					pwd(void);
int					change_dir(char **input, int num_tokens);

/* command_utils.c */
char				*find_executable(char *cmd);
char				**get_cmd(char **input, char c);
int					exe_cmd(char **input, int num_tokens);
void				exe_command(char **parsed);

/* env.c */
void				add_env_node(char *var_name, char *var_value, t_env **head);
t_env				*parse_env(char **environ);
void				print_env(t_env *head);
void				free_env_list(t_env *head);
int					show_env(void);

/* env.utils.c */
void				ft_lstadd_back_env(t_env **lst, t_env *new);
t_env				*ft_lstlast_env(t_env *lst);

/* print_prompt.c */
void				print_prompt(void);

/* utils_1.c */
char				*ft_strcpy(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
void				free_parsed(char **parsed);

/* utils_2.c */
int					count_words(char *str);
char				*ft_strncpy(char *s1, char *s2, int n);
char				**ft_split_default(char *str);
int					show_cmd_error(char *str);

int					exe_executable(char *input);

#endif
