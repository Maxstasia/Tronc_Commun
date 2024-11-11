# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 15:23:06 by mstasiak          #+#    #+#              #
#    Updated: 2024/11/05 15:23:10 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC =	srcs/ft_putchar.c \
		srcs/ft_swap.c \
		srcs/ft_putstr.c \
		srcs/ft_strlen.c \
		srcs/ft_strcmp.c
OBJ = $(SRC:.c=.o)
CC = cc
HEADER = ./includes
CFLAGS = -Wall -Wextra -Werror -I $(HEADER)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
