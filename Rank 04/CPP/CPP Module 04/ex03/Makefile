# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 13:42:23 by mstasiak          #+#    #+#              #
#    Updated: 2025/08/27 13:42:24 by mstasiak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = interface_recap

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = sources
INCDIR = include
OBJDIR = obj

SOURCES = main.cpp \
		  $(SRCDIR)/AMateria.cpp \
		  $(SRCDIR)/Ice.cpp \
		  $(SRCDIR)/Cure.cpp \
		  $(SRCDIR)/Character.cpp \
		  $(SRCDIR)/MateriaSource.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

INCLUDES = -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
