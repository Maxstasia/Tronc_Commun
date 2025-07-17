# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/18 11:12:32 by mstasiak          #+#    #+#              #
#    Updated: 2025/07/17 14:30:40 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# Dossiers
OBJ_DIR		= ./obj

PIPEX_DIR	= ./pipex
P_SRC_DIR	= $(PIPEX_DIR)/pipex_sources
P_UTILS_DIR	= $(PIPEX_DIR)/pipex_utils

BUILTIN_DIR	= ./builtins
INCLUDE_DIR	= ./include
UTILS_DIR	= ./utils
PARSER_DIR	= ./parsing
GNL_DIR		= $(INCLUDE_DIR)/get_next_line
LIBFT_DIR	= $(INCLUDE_DIR)/Libft

# Sources et objets
SRC			=									\
		main_norm.c								\
		main.c									\
		minishell.c								\
		minishell2.c							\
		\
		$(PARSER_DIR)/lexer.c					\
		$(PARSER_DIR)/lexer_redir.c				\
		$(PARSER_DIR)/lexer_redir2.c			\
		$(PARSER_DIR)/lexer_redir3.c			\
		$(PARSER_DIR)/parser.c					\
		$(PARSER_DIR)/parsing.c					\
		$(PARSER_DIR)/parsing_pipe.c			\
		$(PARSER_DIR)/redir.c					\
		$(PARSER_DIR)/redir2.c					\
		$(PARSER_DIR)/redir3.c					\
		\
		$(UTILS_DIR)/cleanup.c					\
		$(UTILS_DIR)/cleanup2.c					\
		$(UTILS_DIR)/envp.c						\
		$(UTILS_DIR)/init.c						\
		$(UTILS_DIR)/init2.c					\
		$(UTILS_DIR)/redirection_case_utils.c	\
		$(UTILS_DIR)/signals.c					\
		$(UTILS_DIR)/utils.c					\
		$(UTILS_DIR)/utils2.c					\
		$(UTILS_DIR)/utils3.c					\
		$(UTILS_DIR)/utils4.c					\
		\
		$(BUILTIN_DIR)/cd.c						\
		$(BUILTIN_DIR)/echo.c					\
		$(BUILTIN_DIR)/env.c					\
		$(BUILTIN_DIR)/exit.c					\
		$(BUILTIN_DIR)/export_print.c			\
		$(BUILTIN_DIR)/export_utils.c			\
		$(BUILTIN_DIR)/export.c					\
		$(BUILTIN_DIR)/pwd.c					\
		$(BUILTIN_DIR)/unset.c					\
		$(BUILTIN_DIR)/utils_builtin.c			\
		\
		$(GNL_DIR)/get_next_line.c				\
		$(GNL_DIR)/get_next_line_utils.c		\
		\
		\
		$(PIPEX_DIR)/pipex_executor.c			\
		$(PIPEX_DIR)/pipex_executor2.c			\
		\
		$(P_SRC_DIR)/error.c					\
		$(P_SRC_DIR)/error2.c					\
		$(P_SRC_DIR)/pipex.c					\
		$(P_SRC_DIR)/heredoc.c					\
		$(P_SRC_DIR)/heredoc2.c					\
		$(P_SRC_DIR)/pipex_redir.c				\
		$(P_SRC_DIR)/pipex_redir2.c				\
		$(P_SRC_DIR)/pipex_redir3.c				\
		\
		$(P_UTILS_DIR)/ft_split_advanced.c		\
		$(P_UTILS_DIR)/ft_split_advanced2.c		\
		$(P_UTILS_DIR)/ft_split_advanced3.c		\
		$(P_UTILS_DIR)/quotes.c					\
		$(P_UTILS_DIR)/quotes2.c				\
		$(P_UTILS_DIR)/utils_pipex.c			\
		$(P_UTILS_DIR)/utils2_pipex.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPENDS = $(SRC:%.c=$(OBJ_DIR)/%.d)

# Bibliothèques
LIBFT_A = $(LIBFT_DIR)/libft.a

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -MMD -I $(INCLUDE_DIR)
LIBS = $(LIBFT_A) -lreadline

# Règles de compilation
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSER_DIR) $(OBJ_DIR)/$(UTILS_DIR) $(OBJ_DIR)/$(BUILTIN_DIR) $(OBJ_DIR)/$(GNL_DIR) $(OBJ_DIR)/$(P_SRC_DIR) $(OBJ_DIR)/$(P_UTILS_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(NAME) compilé avec succès."

$(LIBFT_A):
	@echo "Compilation de LIBFT..."
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage des fichiers objets terminé."

fclean: clean
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "Nettoyage complet terminé."

re: fclean all

.PHONY: all clean fclean re

-include ${DEPENDS}
