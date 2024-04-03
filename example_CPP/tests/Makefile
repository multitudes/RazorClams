CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXX = c++

# the file to tests (SUT = System Under Test)
SUT_SRCS = ../megaphone.cpp
# will be compiled into object files
SUT_OBJS = $(SUT_SRCS:.cpp=.o)

# my test files - each one has a main and will 
# be compiled into an executable
TEST_SRCS= part1_tests.cpp part2_tests.cpp
# this substitution create files without the extension
# they will become the executables
TESTS=$(patsubst %.cpp,%,$(TEST_SRCS))

# the target build
all: tests
	
tests: $(TESTS) runtests

$(TESTS): $(SUT_OBJS) $(TEST_SRCS) 
	$(CXX) $(SUT_OBJS) $@.cpp -o $@

runtests:
	sh ./runtests.sh

clean:
	rm -f *.o
	rm -f tests.log

fclean: clean
	rm -rf $(TESTS)

re: fclean tests

.PHONY: tests 

#will not work on mac
valgrind:
	@echo
	@echo "==================\nLaunching valgrind..."
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)
