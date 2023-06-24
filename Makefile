# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/21 16:08:07 by abaiao-r          #+#    #+#              #
#    Updated: 2023/06/24 20:11:35 by abaiao-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address 

# Directories
SRCDIR = ./src
OBJDIR = ./objs

# Source Files

SRCS = $(SRCDIR)/commands.c \
       $(SRCDIR)/env.c \
       $(SRCDIR)/env_utils.c \
       $(SRCDIR)/error_messages_utils.c \
       $(SRCDIR)/exe_commands.c \
       $(SRCDIR)/exe_shell_cmd.c \
       $(SRCDIR)/export.c \
       $(SRCDIR)/export_utils.c \
       $(SRCDIR)/free_mem.c \
       $(SRCDIR)/ft_getenv.c \
       $(SRCDIR)/heredoc.c \
       $(SRCDIR)/input_parser.c \
       $(SRCDIR)/input_parser_utils_1.c \
       $(SRCDIR)/input_parser_utils_2.c \
       $(SRCDIR)/is_quote_parsed_valid.c \
       $(SRCDIR)/main.c \
       $(SRCDIR)/minishell_data.c \
       $(SRCDIR)/parse_dollar.c \
       $(SRCDIR)/parse_dollar_question.c \
       $(SRCDIR)/parse_pipe_or_redirection.c \
       $(SRCDIR)/parser_2d.c \
       $(SRCDIR)/parser_checks.c \
       $(SRCDIR)/pipe_1.c \
       $(SRCDIR)/pipe_2.c \
       $(SRCDIR)/pipes_exe_commands_utils.c \
       $(SRCDIR)/redirections.c \
       $(SRCDIR)/signal.c \
       $(SRCDIR)/unset.c


OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIBFT_DIR = libft/
LIBFT_INCLUDE = libft

# Targets
NAME = minishell

all: 	$(NAME)

bonus:	all

clean:
		rm -rf $(OBJDIR)
		cd libft && make clean

fclean:	clean
		rm -f $(NAME)
		cd libft && make fclean

run:	all
		./$(NAME)

re:		fclean all

lldb:	all
		lldb $(NAME)

gdb:	all
		gdb $(NAME)

valgrind: 	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
valgrind_supp: all
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./$(NAME)
val_gdb: 	all
			valgrind --vgdb=yes --vgdb-error=0 ./$(NAME) 
remote_gdb:
			gdb -ex "target remote | vgdb"
leak_valgrind: all
				valgrind --leak-check=full --show-leak-kinds=definite,possible --track-origins=yes ./$(NAME)

$(NAME): 	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR) bonus
			$(CC) $(OBJS) $(CFLAGS) -lreadline libft/libft.a -o  $(NAME) 

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@ 

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean bonus re run