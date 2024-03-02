#include <iostream>

#ifdef _WIN32
    const std::string open_command = "start";
#elif __APPLE__
    const std::string open_command = "open";
#else // Linux
    const std::string open_command = "xdg-open"; // run sudo apt-get install xdg-utils
#endif

#include "randomimg.hpp"
#include "functions.hpp"

int main(int argc, char **argv, char **envp) {
    bool running = true;
    std::string input;
    std::cout << "Welcome to the shell!" << std::endl;
    while (running) {
        std::cout << "Enter the command (help for all commands): ";
        std::getline(std::cin, input);
        for (char &c : input) {
            c = std::tolower(c);
        }
        if (input == "help") {
            help();
        } else if (input == "touch") {
            touch();
        } else if (input == "mkdir") {
            mkdir();
        } else if (input == "echo") {
            echo();
        } else if (input == "cat") {
            cat();
        } else if (input == "randomimg") {
            randomimg();
        } else if (input == "clear") {
            clear();
        } else if (input == "rf") {
            rf();
        } else if(input == "rmdir") {
            rmdir();
        } else if (input == "exit") {
            running = false;
        } else {
            std::cout << "Invalid input" << std::endl;
        }
    }

    return 0;
}