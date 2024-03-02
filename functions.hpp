#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream> // for basic io functions
#include <fstream> // for file creation and file reading
#include <filesystem> // for directory creation

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

void touch() {
    std::string fileName;
    std::cout << "Enter the name of the file: ";
    std::getline(std::cin, fileName);
    if (fileName == "") {
        std::cout << "Enter a valid file name" << std::endl;
    }
    std::ofstream file(fileName);
    std::cout << "File created" << std::endl;
    file.close();
}

void mkdir() {
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
    }

    if (std::filesystem::create_directory(newDirectoryPath)) {
        std::cout << "Directory created successfully!" << std::endl;
    } else {
        std::cerr << "Failed to create directory!" << std::endl;
    }
}

void echo() {
    std::cout << "Enter text: ";
    std::string text;
    std::getline(std::cin, text);
    std::cout << text << std::endl;
}

void cat() {
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
}

void randomimg() {
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
}

void clear() {
    int resp = std::system("clear");
            
    if (resp != 0) {
        std::cout << "Failed to clear screen" << std::endl;
    }
}

void rf() {
    std::string fileName;
    std::cout << "Enter file name to delete: ";
    std::getline(std::cin, fileName);
    if (fileName == "") {
        std::cout << "Enter a valid file name" << std::endl;
    }
    remove(fileName.c_str());
    std::cout << "Removed file successfully" << std::endl;
}

void rmdir() {
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
}
#endif