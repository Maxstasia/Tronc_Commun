# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 16:22:48 by mstasiak          #+#    #+#              #
#    Updated: 2025/03/25 14:50:08 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_BONUS	= pipex_bonus

# Dossiers
SRC_DIR		= ./sources
OBJ_DIR		= ./obj
UTILS_DIR	= ./utils
INCLUDE_DIR	= ./includes
GNL_DIR		= $(INCLUDE_DIR)/get_next_line
LIBFT_DIR	= $(INCLUDE_DIR)/Libft
PRINTF_DIR	= $(INCLUDE_DIR)/ft_printf

# Sources et objets
SRC			=									\
		main.c									\
		\
		$(SRC_DIR)/error.c						\
		\
		$(UTILS_DIR)/ft_split_advanced.c		\
		$(UTILS_DIR)/utils.c

SRC_BONUS	=									\
		main_bonus.c							\
		\
		$(GNL_DIR)/get_next_line.c				\
		$(GNL_DIR)/get_next_line_utils.c		\
		\
		$(SRC_DIR)/error_bonus.c				\
		$(SRC_DIR)/pipex_bonus.c				\
		\
		$(UTILS_DIR)/ft_split_advanced_bonus.c	\
		$(UTILS_DIR)/utils_bonus.c

OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS	= $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

# Bibliotheques
PRINTF_A	= $(PRINTF_DIR)/libftprintf.a
LIBFT_A		= $(LIBFT_DIR)/libft.a

# Compileur et flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3 -I $(INCLUDE_DIR)
LIBS		= $(PRINTF_A) $(LIBFT_A)

# Rules
all:		$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(SRC_DIR) $(OBJ_DIR)/$(GNL_DIR) $(OBJ_DIR)/$(UTILS_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ) $(PRINTF_A) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(NAME) compilé avec succès."

bonus:		$(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(PRINTF_A) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBS) -o $(NAME_BONUS)
	@echo "$(NAME_BONUS) compilé avec succès."

$(PRINTF_A):
	@echo "Compilation de ft_printf..."
	@$(MAKE) -s -C $(PRINTF_DIR)

$(LIBFT_A):
	@echo "Compilation de LIBFT..."
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@$(MAKE) -s clean -C $(PRINTF_DIR)
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage des fichiers objets terminé."

fclean:		clean
	@$(MAKE) -s fclean -C $(PRINTF_DIR)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "Nettoyage complet terminé."

re:			fclean all

re_bonus:	fclean bonus

.PHONY:		all clean fclean re bonus re_bonus
