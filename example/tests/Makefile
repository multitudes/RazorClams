CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXXFLAGS += -Wno-shadow
CXX = c++

# the file to tests (SUT = System Under Test)
SUT_SRCS = ../megaphone.cpp
# will be compiled into object files
SUT_OBJS = $(SUT_SRCS:.cpp=.o)

# my test files - each one has a main and will 
# be compiled into an executable
TEST_SRC= part1_tests.cpp part2_tests.cpp
# this substitution create files without the extension
# they will become the executables
TESTS=$(patsubst %.cpp,%,$(TEST_SRC))

# the target build
all: tests
	
tests: $(TESTS) runtests

$(TESTS): $(SUT_OBJS) $(TEST_SRC) 
	$(CXX) $(SUT_OBJS) $@.cpp -o $@

runtests:
	sh ./runtests.sh

# ending in ~ are sometimes VIM files
clean:
	@echo ""
	@echo "==================\ncleaning all object files and log"
	rm -f *.o
	rm -f tests.log
	find  .  -name ".*~" -delete -print
	$(CLEAN_MAC)

# mac sometimes adds these files expecially in Xcode. 
ifeq ($(shell uname),Darwin)
CLEAN_MAC = rm -rf `find . -name "*.dSYM" -print`
else
CLEAN_MAC = 
endif

fclean: clean
	@echo
	@echo "==================\ncleaning all test files and executables"
	rm -rf $(TESTS)
	@echo 

re: fclean tests

.PHONY: tests 

#will not work on mac
valgrind:
	@echo
	@echo "==================\nLaunching valgrind..."
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)
