# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 13:21:58 by mstasiak          #+#    #+#              #
#    Updated: 2025/01/24 16:43:39 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= fractol
NAME_BONUS		= fractol_bonus

# Sources et objets
SRC				= \
		main.c \
		fractales/julia.c \
		fractales/mandelbrot.c \
		sources/colors.c \
		sources/fractal_security.c \
		sources/ft_atof.c \
		sources/function_Libft.c \
		sources/init.c \
		sources/keyboard_events.c \
		sources/mouse_events.c \
		sources/print_function.c \
		sources/screen.c \
		sources/utils.c
OBJ				= $(SRC:.c=.o)

SRC_BONUS		= \
		main_bonus.c \
		fractales/burning_ship_bonus.c \
		fractales/julia_bonus.c \
		fractales/mandelbrot_bonus.c \
		sources/colors_bonus.c \
		sources/fractal_security_bonus.c \
		sources/ft_atof_bonus.c \
		sources/function_Libft_bonus.c \
		sources/init_bonus.c \
		sources/keyboard_events_bonus.c \
		sources/mouse_events_bonus.c \
		sources/print_function_bonus.c \
		sources/screen_bonus.c \
		sources/utils_bonus.c
OBJ_BONUS		= $(SRC_BONUS:.c=.o)

# Dossiers
INCLUDE_DIR		= ./includes
PRINTF_DIR		= $(INCLUDE_DIR)/ft_printf
MLX_DIR			= $(INCLUDE_DIR)/minilibx-linux

# Bibliothèques
PRINTF_A		= $(PRINTF_DIR)/libftprintf.a
MLX_A			= $(MLX_DIR)/libmlx.a

# Compilateur et flags
CC				= cc
CFLAGS			= -Wall -Werror -Wextra -I $(INCLUDE_DIR) -g
LIBS			= $(PRINTF_A) $(MLX_A) -lm -lbsd -lX11 -lXext

# Règles
all: $(NAME)

$(NAME): $(OBJ) $(PRINTF_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(NAME) compilé avec succès."

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(PRINTF_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBS) -o $(NAME_BONUS)
	@echo "$(NAME_BONUS) compilé avec succès."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF_A):
	@echo "Compilation de ft_printf..."
	@$(MAKE) -s -C $(PRINTF_DIR)

$(MLX_A):
	@echo "Compilation de minilibx..."
	@$(MAKE) -s -C $(MLX_DIR)

clean:
	@$(MAKE) -s clean -C $(PRINTF_DIR)
	@$(MAKE) -s clean -C $(MLX_DIR)
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "Nettoyage des fichiers objets terminé."

fclean: clean
	@$(MAKE) -s fclean -C $(PRINTF_DIR)
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "Nettoyage complet terminé."

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re bonus re_bonus
