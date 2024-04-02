#include <iostream>
#include <sstream>
#include <cassert>
#include "../megaphone.hpp"

void test_megaphone() {
    // Test case 1: Single argument
    {
        std::stringstream output;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

        char* argv[] = { (char*)"hello" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        megaphone(argc, argv);

        std::string expectedOutput = "HELLO\n";
        assert(output.str() == expectedOutput);

        std::cout.rdbuf(oldCoutBuffer);
    }

    // Test case 2: Multiple arguments
    {
        std::stringstream output;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

        char* argv[] = { (char*)"hello", (char*)"world" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        megaphone(argc, argv);

        std::string expectedOutput = "HELLO WORLD\n";
        assert(output.str() == expectedOutput);

        std::cout.rdbuf(oldCoutBuffer);
    }

    // Test case 3: No arguments
    {
        std::stringstream output;
        std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

        char* argv[] = { (char*)"program_name" };
        int argc = sizeof(argv) / sizeof(argv[0]);

        megaphone(argc, argv);

        std::string expectedOutput = "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
        assert(output.str() == expectedOutput);

        std::cout.rdbuf(oldCoutBuffer);
    }
}

int main() {
    test_megaphone();
    return 0;
}