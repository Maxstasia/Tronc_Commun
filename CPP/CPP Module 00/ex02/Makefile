# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 15:56:48 by mstasiak          #+#    #+#              #
#    Updated: 2025/07/17 16:08:00 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 16:00:00 by mstasiak          #+#    #+#             #
#    Updated: 2025/07/17 16:30:00 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = account

# Dossiers
OBJ_DIR = ./obj

# Sources et objets
SRC = Account.cpp tests.cpp

OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# Compilateur et flags
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

# Règles de compilation
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compiled successfully."

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable cleaned."

re: fclean all

.PHONY: all clean fclean re
