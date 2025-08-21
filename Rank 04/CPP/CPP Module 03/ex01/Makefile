# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 14:20:13 by mstasiak          #+#    #+#              #
#    Updated: 2025/08/21 16:50:46 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ex01

# Dossiers
OBJ_DIR		= ./obj

INCLUDE_DIR	= ./include
SOURCES_DIR	= ./sources

# Sources et objets
SRC			=						\
		main.cpp					\
		\
		$(SOURCES_DIR)/ClapTrap.cpp	\
		$(SOURCES_DIR)/ScavTrap.cpp

OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDS = $(SRC:%.c=$(OBJ_DIR)/%.d)

# Compilateur et flags
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -I $(INCLUDE_DIR)

# Règles de compilation
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(SOURCES_DIR)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compilé avec succès."

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage des fichiers objets terminé."

fclean: clean
	@rm -f $(NAME)
	@echo "Nettoyage complet terminé."

re: fclean all

.PHONY: all clean fclean re