# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 12:44:03 by abaiao-r          #+#    #+#              #
#    Updated: 2023/03/03 13:49:17 by abaiao-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isdigit.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strlcat.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c  \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c  \
		ft_printf.c \
		get_next_line_utils.c \
		get_next_line.c

LIB = libft.h

		

SRC_BONUS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c
		

OBJS = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

CC= cc 

RM = rm -rf 

all:	$(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $^
	
bonus:	$(OBJS) $(OBJ_BONUS)
			ar -rcs $(NAME) $(OBJS) $(OBJ_BONUS)

clean:	
			$(RM) $(OBJS) $(OBJ_BONUS)

fclean:	clean
				$(RM) $(NAME)

re: fclean all



.PHONY: all clean fclean re bonus
