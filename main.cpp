#include <iostream> // for basic io functions and types
#include <fstream> // for file creation and file reading
#include <filesystem> // for directory creation
#include <cstdlib> // for std::system
#include <string>  // for std::string

#ifdef _WIN32
    const std::string open_command = "start";
#elif __APPLE__
    const std::string open_command = "open";
#else // Linux
    const std::string open_command = "xdg-open"; // run sudo apt-get install xdg-utils
#endif

#include "randomimg.hpp"

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
            std::cout << "Available commands:\nhelp: brings up this menu\nexit: exits the shell\ntouch: creates file\nmkdir: creates directory\necho: prints text\ncat: read from file and display on the shell\nrandomimg: generates random image" << std::endl;
        } else if (input == "touch") {
            std::string fileName;
            std::cout << "Enter the name of the file: ";
            std::getline(std::cin, fileName);
            if (fileName == "") {
                std::cout << "Enter a valid file name" << std::endl;
            }
            std::ofstream file(fileName);
            std::cout << "File created" << std::endl;
            file.close();
        } else if (input == "mkdir") {
            std::string dirName;
            std::cout << "Enter the directory name: ";
            std::getline(std::cin, dirName);
            if (dirName == "") {
                std::cout << "Enter a valid directory name" << std::endl;
            }

            std::filesystem::path currentPath = std::filesystem::current_path();

            std::filesystem::path newDirectoryPath = currentPath / dirName;

            if (std::filesystem::exists(newDirectoryPath)) {
                std::cerr << "Directory already exists!" << std::endl;
                return 1;
            }

            if (std::filesystem::create_directory(newDirectoryPath)) {
                std::cout << "Directory created successfully!" << std::endl;
            } else {
                std::cerr << "Failed to create directory!" << std::endl;
                return 1;
            }
        } else if (input == "echo") {
            std::cout << "Enter text: ";
            std::string text;
            std::getline(std::cin, text);
            std::cout << text << std::endl;
        } else if (input == "cat") {
            std::string fileName;
            std::cout << "Enter the file: ";
            std::getline(std::cin, fileName);

            if (fileName == "") {
                std::cout << "Enter a valid file name" << std::endl;
            }

            std::ifstream file(fileName);
            std::string line;

            while (std::getline(file, line)) {
                std::cout << line << std::endl;
            }
            
            file.close();
        } else if (input == "randomimg") {
            std::string result = getRandImg();
            if (result == "") {
                std::cout << "Unsplashed api get request failed" << std::endl;
            } else {
                std::string command = open_command + " " + std::string(result);
                int resp = std::system(command.c_str());
                
                if (resp == 0) {
                    std::cout << "Image opened successfully" << std::endl;
                } else {
                    std::cout << "Failed to open image" << std::endl;
                }
            }
        } else if (input == "clear") {
           std::system("clear");
        } else if (input == "rf") {
            std::string fileName;
            std::cout << "Enter file name to delete: ";
            std::getline(std::cin, fileName);
            if (fileName == "") {
                std::cout << "Enter a valid file name" << std::endl;
            }
            remove(fileName.c_str());
            std::cout << "Removed file successfully" << std::endl;
        } else if(input == "rmdir") {
            std::string dirName;
            std::cout << "Enter the directory name to remove: ";
            std::getline(std::cin, dirName);
            if (dirName == "") {
                std::cout << "Enter a valid directory name" << std::endl;
            }
            std::error_code eCode;
            
            if (!std::filesystem::remove_all(dirName, eCode)) {
                std::cout << "An error occurred: " << eCode.message() << std::endl;
            }
            std::cout << "Directory removed successfully" << std::endl;
        } else if (input == "exit") {
            running = false;
        } else {
            std::cout << "Invalid input" << std::endl;
        }
    }

    return 0;
}