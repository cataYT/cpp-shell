#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream> // for basic io functions
#include <fstream> // for file creation and file reading
#include <filesystem> // for directory creation

#include "randomimg.hpp"

#ifdef _WIN32
    const std::string open_command = "start";
#elif __APPLE__
    const std::string open_command = "open";
#else // Linux
    const std::string open_command = "xdg-open"; // run sudo apt-get install xdg-utils
#endif

void help() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "help: brings up this menu" << std::endl;
    std::cout << "exit: exits the shell" << std::endl;
    std::cout << "touch: creates file" << std::endl;
    std::cout << "mkdir: creates directory" << std::endl;
    std::cout << "echo: prints text" << std::endl;
    std::cout << "cat: read from file and display on the shell" << std::endl;
    std::cout << "randomimg: generates random image" << std::endl;
    std::cout << "clear: clears the screen" << std::endl;
    std::cout << "rf: removes file" << std::endl;
    std::cout << "rmdir: removes directory" << std::endl;
}

void touch(std::string fileName) {
    if (fileName.empty()) {
        std::cout << "Enter a valid file name" << std::endl;
        return;
    }
        
    std::ofstream file(fileName);
        
    if (!file.is_open() || file.fail()) {
        std::cout << "Failed to create or open file" << std::endl;
        return; 
    }
        
    std::cout << "File created: " << fileName << std::endl; 
}

void mkdir(std::string dirName) {
    if (dirName == "") {
        std::cout << "Enter a valid directory name" << std::endl;
        return;
    }

    std::filesystem::path currentPath = std::filesystem::current_path();

    std::filesystem::path newDirectoryPath = currentPath / dirName;

    if (std::filesystem::exists(newDirectoryPath)) {
        std::cerr << "Directory already exists!" << std::endl;
        return;
    }

    if (std::filesystem::create_directory(newDirectoryPath)) {
        std::cout << "Directory created successfully!" << std::endl;
        return;
    } else {
        std::cerr << "Failed to create directory!" << std::endl;
        return;
    }
}

void echo(std::string text) {
    std::cout << text << std::endl;
}

void cat(std::string fileName) {
    if (fileName == "") {
        std::cout << "Enter a valid file name" << std::endl;
        return;
    }

    std::ifstream file(fileName);
    if (!file || !file.is_open() || file.fail()) {
        std::cout << "Failed to open file" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
            
    file.close();
}

void randomimg() {
    std::string result = getRandImg();
    if (result == "") {
        std::cout << "Unsplashed api get request failed" << std::endl;
        return;
    } else {
        std::string command = open_command + " " + std::string(result);
        int resp = std::system(command.c_str());
                
        if (resp == 0) {
            std::cout << "Image opened successfully" << std::endl;
        } else {
            std::cout << "Failed to open image" << std::endl;
            return;
        }
    }
}

void clear() {
    int resp = std::system("clear");
            
    if (resp != 0) {
        std::cout << "Failed to clear screen" << std::endl;
        return;
    }
}

void rf(std::string fileName) {
    
    if (fileName == "") {
        std::cout << "Enter a valid file name" << std::endl;
        return;
    }
    if (remove(fileName.c_str()) != 0) {
        std::cout << "Failed to remove file" << std::endl;
        return;
    }
    std::cout << "Removed file successfully" << std::endl;
}

void rmdir(std::string dirName) {
    if (dirName == "") {
        std::cout << "Enter a valid directory name" << std::endl;
        return;
    }
    std::error_code eCode;
            
    if (!std::filesystem::remove_all(dirName, eCode)) {
        std::cout << "An error occurred: " << eCode.message() << std::endl;
        return;
    }
    std::cout << "Directory removed successfully" << std::endl;
}

void calc(std::string operation, long double num1, long double num2) {
    for (char &c : operation) {
        c = std::tolower(c);
    }

    if (operation == "add") {
        std::cout << num1 + num2 << std::endl;
    } else if (operation == "sub") {
        std::cout << num1 - num2 << std::endl;
    } else if (operation == "mul") {
        std::cout << num1 * num2 << std::endl;
    } else if (operation == "div") {
        std::cout << num1 / num2 << std::endl;
    } else {
        std::cout << "Invalid operation" << std::endl;
    }
}

std::string xorEncrypt(std::string str, char *key) {
    std::string *ptr = new std::string(str);
    for (char &c : *ptr) {
        c = c ^ *key;
    }
    return *ptr;
}


#endif