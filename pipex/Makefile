# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 16:22:48 by mstasiak          #+#    #+#              #
#    Updated: 2025/02/17 14:44:05 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

# Sources et objets
OBJ			= $(SRC:.c=.o)
SRC			=									\
		main.c

# Dossiers
INCLUDE_DIR	= ./includes
PRINTF_DIR	= $(INCLUDE_DIR)/ft_printf
LIBFT_DIR	= $(INCLUDE_DIR)/Libft

# Bibliotheques
PRINTF_A	= $(PRINTF_DIR)/libftprintf.a
LIBFT_A		= $(LIBFT_DIR)/libft.a

# Compileur et flags
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3 -I $(INCLUDE_DIR)
LIBS		= $(PRINTF_A) $(LIBFT_A)

# Rules
all:		$(NAME)

$(NAME):	$(OBJ) $(PRINTF_A) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF_A):
	@echo "Compilation de ft_printf..."
	@$(MAKE) -s -C $(PRINTF_DIR)

$(LIBFT_A):
	@echo "Compilation de LIBFT..."
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@$(MAKE) -s clean -C $(PRINTF_DIR) $(LIBFT_DIR)
	@rm -f $(OBJ)
	@echo "Nettoyage des fichiers objets terminé."

fclean:		clean
	@$(MAKE) -s fclean -C $(PRINTF_DIR) $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "Nettoyage complet terminé."

re:			fclean all

.PHONY:		all clean fclean re
