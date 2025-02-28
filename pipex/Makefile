# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 16:22:48 by mstasiak          #+#    #+#              #
#    Updated: 2025/02/28 14:00:42 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
NAME_BONUS	= pipex_bonus

# Sources et objets
OBJ			= $(SRC:.c=.o)
SRC			=									\
		main.c									\
		\
		sources/utils.c

OBJ_BONUS	= $(SRC_BONUS:.c=.o)
SRC_BONUS	=									\
		main_bonus.c							\
		\
		sources/utils_bonus.c

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
	@echo "$(NAME) compilé avec succès."

bonus:		$(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(PRINTF_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBS) -o $(NAME_BONUS)
	@echo "$(NAME_BONUS) compilé avec succès."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF_A):
	@echo "Compilation de ft_printf..."
	@$(MAKE) -s -C $(PRINTF_DIR)

$(LIBFT_A):
	@echo "Compilation de LIBFT..."
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@$(MAKE) -s clean -C $(PRINTF_DIR)
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "Nettoyage des fichiers objets terminé."

fclean:		clean
	@$(MAKE) -s fclean -C $(PRINTF_DIR)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "Nettoyage complet terminé."

re:			fclean all

re_bonus:	fclean bonus

.PHONY:		all clean fclean re bonus re_bonus
