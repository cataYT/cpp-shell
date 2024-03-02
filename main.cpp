#include <iostream>

#include "functions.hpp"

int main(int argc, char *argv[], char *envp[]) {

    if (argc == 1) {
        std::cout << "Enter something" << std::endl;
        return 1;
    } else if (argc > 3) {
        std::cout << "Too many arguments" << std::endl;
        return 1;
    }

    std::string input;
    input = argv[1];

    for (char &c : input) {
        c = std::tolower(c);
    }

    if (input == "help") {
        help();
    } else if (input == "touch") {
        try {
            touch(argv[2]);
        } catch (const std::logic_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else if (input == "mkdir") {
        try {
            mkdir(argv[2]);
        } catch (const std::logic_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else if (input == "echo") {
        try {
            echo(argv[2]);            
        } catch (const std::logic_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else if (input == "cat") {
        try {
            cat(argv[2]);
        } catch (const std::logic_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else if (input == "randomimg") {
        randomimg();
    } else if (input == "clear") {
        clear();
    } else if (input == "rf") {
        try {
            rf(argv[2]);
        } catch (const std::logic_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else if(input == "rmdir") {
        try {
            rmdir(argv[2]);
        } catch (const std::logic_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else if (input == "calc") {
        calc();
    } else {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }
    return 0;
}