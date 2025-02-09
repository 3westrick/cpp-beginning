#include "iostream"
#include "vector"
#include <ranges>
#include "map"

int main()
{
    std::vector<int> nums = {10, 20, 30, 40, 50};

    ///Basic Iterator Usage
    std::cout << "Vector elements: ";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";  // Dereferencing the iterator
    }
    std::cout << std::endl;

    std::cout << "Vector elements: ";
    for (int & num : nums) {
        std::cout << num << " ";  // Dereferencing the iterator
    }
    std::cout << std::endl;

    ///Reverse Iterators
    std::cout << "Reverse order: ";
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    /// Uses #include <ranges>
    std::cout << "Reverse order: ";
    for (int & num : std::ranges::reverse_view(nums)) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    /// Iter through map
    std::map<std::string, int> population = {
            {"USA", 331},
            {"China", 1441},
            {"India", 1380}
    };

    std::cout << "Country Populations:" << std::endl;
    for(auto it = population.begin(); it != population.end() ; ++it )
    {
        std::cout << it->first << ": " << it->second << " million" << std::endl;
    }

    std::cout << "Country Populations:" << std::endl;
    for(auto & it : population)
    {
        std::cout << it.first << ": " << it.second << " million" << std::endl;
    }

    return 0;
}