/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quackson <quackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:34:43 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/07 18:56:09 by quackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NO_FLAG 0
# define FLAG 1
# define PWD_SIZE 1024
# define EXIT 0
# define NO_EXIT 1
# define PROMPT_SIZE 1024

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
int					exe_cmd(char **parsed, char *input, int num_tokens,
						char **env);
void				exe_command(char **parsed);

/* env.c */
void				add_env_node(char *var_name, char *var_value, t_env **head);
void				create_env_node(char *env_var_str, t_env **environment);
t_env				*parse_env(char **environ);
int					show_env(char **env);
int					old_show_env(void);

/* env.utils.c */
void				ft_lstadd_back_env(t_env **lst, t_env *new);
t_env				*ft_lstlast_env(t_env *lst);
void				print_env(t_env *head);
void				free_env_list(t_env *head);

/* print_prompt.c */
char				*print_prompt(void);

/* utils_1.c */
char				*ft_strcpy(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
void				free_parsed(char **parsed);

/* utils_2.c */
int					count_words(char *str);
char				*ft_strncpy(char *s1, char *s2, int n);
char				**ft_split_default(char *str);
int					show_cmd_error(char *str);
int					is_valid_input(char *input);
char				**parse_echo_arguments(char *input_string);

/* export.c */
int					export(char **input, int num_tokens, char **env);

void				exe_executable(char **input);

void				execute_pipe(char *cmd1, char *cmd2);

#endif
