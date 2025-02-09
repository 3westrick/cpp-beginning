#include <iostream>
#include <exception>

class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Custom Exception: Something went wrong!";
    }
};

void testFunction() {
    throw MyException();  // Throw custom exception
}

int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Error: Division by zero!");
    }
    if (a < 0 || b < 0) {
        throw std::invalid_argument("Error: Negative numbers not allowed!");
    }
    return a / b;
}

int main() {
    try {
        std::cout << divide(10, 2) << std::endl;
        std::cout << divide(-5, 2) << std::endl;  // Throws exception
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid Argument: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
    }
    catch (...) {  // Catches any other exception
        std::cerr << "Unknown Exception Caught!" << std::endl;
    }

    try {
        testFunction();
    } catch (const MyException& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Program continues..." << std::endl;
    return 0;
}
