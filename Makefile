# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: quackson <quackson@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/21 16:08:07 by abaiao-r          #+#    #+#              #
#    Updated: 2023/06/10 23:01:25 by quackson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address 

# Directories
SRCDIR = ./src
OBJDIR = ./objs

# Source Files

SRCS = $(SRCDIR)/main.c $(SRCDIR)/utils_1.c $(SRCDIR)/utils_2.c $(SRCDIR)/command_utils.c \
	   $(SRCDIR)/commands.c $(SRCDIR)/print_prompt.c $(SRCDIR)/env.c $(SRCDIR)/exe.c \
	   $(SRCDIR)/env_utils.c $(SRCDIR)/export_utils.c $(SRCDIR)/export.c $(SRCDIR)/ft_getenv.c \
	   $(SRCDIR)/is_quote_parsed_valid.c $(SRCDIR)/unset.c $(SRCDIR)/pipe.c $(SRCDIR)/parse_args.c \
	   $(SRCDIR)/parse_pipe_or_redirection.c $(SRCDIR)/parse_args_utils1.c $(SRCDIR)/parse_dollar.c \
	   $(SRCDIR)/parse_dollar_question.c $(SRCDIR)/utils_3.c $(SRCDIR)/new_parser.c
	   

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