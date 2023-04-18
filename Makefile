# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/21 16:08:07 by abaiao-r          #+#    #+#              #
#    Updated: 2023/04/18 19:29:32 by abaiao-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	print_prompt.c \
		main.c 

CFLAGS = -Wall -Wextra -Werror -g

CC= cc 

RM = rm -rf 

LIBFT_DIR = libft/
LIBFT_INCLUDE = libft

all: $(NAME)
	
$(NAME): $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) bonus
			$(CC) $(CFLAGS) $(SRC) libft/libft.a -o $(NAME) -fsanitize=address -lreadline
clean:	
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
				$(RM) $(NAME)
				$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
				
.PHONY: all clean fclean re bonus