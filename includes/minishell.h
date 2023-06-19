/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:34:43 by abaiao-r          #+#    #+#             */
/*   Updated: 2023/06/19 16:11:32 by abaiao-r         ###   ########.fr       */
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
# include <unistd.h>

extern struct s_global_minishell	g_minishell;

struct								s_global_minishell
{
	int								in_command;
	int								sigint;
	int								sigquit;
};

typedef struct s_env
{
	char							*var_name;
	char							*var_value;
	int								rank;
	struct s_env					*next;
}									t_env;

typedef struct s_prompt
{
	char							*prompt_full;
}									t_prompt;

typedef struct s_input
{
	char							*token;
	int								index;
	int								within_quotes;
	struct s_input					*next;
}									t_input;

typedef struct s_minishell
{
	t_env							*environment;
	t_prompt						*prompt;
	t_input							*input;
	int								exit_status;
	char							*input_str;
	char							**tokens;
	int								in;
	int								out;
}									t_minishell;

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

/* command_utils.c */
char *find_executable(char *cmd, t_env **environment);
int exe_cmd(char **tokens, int num_tokens, t_minishell *minishell);
void exe_command(char **parsed);
void exe_executable(char **input, t_env **environment);
int exe_shell_cmd(char **args, int num_tokens, t_env **environment);

/* commands.c */
void echo_aux(char **args, int num_args, int flag);
int echo(t_minishell **minishell, int num_tokens);
int pwd(t_minishell **minishell);
int change_dir(char **input, int num_tokens, t_env **environment);

/* env.c */
void add_env_node(char *var_name, char *var_value, int i, t_env **environment);
void create_env_node(char *env_var_str, int i, t_env **environment);
t_env *parse_env(char **environ);
t_env *sort_rank_env_list(t_env **head);
int show_env(t_minishell **minishell, int num_tokens);

/* env.utils.c */
void ft_lstadd_back_env(t_env **lst, t_env *new);
t_env *ft_lstlast_env(t_env *lst);
void print_env(t_env **head);
void free_env_list(t_env **head);
void swap_env_nodes(t_env *curr);

/* export.c */
int export(int num_tokens, t_minishell **minishell);

/* export_utils.c */
int update_env_name(t_env **env_list, char *find_var, char *new_value, int flag_equal);
int parse_input_export(char *input, char **find_var, char **new_value);
t_env *sort_alphabet_env_list(t_env **head);
void print_export(t_env **head);
int show_export(t_env **environment);

/* ft_getenv.c */
char *ft_getenv(const char *name, t_env *environment);

/* free_mem.c */
void free_parsed(char **parsed);
void free_token_list(t_input **head);
void free_input_resources(t_minishell *minishell);
void free_minishell(t_minishell *minishell);

/* is_pipe_or_redirection_valid */
int is_pipe_or_redirection_valid(t_input *input);

/* minishell_data.c */
t_minishell *init_minishell(char **env);
int validate_and_load_data(t_minishell *minishell, char *input);

/* print_prompt.c */
char *print_prompt(t_prompt **prompt_full);

/* parser_2d.c */
int ft_token_lstsize(t_input *lst);
char **create_token_array_2d(t_input *input, t_minishell *minishell);

/* parse_args */
t_input *parse_arguments(char *string);

/* parse_arg_utils1.c */
int start_arg(t_arg *arg, char *str);
int update_arg(t_arg *arg, char *str, int *i);
bool handle_quotes(t_arg *arg, char c, int *i);
bool is_operator(const char *input);
void free_arg(t_input *head);

/* parse_dollar_question */
char *parse_dollar_question(char *input, int exit_status);

/* parse_pipe_or_redirection */
char *parse_pipe_or_redirection(char *input);

/* parse_utils.c */
char *parse_dollar(char *input, t_env **environment);

/* parser_checks.c */
int is_quotes_special_char_valid(char *input);

/* signal.c */
void sig_handler(int signum);

/* utils_2.c */
int count_words(char *str);
char *ft_strncpy(char *s1, char *s2, int n);
char **ft_split_default(char *str);
int show_cmd_error(char *str);
int show_special_char_error(char c);
int is_builtin(char **tokens);

/* unset.c */
int delete_env_name(t_env **env_list, char *input);
int ft_unset(int num_tokens, t_minishell **minishell);

/* pipe.c */
void execute_pipe(char **cmd1, int cmd1_num_tokens, char **cmd2, int cmd2_num_tokens);
int count_tokens(char **args);
int exe_commands(t_minishell *minishell);

/* utils_3.c */
int is_redirection(char *str);
int show_quotes_error(void);
int has_valid_redirections(char **args);

/* input_parser.c */
t_input *new_parse_arguments(char *input, t_minishell *minishell);
void new_parse_args_aux(t_input **head, char *input, int *i);
int get_word_len(char *input);

/* input_parser_utils_1.c */
void start_quote(int *single_quote, int *double_quote, int *i, char *input);
int is_between_quotes(char *input, int index);
int get_redirection_len(char *str);
char *get_word(char *input, int start, int end, int *quote_flag);
void add_word(t_input **head, char *input, int start, int end);

/* input_parser_utils_1.c */
t_input *ft_lstlast_parser(t_input *lst);
void ft_lstadd_back_parser(t_input **lst, t_input *new);
t_input *new_node(char *str);
void add_node(t_input **head, char *str);
void free_list(t_input *head);

/* others */
void redirect_input(char *file);
void redirect_output(char *file, int append);
void heredoc(char *delimiter);

#endif
