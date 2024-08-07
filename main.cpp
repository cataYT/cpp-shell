#include <iostream>

#include "functions.hpp"

#define BOLD "\033[1m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"

int main(int argc, char *argv[], char *envp[]) {
    bool running = true;
    std::cout << "Welcome to my customized shell!!" << std::endl;
    std::string input;
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    if (name.empty()) {
        name = "cata";
    }
    while (running) {
        std::cout << BOLD << MAGENTA << name << GREEN << "$ " << RESET;
        std::getline(std::cin, input);

        for (char &c : input) {
            c = std::tolower(c);
        }
        
        if (input == "help") {
            help();
        } else if (input == "touch") {
            try {
                std::string fileName;
                std::cout << "Enter file name: ";
                std::getline(std::cin, fileName);
                if (fileName.empty()) {
                    std::cerr << "Enter a valid file name" << std::endl;
                }
                touch(fileName);
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (input == "mkdir") {
            try {
                std::string dirName;
                std::cout << "Enter directory name: ";
                std::getline(std::cin, dirName);
                if (dirName.empty()) {
                    std::cerr << "Enter a valid directory name" << std::endl;
                }
                mkdir(dirName);
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (input == "echo") {
            try {
                std::string text;
                std::cout << "Enter the text: ";
                std::getline(std::cin, text);
                if (text.empty()) {
                    std::cerr << "Enter a valid text" << std::endl;
                }
                echo(text);            
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (input == "cat") {
            try {
                std::string fileName;
                std::cout << "Enter file name: ";
                std::getline(std::cin, fileName);
                if (fileName.empty()) {
                    std::cerr << "Enter a valid file name" << std::endl;
                }
                cat(fileName);
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (input == "randomimg") {
            randomimg();
        } else if (input == "clear") {
            clear();
        } else if (input == "rf") {
            try {
                std::string fileName;
                std::cout << "Enter the file name: ";
                std::getline(std::cin, fileName);
                if (fileName.empty()) {
                    std::cerr << "Enter a valid file name" << std::endl;
                }
                rf(fileName);
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if(input == "rmdir") {
            try {
                std::string dirName;
                std::cout << "Enter the directory name: ";
                std::getline(std::cin, dirName);
                if (dirName.empty()) {
                    std::cerr << "Enter a valid directory name" << std::endl;
                }
                rmdir(dirName);
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (input == "calc") {
            try {
                long double num1;
                std::cout << "Enter number 1: ";
                std::cin >> num1;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

                long double num2;
                std::cout << "Enter number 2: ";
                std::cin >> num2;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
                
                std::string operation;
                std::cout << "Enter a operation: ";
                std::getline(std::cin, operation);
                calc(operation, num1, num2);
            } catch (const std::logic_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (input == "xor") {
            try {
                std::string str;
                std::cout << "Enter a string: ";
                std::getline(std::cin, str);
                if (str.empty()) {
                    std::cerr << "Enter a valid string" << std::endl;
                }
                char key;
                std::cout << "Enter a key: ";
                std::cin.get(key);
                if (key == '\0') {
                    std::cerr << "Invalid key" << std::endl;
                }
                std::cout << xorEncrypt(str, &key) << std::endl;
            } catch (std::logic_error &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (input == "ls") {
            ls();
        } else if (input == "exit") {
            running = false;
        } else if (input == "pwd") {
            pwd();
        } else if (input == "sha512") {
            std::string str;
            std::cout << "Enter a string: ";
            std::getline(std::cin, str);
            if (str.empty()) {
                std::cerr << "Enter a valid string" << std::endl;
            }
            std::string result = sha512(str);
            if (!result.empty()) {
                std::cout << result << std::endl;
            }
        } else if (input == "verify") {
            std::string hash1;
            std::cout << "Enter the directory name: ";
            std::getline(std::cin, hash1);
            if (hash1.empty()) {
                std::cerr << "Please enter first hash" << std::endl;
            }

            std::string hash2;
            std::cout << "Enter the directory name: ";
            std::getline(std::cin, hash2);
            if (hash2.empty()) {
                std::cerr << "Please enter second hash" << std::endl;
            }

            bool result = verify_sha512(hash1, hash2);
            if (result) {
                std::cout << "SHA512 Matched!" << std::endl;
            } else {
                std::cout << "SHA512 did not match!" << std::endl;
            }
        } else {
            std::cerr << "Invalid input" << std::endl;
        }
    }
    return 0;
}