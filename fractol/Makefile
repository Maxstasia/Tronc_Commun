# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 13:19:53 by mstasiak          #+#    #+#              #
#    Updated: 2025/01/03 15:40:32 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol

# Sources et objets
OBJ			= $(SRC:.c=.o)
SRC			= \
		main.c \
		sources/colors.c \
		sources/events.c \
		sources/julia.c \
		sources/mandelbrot.c \
		sources/utils.c

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
