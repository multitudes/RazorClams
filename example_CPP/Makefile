CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXX = c++

NAME = megaphone

SRCS = megaphone.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests:
	make -C tests

.PHONY: all clean fclean re tests
