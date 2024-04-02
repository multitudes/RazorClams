# dolphintests

> “For instance, on the planet Earth, man had always assumed that he was more intelligent than dolphins because he had achieved so much—the wheel, New York, wars and so on—whilst all the dolphins had ever done was muck about in the water having a good time. But conversely, the dolphins had always believed that they were far more intelligent than man—for precisely the same reasons.” ― Douglas Adams, The Hitchhiker's Guide to the Galaxy 

A small suite of tests for the libft project at 42 written in C.

## The project
The first project at 42 is to re-code a set of the libc functions, as defined in their man. In part 2 there some additional functions to create and at the end a bonus part with linked lists. 

## Usage
No installation needed. 
Just download the repo and copy it in your libft project folder. Compile your library first with its own makefile. Then cd into the dolphintest folder cloned from GitHub and run `make` again. The output should be similar to this one below:

```c
make      
cc -Wall -Wextra -Werror    part1_tests.c  -lm -lbsd ../libft.a -o part1_tests
cc -Wall -Wextra -Werror    part2_tests.c  -lm -lbsd ../libft.a -o part2_tests
sh ./runtests.sh
Running unit tests:
----
RUNNING: ./part1_tests
ALL TESTS PASSED
Tests run: 23
part1_tests PASS
----
RUNNING: ./part2_tests
ALL TESTS PASSED
Tests run: 11
part2_tests PASS
```

Or if you want to test the bonus functions run `make bonus` instead. But this assumes that you compiled already your library with the bonus functions and that your library name is libft_bonus.a.

Example:

```c
make bonus
cc -Wall -Wextra -Werror    zbonus_tests.c  -lm -lbsd ../libft_bonus.a -o zbonus_tests
sh ./runtests.sh
Running unit tests:
----
RUNNING: ./part1_tests
ALL TESTS PASSED
Tests run: 23
part1_tests PASS
----
RUNNING: ./part2_tests
ALL TESTS PASSED
Tests run: 11
part2_tests PASS
----
RUNNING: ./zbonus_tests
ALL TESTS PASSED
Tests run: 9
zbonus_tests PASS
```

Other commands are or course `make clean` and even `make valgrind` (on a Linux system). 

It will create a test log file with the debugging output of the tests. 

To work you need to be in a subdirectory of your libft project.
Also it assumes that the name of your library is libft.a and libft_bonus.a if the bonus files are compiled together.

## Acknoledgements
I took inspiration from the debugging and test tools found in Zed Shaw "learn C the hard way" book and tutorial! Thank you Zed!

## Bugs and suggestions
They are always welcome. Please file under issues. :)

