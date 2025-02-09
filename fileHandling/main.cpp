#include "iostream"
#include <fstream>  // Required for file handling
#include <string>


void write()
{
    std::ofstream file("example.txt");  // Open file

    if (file.is_open()) {
        file << "Hello, World!\n";  // Write to file
        file << "This is a C++ file handling example.\n";
        file.close();  // Close file
        std::cout << "Data written successfully!" << std::endl;
    } else {
        std::cout << "Error opening file!" << std::endl;
    }
}

void read()
{
    std::ifstream file("example.txt");  // Open file for reading

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {  // Read line by line
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Error opening file!" << std::endl;
    }
}

void append_to_file()
{
    std::ofstream file("example.txt", std::ios::app);  // Append mode
    if (file.is_open()) {
        file << "Appending new data.\n";
        file.close();
        std::cout << "Data appended successfully!" << std::endl;
    } else {
        std::cout << "Error opening file!" << std::endl;
    }
}

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int main()
{
    write();
    read();
    append_to_file();
    read();

    if (std::ifstream("example.txt").good() || fileExists("example.txt"))
    {
        std::cout << "File exists!" << std::endl;
    }
    else
    {
        std::cout << "File does not exist!" << std::endl;
    }

    return 0;
};

