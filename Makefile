# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -lreadline #-fsanitize=address 

# Directories
SRCDIR = ./src
OBJDIR = ./objs

# Source Files

SRCS = $(SRCDIR)/main.c $(SRCDIR)/utils_1.c $(SRCDIR)/utils_2.c $(SRCDIR)/command_utils.c $(SRCDIR)/commands.c
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Targets
NAME = minishell

all: 	$(NAME)

bonus:	all

clean:
		rm -f $(OBJDIR)/*.o

fclean:	clean
		rm -f $(NAME)

run:	all
		./$(NAME)

re:		fclean all

lldb:	all
		lldb -- ./$(NAME)

gdb:	all
		gdb --args $(NAME)

valgrind: 	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -O3 -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean bonus run
