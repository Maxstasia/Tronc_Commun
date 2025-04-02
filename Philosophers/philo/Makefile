# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 16:22:48 by mstasiak          #+#    #+#              #
#    Updated: 2025/04/02 16:14:14 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

# Dossiers
OBJ_DIR		= ./obj
UTILS_DIR	= ./utils
SRC_DIR		= ./sources
INCLUDE_DIR	= ./includes

# Sources et objets
SRC			=									\
		main.c									\
		\
		$(SRC_DIR)/error.c						\
		$(SRC_DIR)/philo.c						\
		\
		$(UTILS_DIR)/utils.c

OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

# Compileur et flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3 -I $(INCLUDE_DIR)

# Rules
all:		$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(SRC_DIR) $(OBJ_DIR)/$(UTILS_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compilé avec succès."

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage des fichiers objets terminé."

fclean:		clean
	@rm -f $(NAME)
	@echo "Nettoyage complet terminé."

re:			fclean all

.PHONY:		all clean fclean re
