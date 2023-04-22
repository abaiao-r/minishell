# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/21 16:08:07 by abaiao-r          #+#    #+#              #
#    Updated: 2023/04/22 14:11:29 by andrefranci      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	commands.c \
		command_utils.c \
		print_prompt.c \
		utils_1.c \
		utils_2.c \
		main.c 

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS =  -L/usr/lib -lreadline

CC= cc 

RM = rm -rf 

LIBFT_DIR = libft/
LIBFT_INCLUDE = libft

all: $(NAME)

$(NAME): $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) bonus
			$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) libft/libft.a -o $(NAME) 
clean:	
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
				$(RM) $(NAME)
				$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

run:	all
		./$(NAME)

lldb:	all
		lldb -- ./$(NAME)

gdb:	all
		gdb --args $(NAME)

valgrind: 	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re bonus run