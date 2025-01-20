# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 16:22:48 by mstasiak          #+#    #+#              #
#    Updated: 2025/01/20 17:17:12 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap

# Sources et objets
OBJ			= $(SRC:.c=.o)
SRC			= \
		main.c \
		sources/error.c \
		sources/input.c \
		sources/instructions.c \
		sources/sort.c \
		sources/stack.c \
		sources/utils.c

# Dossiers
INCLUDE_DIR	= ./includes

# Bibliotheques
PRINTF_A	= $(INCLUDE_DIR)/libftprintf.a

# Compileur et flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I $(INCLUDE_DIR)

# Rules
all:		$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF_A) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
