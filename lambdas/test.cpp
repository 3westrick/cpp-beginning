#include "iostream"
#include "vector"
#include "algorithm"

int main()
{
    auto print = []() -> void {
        std::cout << "Lambda in C++!" << std::endl;
    };
    print();

    auto add = [](int a, int b) -> int {
        return a + b;
    };
    std::cout << add(1,4) << std::endl;

    int x = 10;
    auto captureByValue = [=]() -> void {
        std::cout << x << std::endl;
    };

    auto captureByReference = [&]() -> void {
        std::cout << x << std::endl;
    };
    captureByValue();
    captureByReference();

    std::vector<int> numbers = {1,3,4,7,2,9};
    std::sort(numbers.begin(), numbers.end(), [](int a, int b){
        return a > b;
    });

    std::cout << "Sorted: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}