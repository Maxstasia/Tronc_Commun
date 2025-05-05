# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 16:22:48 by mstasiak          #+#    #+#              #
#    Updated: 2025/04/15 16:31:01 by mstasiak         ###   ########.fr        #
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
		$(SRC_DIR)/init.c						\
		$(SRC_DIR)/philosopher.c				\
		\
		$(UTILS_DIR)/error.c						\
		$(UTILS_DIR)/monitoring.c				\
		$(UTILS_DIR)/output.c					\
		$(UTILS_DIR)/parsing.c					\
		$(UTILS_DIR)/time.c

OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPENDS		= ${OBJ:.o=.d}

# Compileur et flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -MMD -g3 -I $(INCLUDE_DIR)

# Rules
all:		$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(SRC_DIR) $(OBJ_DIR)/$(UTILS_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -pthread
	@echo "$(NAME) compilé avec succès."

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage des fichiers objets terminé."

fclean:		clean
	@rm -f $(NAME)
	@echo "Nettoyage complet terminé."

re:			fclean all

.PHONY:		all clean fclean re

-include ${DEPENDS}
