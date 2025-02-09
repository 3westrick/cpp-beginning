#include "iostream"

///Vectors (Dynamic Arrays)
#include <vector>

/// Sets (Unique Elements)
#include <set>

/// Maps (Key-Value Pairs)
#include <map>

int main()
{
    std::cout << "----------Vectors----------" << std::endl;
    /// <h3>Vectors</h3>
    std::vector<int> numbers_vec = {1, 2, 3, 4, 5};

    /// Add elements
    numbers_vec.push_back(6);
    numbers_vec.push_back(7);

    /// access elements
    std::cout << "First element: " << numbers_vec[0] << std::endl;
    std::cout << "Last element: " << numbers_vec.back() << std::endl;

    /// Iterate over vector
    std::cout << "Vector elements: ";
    for (int num : numbers_vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    /// Remove last element
    numbers_vec.pop_back();

    /// Get size
    std::cout << "Size: " << numbers_vec.size() << std::endl;


    std::cout << "----------Sets----------" << std::endl;
    /// <hr><h3>Sets</h3>

    std::set<int> numbers_set =  {5, 1, 4, 2, 3, 3, 2}; /// Duplicates are ignored

    /// Insert a new element
    numbers_set.insert(6);

    /// Iterate over set (sorted order)
    std::cout << "Set elements: ";
    for (int num : numbers_set) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    /// Check if an element exists
    if (numbers_set.find(4) != numbers_set.end()) {
        std::cout << "4 is in the set" << std::endl;
    }


    std::cout << "----------Maps----------" << std::endl;
    /// Maps
    std::map<std::string, int> ages;

    /// Add key-value pairs
    ages["Alice"] = 25;
    ages["Bob"] = 30;
    ages["Charlie"] = 22;

    /// Access value by key
    std::cout << "Alice's age: " << ages["Alice"] << std::endl;

    /// Iterate over map
    for (auto pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    /// Check if a key exists
    if (ages.find("David") == ages.end()) {
        std::cout << "David not found" << std::endl;
    }else
    {
        std::cout << "David's age: " << ages["David"] << std::endl;
    }

    return 0;
}