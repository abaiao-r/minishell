/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:34:43 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/05/16 18:33:07 by abaiao-r         ###   ########.fr       */
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
# define MAX_ARGS 1024

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
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
	int				rank;
	struct s_env	*next;
}					t_env;

typedef struct s_dollar_data
{
	int		start;
	int		end;
	char	*find_var;
	char	*replacement;
	size_t	input_len;
	size_t	replacement_len;
	int		flag_double_quotes;
	int		flag_single_quotes;
}			t_dollar_data;

typedef struct s_parsed
{
	char			**args;
	int				arg_index;
	int				string_len;
}					t_parsed;

typedef struct s_arg
{
	char			*arg;
	int				arg_len;
	int				in_quotes;
	char			quote_type;
}					t_arg;

/* commands.c */
void				echo_aux(char **args, int num_args, int flag);
int					echo(char **input, int num_tokens);
int					pwd(void);
int					change_dir(char **input, int num_tokens);

/* command_utils.c */
char				*find_executable(char *cmd);
char				**get_cmd(char **input, char c);
int					exe_cmd(char **parsed, char *input, int num_tokens,
						t_env **environment);
void				exe_command(char **parsed);
void				exe_executable(char **input);

/* env.c */
void				add_env_node(char *var_name, char *var_value, int i,
						t_env **environment);
void				create_env_node(char *env_var_str, int i,
						t_env **environment);
t_env				*parse_env(char **environ);
t_env				*sort_rank_env_list(t_env **head);
int					show_env(t_env **environment);

/* env.utils.c */
void				ft_lstadd_back_env(t_env **lst, t_env *new);
t_env				*ft_lstlast_env(t_env *lst);
void				print_env(t_env **head);
void				free_env_list(t_env **head);
void				swap_env_nodes(t_env *curr);

/* export.c */
int					export(char **input, int num_tokens, t_env **environment);

void				execute_pipe(char **cmd1, int cmd1_num_tokens, char **cmd2,
						int cmd2_num_tokens);

/* export_utils.c */
int					update_env_name(t_env **env_list, char *find_var,
						char *new_value, int flag_equal);
int					parse_input_export(char *input, char **find_var,
						char **new_value);
t_env				*sort_alphabet_env_list(t_env **head);
void				print_export(t_env **head);
int					show_export(t_env **environment);

/* print_prompt.c */
char				*print_prompt(void);

/* parse_args */
char				**parse_arguments(char *input_string);

/* parse_utils.c */
char				*parse_dollar(char *input, t_env **environment);

/* utils_1.c */
void				free_parsed(char **parsed);

/* utils_2.c */
int					count_words(char *str);
char				*ft_strncpy(char *s1, char *s2, int n);
char				**ft_split_default(char *str);
int					show_cmd_error(char *str);
int					show_pipe_error(void);
int					is_valid_input(char *input);

/* unset.c */
int					delete_env_name(t_env **env_list, char *input);
int					ft_unset(char **input, int num_tokens, t_env **environment);

#endif
