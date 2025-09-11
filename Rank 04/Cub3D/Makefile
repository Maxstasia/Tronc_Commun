# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 11:38:53 by mstasiak          #+#    #+#              #
#    Updated: 2025/09/11 13:44:20 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D

# Dossiers
OBJ_DIR			= ./obj

INCLUDE_DIR		= includes
PARSER_DIR		= parsing
RAY_DIR			= ray_casting
SOURCES_DIR		= sources
INIT_DIR		= $(SOURCES_DIR)/init
UTILS_DIR		= utils

LIBFT_DIR		= $(INCLUDE_DIR)/Libft
MLX_DIR			= $(INCLUDE_DIR)/minilibx-linux

# Sources et objets
SRC				=							\
			main.c							\
			\
			$(PARSER_DIR)/parser.c			\
			\
			$(RAY_DIR)/ray_casting.c		\
			\
			$(SOURCES_DIR)/error.c			\
			$(SOURCES_DIR)/keyboard_event.c	\
			$(SOURCES_DIR)/mouse_event.c	\
			\
			$(INIT_DIR)/init_data.c			\
			$(INIT_DIR)/init_main.c			\
			$(INIT_DIR)/init_mlx.c			\
			\
			$(UTILS_DIR)/cleanup.c
OBJ				= $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPENDS			= $(SRC:%.c=$(OBJ_DIR)/%.d)

# Bibliothèques
LIBFT_A			= $(LIBFT_DIR)/libft.a
MLX_A			= $(MLX_DIR)/libmlx.a
LIBS			= -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -lm -lXext -lX11 -lz

# Compilateur et flags
CC				= cc
CFLAGS			= -Wall -Werror -Wextra -MMD -I $(INCLUDE_DIR) -g

# Règles de compilation
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSER_DIR) $(OBJ_DIR)/$(RAY_DIR) $(OBJ_DIR)/$(SOURCES_DIR) $(OBJ_DIR)/$(INIT_DIR) $(OBJ_DIR)/$(UTILS_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(NAME) compilé avec succès."

$(LIBFT_A):
	@echo "Compilation de LIBFT..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX_A):
	@echo "Compilation de minilibx..."
	@$(MAKE) -s -C $(MLX_DIR)

clean:
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@$(MAKE) -s clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage des fichiers objets terminé."

fclean: clean
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "Nettoyage complet terminé."

re: fclean all

.PHONY: all clean fclean re

-include ${DEPENDS}
