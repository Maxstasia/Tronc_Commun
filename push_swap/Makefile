# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 16:22:48 by mstasiak          #+#    #+#              #
#    Updated: 2025/01/30 13:04:50 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap

# Sources et objets
OBJ			= $(SRC:.c=.o)
SRC			=						\
		main.c						\
		sources/error.c				\
		sources/ft_split.c			\
		sources/function_Libft.c	\
		sources/input.c				\
		sources/instructions.c		\
		sources/quick_sort.c		\
		sources/sort.c				\
		sources/stack.c				\
		sources/utils.c

# Dossiers
INCLUDE_DIR	= ./includes
PRINTF_DIR	= $(INCLUDE_DIR)/ft_printf

# Bibliotheques
PRINTF_A	= $(PRINTF_DIR)/libftprintf.a

# Compileur et flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I $(INCLUDE_DIR)
LIBS		= $(PRINTF_A)

# Rules
all:		$(NAME)

$(NAME):	$(OBJ) $(PRINTF_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF_A):
	@echo "Compilation de ft_printf..."
	@$(MAKE) -s -C $(PRINTF_DIR)

clean:
	@$(MAKE) -s clean -C $(PRINTF_DIR)
	@rm -f $(OBJ)
	@echo "Nettoyage des fichiers objets terminé."

fclean:		clean
	@$(MAKE) -s fclean -C $(PRINTF_DIR)
	@rm -f $(NAME)
	@echo "Nettoyage complet terminé."

re:			fclean all

.PHONY:		all clean fclean re
