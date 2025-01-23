# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 13:19:53 by mstasiak          #+#    #+#              #
#    Updated: 2025/01/23 15:15:13 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol
NAME_BONUS	= fractol_bonus

# Sources et objets
OBJ			= $(SRC:.c=.o)
SRC			= \
		main.c \
		fractales/julia.c \
		fractales/mandelbrot.c \
		sources/colors.c \
		sources/fractal_security.c \
		sources/init.c \
		sources/keyboard_events.c \
		sources/mouse_events.c \
		sources/print_function.c \
		sources/screen.c \
		sources/utils.c

OBJ_BONUS		= $(SRC_BONUS:.c=.o)
SRC_BONUS	= \
		main_bonus.c \
		fractales/burning_ship_bonus.c \
		fractales/julia_bonus.c \
		fractales/mandelbrot_bonus.c \
		sources/colors_bonus.c \
		sources/fractal_security_bonus.c \
		sources/init_bonus.c \
		sources/keyboard_events_bonus.c \
		sources/mouse_events_bonus.c \
		sources/print_function_bonus.c \
		sources/screen_bonus.c \
		sources/utils_bonus.c

# Dossiers
INCLUDE_DIR	= ./includes
PRINTF_DIR	= $(INCLUDE_DIR)/ft_printf
LIBFT_DIR	= $(INCLUDE_DIR)/Libft
MLX_DIR		= $(INCLUDE_DIR)/minilibx-linux

# Bibliotheques
PRINTF_A	= $(PRINTF_DIR)/libftprintf.a
LIBFT_A		= $(LIBFT_DIR)/libft.a
MLX_A		= $(MLX_DIR)/libmlx.a

# Compileur et flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I $(PRINTF_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR) -I $(INCLUDE_DIR) -g
LIBS		= -lm -lbsd -lX11 -lXext

# Rules
all:		$(NAME)

$(NAME):	$(OBJ) $(PRINTF_A) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF_A) $(LIBFT_A) $(MLX_A) $(LIBS) -o $(NAME)

bonus:		$(NAME_BONUS)

$(NAME_BONUS):	$(OBJ) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF_A) $(LIBFT_A) $(MLX_A) $(LIBS) -o $(NAME_BONUS)

$(PRINTF_A):
	make -C $(PRINTF_DIR)
$(LIBFT_A):
	make -C $(LIBFT_DIR)
$(MLX_A):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(PRINTF_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean:		clean
	rm -f $(NAME)
	make fclean -C $(PRINTF_DIR)
	make fclean -C $(LIBFT_DIR)

re:			fclean all

.PHONY:		all clean fclean re bonus
