#include "iostream"
#include "exception"

class NegativeInputException: std::exception {
public:
    const char* what() const noexcept override {
        return "Custom Error: Invalid Input";
    }
};

int divide__(int a, int b)
{
    if (b == 0) throw std::runtime_error("Division by zero!");

//    if (a < 0 || b < 0) throw std::invalid_argument("Negative numbers not allowed!");
    if (a < 0 || b < 0) throw NegativeInputException();

    return a / b;
}

int divide(int a, int b){
    try{
        return divide__(a,b);
    }catch (std::runtime_error& e) {
        std::cerr << "Run Time Error - " << e.what() << std::endl;
    }catch (const NegativeInputException& e){
        std::cerr << e.what() << std::endl;
    }catch (...){
        std::cerr << "Unknown Exception Caught!" << std::endl;
    }
}

int main()
{

    std::cout << divide(6,2) << std::endl;
    std::cout << divide(6,0) << std::endl;
    std::cout << divide(6,-1) << std::endl;

    return 0;
}