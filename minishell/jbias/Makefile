NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = $(wildcard builtins/*.c) $(wildcard LIBFT/*.c) \
		$(wildcard pipex/pipex_sources/*.c) $(wildcard pipex/pipex_utils/*.c) \
		$(wildcard pipex/*.c) minishell.c parsing.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline
	@echo "$(NAME) compiled successfully!"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re