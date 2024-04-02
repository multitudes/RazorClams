# RazorClams
Writing a razor fast suite of tests for my C++ student assignments 


There is a lot to be learned by writing your own tests.  
- handle redirections.  
- write debug messages to a log.txt file.  
- integrate the tests in the makefile for a semi continuous integration.
- be more confident in changing and updating functions in a large codebase knowing that you did not break anything (if you wrote the tests correctly)
- Write edgy test cases.
- Try some TDD or test driven development...

The main idea is that running make in development will trigger the tests everytime.  This can be modified to run the tests with a `make tests` instead.
I will show how this all comes together. 

## A very easy example

SUT or system under test is our program.  
To simplify things, I will use a simple program that takes a string and prints the uppercased string to the console.
The program is called megaphone.

This is my megaphone.cpp file.
```cpp
#include <iostream>
#include "megaphone.hpp"
/*
I use std::cout because I am not allowed to use namespaces in this module
*/
int megaphone(int argc, char **argv)
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++) 
		{
			for(int j = 0; argv[i][j]; j++)
				std::cout << (char)toupper(argv[i][j]);
		}
		std::cout << std::endl; 
	}
	else
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	return (0);
}
```

My main.cpp file will just call my function with the arguments from the command line.  

```cpp
#include "megaphone.hpp"

int main(int argc, char **argv)
{
	return (megaphone(argc, argv));
}
```

The header file is just a declaration of the function.  

```cpp
#ifndef MEGAPHONE_HPP
# define MEGAPHONE_HPP

int megaphone(int argc, char **argv);

#endif
```
This is my makefile.
```makefile
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
```

If I run make, I will compile my program and run it with the arguments I give it.  

```bash
$ make
c++ -Wall -Wextra -Werror -std=c++98   -c -o megaphone.o megaphone.cpp
c++ -Wall -Wextra -Werror -std=c++98   -c -o main.o main.cpp
c++ -o megaphone megaphone.o main.o

$ ./megaphone "Hello, World!"
HELLO, WORLD!
```

But running make tests will run the tests in the tests folder.  
  
## Run the tests

To do so I will copy my tests folder in the root of my project.
The tests folder contains the following files.  
- a makefile to compile the tests into executables
- a runtests.sh script to run the tests executables
 - a part1_tests.cpp file that contains the tests. The name can be changed to whatever you want but it has to end with `_tests.cpp`. More than one file can be created like a part2_tests.cpp file etc. Each file will be compiled into an executable called `part1_tests`, `part2_tests` etc. the script will run all the tests executables.
 - a razorclams.hpp file that contains the test macros like the `my_assert` and `debug` macros.
 - eventually a log file will be produced by the tests.

The makefile in the tests folder is the following.

```makefile
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
```

In the makefile you will only need to change the `SUT_SRCS` variables to the files of your program, your system under test.  
The `TEST_SRCS` variable is the list of test files written by you that will contain the tests.  

Example of the tests file.  
```cpp
#include "razorclam_tests.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include "../megaphone.hpp"

/*
This is a test function. It should return NULL if the test passes
debug will print to the log
log_err will print to the error log
my_assert will check a condition and return an error message if it fails
run_test will run a test function and return the error message if it fails
RUN_TESTS will run all the tests and print the results
*/
const char* test_example() {
  // debug("This is a debug message");
	return NULL;
}

const char *all_tests()
{
	// necessary to start the test suite
	suite_start();
	
	// run the tests
	run_test(test_example);
	
	return NULL;
}

// works as a main
RUN_TESTS(all_tests);
```

To write a test to check what is printed to the console, you can write a test as follows for instance :

```cpp
const char *test_megaphone_loud(){
	/* std::stringstream object named output. 
	This object can be used to construct strings using the << operator, 
	just like std::cout. */
	std::stringstream output;

	/*
	This line redirects std::cout to output. 
	This means that anything written to std::cout will now be written 
	to output instead. The original buffer of std::cout is saved 
	in oldCoutBuffer so it can be restored later.
	*/
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	/*
	create an argument list for the megaphone function. 
	This is similar to the argv and argc parameters of 
	the main function.
	*/
	char* argv[] = { (char*)"./megaphone",(char*)"hello" };
	int argc = 2;

	// call the megaphone function with the argument list
	megaphone(argc, argv);
	// not necessary but can be useful to debug - will print to the log file
	debug("output: %s", output.str().c_str());

	// check if the output is as expected
	std::string expectedOutput = "HELLO\n";
	// my_assert is a macro which expects a c string... 
	my_assert(strcmp(output.str().c_str(), expectedOutput.c_str()) == 0, "should be : HELLO");
	
	/*
	This line restores the original buffer of std::cout, 
	undoing the redirection to output.
	*/
	std::cout.rdbuf(oldCoutBuffer);
	return NULL;
}
```
In the code above, we redirect the output of the program to a stringstream object.
The str() function of std::stringstream returns a string object with a copy of the current contents of the stream.  

On the other hand, c_str() is a function that returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) representing the current value of the string object.  

I suggest to download the repo and try it out. run make and make tests in the example folder. The tests are very fast and will stop only if there is an error. You can add as many files and tests as you want in both the SUT and the partx_tests.cpp files.

I hope this helps you write your own tests.
