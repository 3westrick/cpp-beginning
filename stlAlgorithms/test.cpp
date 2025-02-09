#include "iostream"
#include "vector"
#include "map"
#include "set"
#include <algorithm>

template <typename T>
void print_vector(std::vector<T>& v)
{
    for (T num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}


int main()
{
    std::vector<int> nums = {1,2,5,4,3};
    print_vector(nums);

    /// Sort ascending
    std::sort(nums.begin(), nums.end());
    print_vector(nums);

    /// Sort descending
    std::sort(nums.begin(), nums.end(), std::greater<int>());
    print_vector(nums);

    /// find element
    auto it = std::find(nums.begin(), nums.end(), 4);

    if (it != nums.end())
    {
        std::cout << "not found." << std::endl;
    }
    else
    {
        std::cout << "found." << std::endl;
    }

    /// count element
    int occurrences = std::count(nums.begin(), nums.end(), 5);
    std::cout << "Found " << occurrences << "element" << std::endl;

    /// binary search
    std::sort(nums.begin(), nums.end());

    bool exists = std::binary_search(nums.begin(), nums.end(), 5);
    if (exists) {
        std::cout << 5 << " exists in the vector" << std::endl;
    } else {
        std::cout << 5 << " does not exist" << std::endl;
    }

    return 0;
}