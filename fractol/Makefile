# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 13:19:53 by mstasiak          #+#    #+#              #
#    Updated: 2024/12/11 18:30:17 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC =	main.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

PRINTF_A = ./includes/libftprintf.a
LIBFT_A = ./includes/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF_A) $(LIBFT_A) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
