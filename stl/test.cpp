#include "iostream"
#include "vector"
#include "map"
#include "set"

int main()
{
    ///Vector
    std::vector<int> num_vec = {1,2,3,4,5};

    for (int elem : num_vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    ///Set
    std::set<std::string> names = {"arad", "amir", "reza", "hamid", "amir"};

    std::cout << "Set elements: ";
    for (std::string name : names) {
        std::cout << name << " ";
    }
    std::cout << std::endl;

    std::string newName = "amir";

    if (names.find(newName) == names.end()) {  // Not found → safe to insert
        names.insert(newName);
        std::cout << newName << " added." << std::endl;
    } else {
        std::cout << newName << " already exists!" << std::endl;
    }

    /// Maps
    std::map<std::string, int> countries;
    countries["USA"] = 10000000;
    countries["China"] = 100000000;
    countries["Canada"] = 2000000;

    for (auto& country : countries) {
        std::cout << country.first << ": " << country.second << std::endl;
    }

    return 0;
}