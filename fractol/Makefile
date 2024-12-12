# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 13:19:53 by mstasiak          #+#    #+#              #
#    Updated: 2024/12/12 17:23:56 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol

# Sources et objets
OBJ			= $(SRC:.c=.o)
SRC			= \
		main.c

# Dossiers
INCLUDE_DIR	= ./includes
MLX_DIR		= $(INCLUDE_DIR)/minilibx-linux

# Bibliotheques
PRINTF_A	= $(INCLUDE_DIR)/libftprintf.a
LIBFT_A		= $(INCLUDE_DIR)/libft.a
MLX_A		= $(MLX_DIR)/libmlx.a

# Compileur et flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I $(MLX_DIR) -I $(INCLUDE_DIR) -g
LIBS		= -lm -lbsd -lX11 -lXext

# Rules
all:		$(NAME)

$(NAME):	$(OBJ) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF_A) $(LIBFT_A) $(MLX_A) $(LIBS) -o $(NAME)

$(MLX_A):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
