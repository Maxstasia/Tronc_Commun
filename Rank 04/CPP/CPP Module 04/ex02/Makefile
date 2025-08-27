# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 14:20:13 by mstasiak          #+#    #+#              #
#    Updated: 2025/08/27 13:10:13 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ex02
NAME_ERROR	= ex02_error

# Dossiers
OBJ_DIR		= ./obj

INCLUDE_DIR	= ./include
SOURCES_DIR	= ./sources

# Sources et objets
SRC	=									\
		main.cpp						\
		\
		$(SOURCES_DIR)/Animal.cpp		\
		$(SOURCES_DIR)/Dog.cpp			\
		$(SOURCES_DIR)/Cat.cpp			\
		$(SOURCES_DIR)/Brain.cpp		\
		$(SOURCES_DIR)/WrongAnimal.cpp	\
		$(SOURCES_DIR)/WrongCat.cpp

SRC_ERROR	=							\
		test_error.cpp					\
		\
		$(SOURCES_DIR)/Animal.cpp		\
		$(SOURCES_DIR)/Dog.cpp			\
		$(SOURCES_DIR)/Cat.cpp			\
		$(SOURCES_DIR)/Brain.cpp		\
		$(SOURCES_DIR)/WrongAnimal.cpp	\
		$(SOURCES_DIR)/WrongCat.cpp

OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDS = $(SRC:%.c=$(OBJ_DIR)/%.d)

OBJ_ERROR = $(SRC_ERROR:%.cpp=$(OBJ_DIR)/%.o)
DEPENDS_ERROR = $(SRC_ERROR:%.c=$(OBJ_DIR)/%.d)

# Compilateur et flags
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -I $(INCLUDE_DIR)

# Règles de compilation
all: $(NAME)
error: $(NAME_ERROR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(SOURCES_DIR)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compilé avec succès."

$(NAME_ERROR): $(OBJ_ERROR)
	@$(CC) $(CFLAGS) $(OBJ_ERROR) -o $(NAME_ERROR)
	@echo "$(NAME_ERROR) compilé avec succès."

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage des fichiers objets terminé."

fclean: clean
	@rm -f $(NAME) $(NAME_ERROR)
	@echo "Nettoyage complet terminé."

re: fclean all

.PHONY: all clean fclean re error