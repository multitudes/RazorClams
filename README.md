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




