# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 16:30:00 by mstasiak          #+#    #+#              #
#    Updated: 2025/08/11 17:26:59 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = replace

# Dossiers
OBJ_DIR		= ./obj

INCLUDE_DIR	= ./include
SOURCE_DIR	= ./sources

# Sources et objets
SRC			=							\
		main.cpp						\
		\
		$(SOURCE_DIR)/FileReplacer.cpp

OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDS = $(SRC:%.c=$(OBJ_DIR)/%.d)

# Compilateur et flags
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -I $(INCLUDE_DIR)

# Règles de compilation
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(SOURCE_DIR)

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
