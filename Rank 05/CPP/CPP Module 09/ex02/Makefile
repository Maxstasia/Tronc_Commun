NAME		= PmergeMe
NAME_Comments	= PmergeMeComment

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS		= main.cpp \
			  PmergeMe.cpp

SRCS_Comments	= main.cpp \
				  PmergeMeComment.cpp

OBJS		= $(SRCS:.cpp=.o)
OBJS_Comments	= $(SRCS_Comments:.cpp=.o)

all: $(NAME)
comment: $(NAME_Comments)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(NAME_Comments): $(OBJS_Comments)
	$(CXX) $(CXXFLAGS) $(OBJS_Comments) -o $(NAME_Comments)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_Comments)

fclean: clean
	rm -f $(NAME) $(NAME_Comments)

re: fclean all

.PHONY: all clean fclean re comment
