# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/27 14:51:00 by rcini-ha          #+#    #+#              #
#    Updated: 2026/01/28 13:52:46 by rcini-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv
OBJDIR = obj
SRCS = \
	src/main.cpp \
	src/Utils/FileUtils.cpp \
	src/Utils/StringUtils.cpp \
	src/Config/Tokenizer/Tokenizer.cpp \
	src/Config/Validator/Validator.cpp \
	src/Config/Validator/ValidatorSemantic.cpp \
	src/Config/MimeTypeRegistry/MimeTypeRegistry.cpp \
	src/Config/DirectiveRegistry/DirectiveRegistry.cpp \
	src/Config/Loader/LoaderAccessor.cpp \
	src/Config/Loader/Loader.cpp \
	src/Config/Parser/Parser.cpp \
	src/Config/Parser/ParserLocation.cpp \
	src/Config/Parser/ParserServer.cpp \
	src/Network/EventManager/EventManager.cpp \
	src/Network/Server/Server.cpp \
	src/Network/Server/ServerAccessor.cpp \
	src/Network/Server/Location/Location.cpp \
	src/Network/Server/ServerSocket.cpp \
	src/HTTP/Client/Client.cpp \
	src/HTTP/Client/ClientAccessor.cpp \
	src/HTTP/Request/Request.cpp \
	src/HTTP/Request/RequestAccessor.cpp \
	src/HTTP/Request/ParserRequest.cpp \
	src/HTTP/Response/Response.cpp \
	src/HTTP/Response/ResponseAccessor.cpp \
	src/HTTP/RequestProcessor/RequestProcessor.cpp \
	src/Manager/ClientManager/ClientManager.cpp \
	src/Manager/ManagerServer/ManagerServer.cpp \
	src/Manager/ManagerServer/ManagerServerBuild.cpp \
	src/Manager/ManagerServer/ManagerServerPrint.cpp \
	src/Manager/ManagerServer/ManagerServerEventLoop.cpp \
	src/Manager/ManagerServer/ManagerServerAccessor.cpp \

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
CXX = c++
CC = gcc
INCLUDES = -Isrc/Utils -Isrc/Config/Loader -Isrc/Config/Parser -Isrc/Config/Tokenizer -Isrc/Config/Validator -Isrc/Config/MimeTypeRegistry -Isrc/Config/DirectiveRegistry -Isrc/Network/EventManager -Isrc/Network/Server -Isrc/Network/Server/Location -Isrc/HTTP/Client -Isrc/HTTP/Request -Isrc/HTTP/Response -Isrc/HTTP/RequestProcessor -Isrc/Manager/ClientManager -Isrc/Manager/ManagerServer
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 $(INCLUDES)
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Colors
VERBOSE ?= 1
ifeq ($(VERBOSE),1)
  V :=
else
  V := @
endif

RED = \033[1;31m
GREEN = \033[1;32m
RESET = \033[0m

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	$(V)mkdir -p $(OBJDIR)

DEP = $(OBJS:.o=.d)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

$(NAME): $(OBJS)
	$(V)$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)[$(NAME)] Executable created ✅$(RESET)"

clean:
	@echo "$(RED)[$(NAME)] Cleaning objects$(RESET)"
	$(V)$(RM) -r $(OBJDIR)

fclean: clean
	@echo "$(RED)[$(NAME)] Cleaning all files$(RESET)"
	$(V)$(RM) $(NAME) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re test
.DEFAULT_GOAL := all
