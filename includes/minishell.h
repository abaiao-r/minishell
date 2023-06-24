/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:34:43 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/24 20:57:57 by abaiao-r         ###   ########.fr       */
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
# define LLONG_MAX_STR "9223372036854775807"
# define LLONG_MIN_STR "9223372036854775808"

# define VALID 0
# define INVALID 1
# define FAILURE -1

# include "../libft/libft.h"
# include <assert.h>
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
# include <termios.h>
# include <unistd.h>

extern struct s_global_minishell	g_minishell;

typedef struct s_env
{
	char							*var_name;
	char							*var_value;
	int								rank;
	struct s_env					*next;
}									t_env;

typedef struct s_input
{
	char							*token;
	int								index;
	int								in_quotes;
	struct s_input					*next;
}									t_input;

typedef struct s_minishell
{
	t_env							*environment;
	t_input							*input;
	unsigned char					exit_status;
	char							*input_str;
	char							**tokens;
	int								in;
	int								out;
	char							**cmd_without_redirects;
}									t_minishell;

struct								s_global_minishell
{
	int								in_command;
	int								sigint;
	int								sigquit;
	t_minishell						*minishell;
};

typedef struct s_arg
{
	int								arg_index;
	int								string_len;
	char							*arg;
	int								arg_len;
	int								in_quotes;
	int								within_quotes;
	char							quote_type;
	char							c;
	char							operator[3];
}									t_arg;

typedef struct s_dollar_data
{
	int								start;
	int								end;
	char							*find_var;
	char							*replacement;
	size_t							input_len;
	size_t							replacement_len;
	int								flag_double_quotes;
	int								flag_single_quotes;
}									t_dollar_data;

typedef struct s_por_data
{
	size_t							input_len;
	size_t							replacement_len;
	int								flag_single_quotes;
	int								flag_double_quotes;
	char							*replacement;
	int								start;
	int								end;
}									t_por_data;

typedef struct redirect_info
{
	int								pipe_fd_0;
	int								pipe_fd_1;
	int								in_fd;
	int								i;
	int								status;
	pid_t							pid;
}									t_redirect_info;

/* commands.c */
void								echo_aux(char **args, int num_args,
										int flag);
int									echo(t_minishell **minishell, char **tokens,
										int num_tokens);
int									pwd(t_minishell **minishell);
int									change_dir(char **input, int num_tokens,
										t_env **environment);
int									exe_cmd(char **tokens, int num_tokens,
										t_minishell *minishell);

/* env_utils.c */
t_env								*ft_lstlast_env(t_env *lst);
void								ft_lstadd_back_env(t_env **lst, t_env *new);
void								print_env(t_env **head);
void								free_env_list(t_env **head);
void								swap_env_nodes(t_env *curr);

/* env.c */
void								add_env_node(char *var_name,
										char *var_value,
										int i,
										t_env **environment);
void								create_env_node(char *env_var_str, int i,
										t_env **environment);
t_env								*parse_env(char **environ);
t_env								*sort_rank_env_list(t_env **head);
int									show_env(t_minishell **minishell,
										int num_tokens);

/* error_messages_utils.c */
void								print_error_cd(char *token);
void								print_error_exit(char *token);
int									show_quotes_error(void);
int									show_special_char_error(char c);

/* exe_commands.c */
void								save_fds(t_minishell *minishell);
void								reset_fds(t_minishell *minishell);
int									exe_builtin(char **tokens,
										t_minishell *minishell);
void								exe_command_no_pipes(int num_commands,
										t_minishell *minishell);
int									exe_commands(t_minishell *minishell);

/* exe_shell_cmd.c */
char								*get_path(char *cmd, char *path);
char								*find_executable(char *cmd,
										t_env **environment);
int									exe_bash_args(char **bash_args,
										t_env **environment,
										t_minishell *minishell, int i);
int									exe_shell_cmd(char **args, int num_tokens,
										t_minishell *minishell,
										t_env **environment);

/* export_utils.c */
int									update_env_name(t_env **env_list,
										char *find_var, char *new_value,
										int flag_equal);
int									parse_input_export(char *input,
										char **find_var, char **new_value);
t_env								*sort_alphabet_env_list(t_env **head);
void								print_export(t_env **head);
int									show_export(t_env **environment);

/* export.c */
int									export(int num_tokens,
										t_minishell **minishell);

/* free_mem.c */
void								free_parsed(char **parsed);
void								free_token_list(t_input **head);
void								free_input_resources(
										t_minishell *minishell);
void								free_minishell(t_minishell *minishell);

/* ft_getenv.c */
char								*ft_getenv(const char *name,
										t_env *environment);

/* heredoc.c */
int									heredoc(char *delimiter,
										t_minishell *minishell);

/* input_parser_utils_1.c */
void								start_quote(int *single_quote,
										int *double_quote, int *i, char *input);
int									is_between_quotes(char *input, int index);
int									get_redirection_len(char *str);
char								*get_word(char *input, int start, int end,
										int *quote_flag);
void								add_word(t_input **head, char *input,
										int start, int end);

/* input_parser_utils_2.c */
t_input								*ft_lstlast_parser(t_input *lst);
void								ft_lstadd_back_parser(t_input **lst,
										t_input *new);
t_input								*new_node(char *str);
void								add_node(t_input **head, char *str);
void								free_list(t_input *head);

/* input_parser.c */
int									get_word_len(char *input);
void								new_parse_args_aux(t_input **head,
										char *input, int *i);
t_input								*new_parse_arguments(char *input,
										t_minishell *minishell);

/* is_quote_parsed_valid.c */
int									is_pipe_or_redirection_valid(
										t_input *input);

/* minishell_data.c */
t_minishell							*init_minishell(char **env);
int									validate_and_load_data(
										t_minishell *minishell,
										char *input);

/* parse_dollar_question.c */
char								*parse_dollar_question(char *input,
										int exit_status);

/* parse_dollar.c */
char								*parse_dollar(char *input,
										t_env **environment);

/* parse_pipe_or_redirection.c */
char								*parse_pipe_or_redirection(char *input);

/* parser_2d.c */
int									ft_token_lstsize(t_input *lst);
char								**create_token_array_2d(t_input *input,
										t_minishell *minishell);

/* parser_checks.c */
int									is_quotes_special_char_valid(char *input);

/* pipe_1.c */
void								redirect_child(t_input *input,
										int num_commands,
										t_minishell *minishell,
										t_redirect_info redirect_info);
void								wait_for_children(int num_commands,
										t_redirect_info redirect_info,
										t_minishell *minishell);
void								redirect(t_input *input, int num_commands,
										t_minishell *minishell);

/* pipe_2.c */
t_input								*get_next_cmd(t_input *input);
int									count_tokens_str(char **args);
int									count_arguments(t_input *input);
void								print_error_shell(char *str);

/* pipes_exe_commands_utils.c */
int									is_redirection(char *str);
int									is_builtin(char **tokens);
int									ft_isnumber(char *str);
int									ft_exit(t_minishell *minishell,
										char **tokens, int num_tokens);
int									count_commands_lst(t_input *input);

/* redirections.c */
int									redirect_input(char *file);
int									redirect_output(char *file, int append);
char								**get_command_without_redirects(
										t_input *input);
int									handle_redirections(t_input *input,
										t_minishell *minishell);

/* signal.c */
void								sig_handler(int signum);

/* unset.c */
int									delete_env_name(t_env **env_list,
										char *input);
int									ft_unset(int num_tokens,
										t_minishell **minishell);
#endif