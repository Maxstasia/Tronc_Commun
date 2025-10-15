# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 11:38:53 by mstasiak          #+#    #+#              #
#    Updated: 2025/10/15 16:44:16 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
NAME_BONUS		= cub3D_Bonus

# Dossiers
OBJ_DIR				= ./obj

OBJ_DIR_BONUS		= ./Bonus/obj

INCLUDE_DIR			= includes
GNL_DIR				= $(INCLUDE_DIR)/get_next_line
PARSER_DIR			= parsing
RAY_DIR				= ray_casting
SOURCES_DIR			= sources
EVENT_DIR			= $(SOURCES_DIR)/events
INIT_DIR			= $(SOURCES_DIR)/init
UTILS_DIR			= utils

INCLUDE_DIR_BONUS	= Bonus/includes
GNL_DIR_BONUS		= $(INCLUDE_DIR_BONUS)/get_next_line
PARSER_DIR_BONUS	= Bonus/parsing
RAY_DIR_BONUS		= Bonus/ray_casting
SOURCES_DIR_BONUS	= Bonus/sources
EVENT_DIR_BONUS		= $(SOURCES_DIR_BONUS)/events
INIT_DIR_BONUS		= $(SOURCES_DIR_BONUS)/init
UTILS_DIR_BONUS		= Bonus/utils

LIBFT_DIR			= $(INCLUDE_DIR)/Libft
MLX_DIR				= $(INCLUDE_DIR)/minilibx-linux

LIBFT_DIR_BONUS		= $(INCLUDE_DIR_BONUS)/Libft
MLX_DIR_BONUS		= $(INCLUDE_DIR_BONUS)/minilibx-linux

# Sources et objets
SRC					=							\
			main.c								\
			\
			$(GNL_DIR)/get_next_line.c			\
			$(GNL_DIR)/get_next_line_utils.c	\
			\
			$(PARSER_DIR)/check_map.c			\
			$(PARSER_DIR)/parse_colors.c		\
			$(PARSER_DIR)/parse_map_lines.c		\
			$(PARSER_DIR)/parse_textures.c		\
			$(PARSER_DIR)/parser.c				\
			\
			$(RAY_DIR)/ray_casting_norm.c		\
			$(RAY_DIR)/ray_casting.c			\
			$(RAY_DIR)/render.c					\
			\
			$(SOURCES_DIR)/error.c				\
			\
			$(EVENT_DIR)/keyboard_event.c		\
			$(EVENT_DIR)/mouse_event.c			\
			$(EVENT_DIR)/movement.c				\
			\
			$(INIT_DIR)/init_data.c				\
			$(INIT_DIR)/init_keys.c				\
			$(INIT_DIR)/init_main.c				\
			$(INIT_DIR)/init_map.c				\
			$(INIT_DIR)/init_mlx.c				\
			$(INIT_DIR)/init_parser.c			\
			$(INIT_DIR)/init_player.c			\
			$(INIT_DIR)/init_ray.c				\
			\
			$(UTILS_DIR)/cleanup.c				\
			$(UTILS_DIR)/free_all.c				\
			$(UTILS_DIR)/free_data.c
OBJ					= $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPENDS				= $(SRC:%.c=$(OBJ_DIR)/%.d)

# Sources et objets bonus
SRC_BONUS			=										\
			Bonus/main_bonus.c								\
			\
			$(GNL_DIR_BONUS)/get_next_line.c				\
			$(GNL_DIR_BONUS)/get_next_line_utils.c			\
			\
			$(PARSER_DIR_BONUS)/check_doors_bonus.c			\
			$(PARSER_DIR_BONUS)/check_map_bonus.c			\
			$(PARSER_DIR_BONUS)/check_teleporters_bonus.c	\
			$(PARSER_DIR_BONUS)/parse_colors_bonus.c		\
			$(PARSER_DIR_BONUS)/parse_door_bonus.c			\
			$(PARSER_DIR_BONUS)/parse_map_lines_bonus.c		\
			$(PARSER_DIR_BONUS)/parse_textures_bonus.c		\
			$(PARSER_DIR_BONUS)/parser_bonus.c				\
			\
			$(RAY_DIR_BONUS)/animation_bonus.c				\
			$(RAY_DIR_BONUS)/load_texture_bonus.c			\
			$(RAY_DIR_BONUS)/minimap_bonus.c				\
			$(RAY_DIR_BONUS)/minimap_helper_bonus.c			\
			$(RAY_DIR_BONUS)/ray_casting_norm_bonus.c		\
			$(RAY_DIR_BONUS)/ray_casting_bonus.c			\
			$(RAY_DIR_BONUS)/render_bonus.c					\
			\
			$(EVENT_DIR_BONUS)/interaction_movement_bonus.c	\
			$(EVENT_DIR_BONUS)/keyboard_event_bonus.c		\
			$(EVENT_DIR_BONUS)/mouse_event_bonus.c			\
			$(EVENT_DIR_BONUS)/movement_bonus.c				\
			$(EVENT_DIR_BONUS)/rotation_movement_bonus.c	\
			\
			$(INIT_DIR_BONUS)/init_animation_bonus.c		\
			$(INIT_DIR_BONUS)/init_data_bonus.c				\
			$(INIT_DIR_BONUS)/init_keys_bonus.c				\
			$(INIT_DIR_BONUS)/init_main_bonus.c				\
			$(INIT_DIR_BONUS)/init_map_bonus.c				\
			$(INIT_DIR_BONUS)/init_minimap_bonus.c			\
			$(INIT_DIR_BONUS)/init_mlx_bonus.c				\
			$(INIT_DIR_BONUS)/init_parser_bonus.c			\
			$(INIT_DIR_BONUS)/init_player_bonus.c			\
			$(INIT_DIR_BONUS)/init_ray_bonus.c				\
			\
			$(SOURCES_DIR_BONUS)/error_bonus.c				\
			\
			$(UTILS_DIR_BONUS)/cleanup_bonus.c				\
			$(UTILS_DIR_BONUS)/free_all_bonus.c				\
			$(UTILS_DIR_BONUS)/free_data_bonus.c
