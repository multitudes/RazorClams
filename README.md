# RazorClams
Writing a razor fast suite of tests for my C++ student assignments. (I made a folder called tests_c for with the c version)

⚠️ This is intentionally written in simple code as a learning opportunity, it is not intended to be a fully fledged test suite! ⚠️	

What I really like about this test suite is that it is fast. It runs the tests and I get notified only when there is a test failing.  
It is easy to output debug messages to a log file as well. 

There is a lot to be learned by writing your own tests.  
- handle redirections, for example I wnt to read what is being printed to the console.  
- write debug messages to a log.txt file.  
- integrate the tests in the main makefile for a semi continuous integration.
- when coding be more confident in changing and updating functions in a large codebase, knowing that I did not break anything (if I wrote the tests correctly)
- Write edgy test cases.
- Try some TDD or test driven development...

To add the tests modifying the existing makefile in the existing project with:
```
tests:
	make -C tests
```
and copy the tests folder into the root...

The main idea is that running `make` in development will trigger the tests everytime.  This can be modified to run the tests with a `make tests` instead.
I will show how this all comes together. 

## A very easy example

SUT or system under test is our program.  
To simplify things, I will use a simple example of a function that takes a string and prints the uppercased string to the console.
The program is called megaphone. (eh!)

This is my megaphone.cpp file.
```cpp
#include <iostream>
#include "megaphone.hpp"

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
This is my makefile to compile `megaphone`

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
- eventually a log file will be produced by the tests. A nice trick is to display the output of the logfile in a separate terminal window like `tail -f tests/tests.log > /dev/pts/4 &` where ` /dev/pts/4` is the device file in Linux that represents a pseudo-terminal (pty). You get it when you execute the command `tty` in the new window.  


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

On the other hand, `c_str()` is a function that returns a pointer to an array that contains a null-terminated sequence of characters (i.e., a C-string) representing the current value of the string object.  

I suggest to download the repo and try it out. run make and make tests in the example folder. The tests are very fast and will stop only if there is an error. You can add as many files and tests as you want in both the SUT and the `partx_tests.cpp` files.

The macros used are the following:
- `debug` will print to the log file. Usage `debug("message %d", 42);`
- 'my_assert' will check a condition and return an error message if it fails. Usage `my_assert(condition, "error message");`
- `run_test` will run a test function and return the error message if it fails. Usage `run_test(test_example);` It expects a function that returns a const char*. If the function returns NULL, the test passes.
- `RUN_TESTS` is a macro that will run all the tests and print the results. it expands to a main. Usage: `RUN_TESTS(all_tests);` It expects a function that returns a const char* and will run all the tests in that function. If the function returns NULL, all the tests pass.

I hope this helps you write your own tests.

## thanks
Special thanks to Zed Shaw for the inspiration. Some of the macros and ideas are found in "Learn C the Hard Way" chapter 30 - "Automated Testing". Great book!
