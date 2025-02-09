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

template <typename T>
void find_element(std::vector<T>& v, T a)
{
    auto it = std::find(v.begin(), v.end(), a);

    if (it != v.end())
    {
        std::cout << "Found "<< a <<" at position: " << (it - v.begin()) << std::endl;
    }
    else
    {
        std::cout << a  <<" not found" << std::endl;
    }
}

template <typename T>
void count_occurrences(std::vector<T>& v, T a)
{
    int occurrences = std::count(v.begin(), v.end(), a);  // Count 'a's
    std::cout << "Number of times "<< a <<" appears: " << occurrences << std::endl;
}

template <typename T>
void binary_search(std::vector<T>& v, T a)
{
    /// The vector should be sorted Ascending
    bool exists = std::binary_search(v.begin(), v.end(), a);

    if (exists) {
        std::cout << a << " exists in the vector" << std::endl;
    } else {
        std::cout << a << " does not exist" << std::endl;
    }

}

int main()
{
    std::vector<int> nums = {1,2,3,8,5, 5,5,6,7, 30};

    /// Uses QuickSort or IntroSort, making it very fast (O(n log n)).
    std::sort(nums.begin(), nums.end());  /// Sort in ascending order

    std::cout << "Sorted (Asc): ";
    print_vector(nums);


    /// Sorting in Descending Order
    std::sort(nums.begin(), nums.end(), std::greater<int>());
    std::cout << "Sorted (Dec): ";
    print_vector(nums);

    /// Find in vectors
    find_element(nums, 30);
    find_element(nums, 5);
    find_element(nums, 40);

    /// Count number of occurrences of an element in a vector
    count_occurrences(nums, 6);
    count_occurrences(nums, 5);

    ///Checking if an Element Exists (binary_search())
    print_vector(nums);
    std::vector<int> v = {1,2,3,4,5};
    binary_search(v, 2);
    binary_search(v, 20);


    return 0;
}