OBJ_BONUS			= $(SRC_BONUS:%.c=$(OBJ_DIR_BONUS)/%.o)
DEPENDS_BONUS		= $(SRC_BONUS:%.c=$(OBJ_DIR_BONUS)/%.d)

# Bibliothèques
LIBFT_A				= $(LIBFT_DIR)/libft.a
MLX_A				= $(MLX_DIR)/libmlx.a
LIBS				= -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -lm -lXext -lX11 -lz

LIBFT_A_BONUS		= $(LIBFT_DIR_BONUS)/libft.a
MLX_A_BONUS			= $(MLX_DIR_BONUS)/libmlx.a
LIBS_BONUS			= -L $(LIBFT_DIR_BONUS) -lft -L $(MLX_DIR_BONUS) -lmlx -lm -lXext -lX11 -lz

# Compilateur et flags
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -MMD -I $(INCLUDE_DIR) -g
CC_BONUS			= cc
CFLAGS_BONUS		= -Wall -Werror -Wextra -MMD -I $(INCLUDE_DIR_BONUS) -g

# Règles de compilation
all: $(NAME)
bonus: $(NAME_BONUS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(GNL_DIR) $(OBJ_DIR)/$(PARSER_DIR) $(OBJ_DIR)/$(RAY_DIR) $(OBJ_DIR)/$(SOURCES_DIR) $(OBJ_DIR)/$(EVENT_DIR) $(OBJ_DIR)/$(INIT_DIR) $(OBJ_DIR)/$(UTILS_DIR)
$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS) $(OBJ_DIR_BONUS)/$(GNL_DIR_BONUS) $(OBJ_DIR_BONUS)/$(PARSER_DIR_BONUS) $(OBJ_DIR_BONUS)/$(RAY_DIR_BONUS) $(OBJ_DIR_BONUS)/$(SOURCES_DIR_BONUS) $(OBJ_DIR_BONUS)/$(EVENT_DIR_BONUS) $(OBJ_DIR_BONUS)/$(INIT_DIR_BONUS) $(OBJ_DIR_BONUS)/$(UTILS_DIR_BONUS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR_BONUS)/%.o: %.c | $(OBJ_DIR_BONUS)
	@$(CC_BONUS) $(CFLAGS_BONUS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(NAME) compilé avec succès."
$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT_A_BONUS) $(MLX_A_BONUS)
	@$(CC) $(CFLAGS_BONUS) $(OBJ_BONUS) $(LIBS_BONUS) -o $(NAME_BONUS)
	@echo "$(NAME_BONUS) compilé avec succès."

$(LIBFT_A):
	@echo "Compilation de LIBFT..."
	@$(MAKE) -s -C $(LIBFT_DIR)
$(LIBFT_A_BONUS):
	@echo "Compilation de LIBFT..."
	@$(MAKE) -s -C $(LIBFT_DIR_BONUS)

$(MLX_A):
	@echo "Compilation de minilibx..."
	@$(MAKE) -s -C $(MLX_DIR)
$(MLX_A_BONUS):
	@echo "Compilation de minilibx..."
	@$(MAKE) -s -C $(MLX_DIR_BONUS)

clean:
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@$(MAKE) -s clean -C $(MLX_DIR)
	@$(MAKE) -s clean -C $(LIBFT_DIR_BONUS)
	@$(MAKE) -s clean -C $(MLX_DIR_BONUS)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@echo "Nettoyage des fichiers objets terminé."

fclean: clean
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@$(MAKE) -s fclean -C $(LIBFT_DIR_BONUS)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "Nettoyage complet terminé."

re: fclean all

.PHONY: all clean fclean re bonus

-include ${DEPENDS}
