#include "iostream"
#include <fstream>  // Required for file handling
#include <string>
#include <utility>

void write_file()
{
    std::ofstream file("../data.txt");

    if(file.is_open()){
        file << "Hello my data file.\n";
        file << "Goodbye, for now.\n";
        file.close();
    }else{
        std::cout << "Error opening file!" << std::endl;
    }

}

class File{
private:
    std::string fileName;
public:
    File(std::string fileName):
    fileName(std::move(fileName))
    {
        std::cout << "Creating File" << std::endl;
    }

    void write(std::string text){
        std::ofstream file(fileName);
        if (!isFileOpen(file)) return;

        file << text;
        file.close();
    }

    void read(){
        std::ifstream file(fileName);
        if (!isFileOpen(file)) return;

        std::string line;
        while (std::getline(file, line)){
            std::cout << line << std::endl;
        }
        file.close();
    }

    template<typename T>
    bool isFileOpen(T& file){
        if (file.is_open()) return true;

        std::cout << "Could not open file!!!" << std::endl;
        return false;
    }

};

void read_file()
{
    std::ifstream file("../data.txt");
    if(file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::cout << line << std::endl;
        }
        file.close();
    }else{
        std::cout << "Error opening file!" << std::endl;
    }
}

void append_file()
{
    std::ofstream file("../data.txt", std::ios::app);
    if(file.is_open()){
        file << "Appending new data.\n";
        file.close();
    }else{
        std::cout << "Error opening file!" << std::endl;
    }

}

int main()
{
//    write_file();
//    read_file();
//    append_file();
//    read_file();

    File file("../hello.txt");
    file.write("Hello\n");
    file.write("How are you?\n");
    file.read();
    return 0;
}