#include "iostream"
#include "filesystem"
#include "exception"

class FileNotFound : public std::exception{
public:
    const char* what() const noexcept override {
        return "File Not Found";
    }
};

bool check_exists(std::string file, bool throw_exception = false){
    if (std::filesystem::exists(file)) return true;
    else if (throw_exception) throw FileNotFound();
    else return false;
}

void ls(std::string path){
    std::cout << "Files in directory:" << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(path)){
        std::cout << entry.path() << std::endl;
    }
}

void create_folder(std::string folder){
    if(!std::filesystem::exists(folder)){
        std::filesystem::create_directory(folder);
        std::cout << "Folder created: " << folder << std::endl;
    }
}

void delete_folder(std::string folder){
    if(std::filesystem::exists(folder)){
        std::filesystem::remove(folder);
        std::cout << "Folder deleted: " << folder << std::endl;
    }
}

int main()
{
    /// Checking if a File Exists
    //std::string file = "../test.cpp";
    //std::cout << check_exists(file) << std::endl;
    //std::cout << check_exists("file.txx", false) << std::endl;
    //std::cout << check_exists("file.txx", true) << std::endl;

    /// List All Files in a Directory
    ls(".");

    /// Creating and Removing Directories
    create_folder("new_folder");
    delete_folder("new_folder");

    return 0;
}