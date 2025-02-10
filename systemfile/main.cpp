#include <iostream>
#include <filesystem>

void check_file(std::string filename){
    if (std::filesystem::exists(filename)) {
        std::cout << '"'<< filename<< '"' <<" exists!" << std::endl;
    } else {
        std::cerr << '"'<< filename<< '"' << " does not exist." << std::endl;
    }
}

void get_size(std::string filename){
    if (std::filesystem::exists(filename)) {
        std::cout << '"'<< filename<< '"' <<" size: " << std::filesystem::file_size(filename) << " bytes" << std::endl;
    } else {
        std::cerr << '"'<< filename<< '"' << " does not exist." << std::endl;
    }
}

int main() {

    /// Checking if a File Exists
    check_file("../data.txt");
    check_file("../example.txt");

    /// Getting File Size
    get_size("../data.txt");
    get_size("../example.txt");

    /// Listing Files in a Directory
    std::string path = ".";  // Current directory
    std::cout << "Files in directory:" << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::cout << entry.path() << std::endl;
    }

    /// Creating and Removing Directories
    std::string folder = "../new_folder";
    if (!std::filesystem::exists(folder)) {
        std::filesystem::create_directory(folder);
        std::cout << "Folder created: " << folder << std::endl;
    }else{
        std::filesystem::remove(folder);
        std::cout << "Folder deleted: " << folder << std::endl;
    }



    return 0;
}
