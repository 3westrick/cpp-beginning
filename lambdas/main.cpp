/// A lambda function is an inline, anonymous function that
/// can be used wherever a function is required.<br>
/// ✔️ Shorter and cleaner syntax<br>
/// ✔️ Useful for passing functions to algorithms<br>
/// ✔️ Can capture variables from outer scope<br><br>
/// [ capture ] ( parameters ) -> return_type { function_body };
///

#include "iostream"
#include <vector>
#include <algorithm>

int main() {
    ///Basic Lambda Function
    auto greet = []()-> void {
        std::cout << "Hello, Lambda!" << std::endl;
    };
    greet();  // Call the lambda function

    /// Lambda with Parameters
    auto add = [] (int a, int b) -> int {
        return a + b;
    };
    std::cout << "Sum: " << add(5, 3) << std::endl;

    /// Capturing Variables from Scope
    int x =10, y = 20;
    /// Capture by Value ([=])
    auto sum = [=]() {  // Captures x and y by value
        return x + y;
    };
    std::cout << "Sum: " << sum() << std::endl;

    /// Capture by Reference ([&])
    auto modifyX = [&]() {  // Captures x by reference
        x += 5;
    };
    modifyX();
    std::cout << "Modified x: " << x << std::endl;

    ///Lambda in STL Algorithms
    std::vector<int> numbers = {5, 2, 8, 1, 3};

    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
       return a < b;
    });

    std::cout << "Sorted: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}