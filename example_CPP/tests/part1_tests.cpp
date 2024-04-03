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

	return NULL;
}

// This is the entry point for the test suite
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
	debug("output: %s", output.str().c_str());

	// check if the output is as expected
	std::string expectedOutput = "HELLO\n";
	// these are c string so I use strcmp or strncmp etc
	my_assert(strcmp(output.str().c_str(), expectedOutput.c_str()) == 0, "should be : HELLO");
	
	/*
	This line restores the original buffer of std::cout, 
	undoing the redirection to output.
	*/
	std::cout.rdbuf(oldCoutBuffer);
	return NULL;
}


const char *test_megaphone_loud2(){
	std::stringstream output;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	char* argv[] = { (char*)"./megaphone",(char*)"hello world" };
	int argc = 2;

	megaphone(argc, argv);
	debug("output: %s", output.str().c_str());
	std::string expectedOutput = "HELLO WORLD\n";
	my_assert(strcmp(output.str().c_str(), expectedOutput.c_str()) == 0, "should be : HELLO WORLD");

	std::cout.rdbuf(oldCoutBuffer);
	return NULL;
}

const char *test_megaphone_unbearable(){
	std::stringstream output;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	char* argv[] = { (char*)"./megaphone" };
	int argc = 1;

	megaphone(argc, argv);
	debug("output: %s", output.str().c_str());
 	std::string expectedOutput = "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	my_assert(output.str() == expectedOutput, "should be: Loud and um... ");

	std::cout.rdbuf(oldCoutBuffer);

	return NULL;
}


const char *all_tests()
{
	// necessary to start the test suite
	suite_start();
	
	// run the tests
	run_test(test_megaphone_loud);
	run_test(test_megaphone_loud2);	
	run_test(test_megaphone_unbearable);		
	
	return NULL;
}

// works as a main
RUN_TESTS(all_tests);

