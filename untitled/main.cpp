#include "iostream"
#include <memory>
using namespace std;

void number_value()
{
    int number;
    cout << "Pleas enter a number: ";
    cin >> number;

    if (number > 0)
    {
        cout << "Pos" << endl;
    }else if(number < 0)
    {
        cout << "Neg" << endl;
    }else
    {
        cout << "Zero" << endl;
    }
}

void for_loop()
{
    for(int i = 0 ; i < 5; i++)
    {
        cout << "Iter #" << i << endl;
    }
}

int add(int a, int b)
{
    return  a + b;
}

double add(double a, double b)
{
    return a + b;
}

void greet(const string& name = "User")
{
    cout << "Hello, " << name << endl;
}

int globalVar = 100;  // Global variable

void show() {
    int localVar = 50;  // Local variable
    std::cout << "Local Variable: " << localVar << std::endl;
    std::cout << "Global Variable: " << globalVar << std::endl;
}

int multiply(int a, int b)
{
    return a * b;
}

double multiply(double a, double b)
{
    return a * b;
}

void pointer()
{
    int x = 10;
    int* ptr = &x;  // Pointer storing the address of x

    std::cout << "Value of x: " << x << std::endl;
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Pointer ptr stores: " << ptr << std::endl;
    std::cout << "Value at pointer ptr: " << *ptr << std::endl;
}

void changeValue(int* ptr, int value)
{
    *ptr = value;
}

void cahnge_value()
{
    int x = 10;
    int* ptr = &x;
    std::cout << "Value of x: " << x << std::endl;
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Pointer ptr stores: " << ptr << std::endl;
    changeValue(ptr, 20);
    std::cout << "Value of x: " << x << std::endl;
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Pointer ptr stores: " << ptr << std::endl;
}

void reference()
{
    int x = 10;
    int& ref = x;
    std::cout << "Value of x: " << x << std::endl;
    std::cout << "Value of ref: " << ref << std::endl;
    ref = 20;
    std::cout << "Value of x: " << x << std::endl;
    std::cout << "Value of ref: " << ref << std::endl;

}

void realUpdate(int& x)
{
    x = 10;
}

void fakeUpdate(int x)
{
    x = 10;
}

void updateValue()
{
    int x = 20;
    std::cout << "Value of x: " << x << std::endl;
    fakeUpdate(x);
    std::cout << "Value of x (fakeUpdate): " << x << std::endl;
    realUpdate(x);
    std::cout << "Value of x (realUpdate): " << x << std::endl;
}

void swap(int& a, int& b)
{
    int temp = b;
    b = a;
    a = temp;
}

void swap_numbers()
{
    int a = 2;
    int b = 5;
    cout << a << " " << b << endl;
    swap(a,b);
    cout << a << " " << b << endl;
}

void doubleValue(int* p)
{
    *p =  *p * 2 ;
}

void double_value()
{
    int x = 5;
    cout << x << endl;
    doubleValue(&x);
    cout << x << endl;
}

void int_memory_alloc()
{
    int* ptr = new int;

    *ptr = 42;
    cout << *ptr << endl;

    delete ptr;
}

void array_memory_alloc()
{
    int size = 5;
    int* arr = new int[size];

    for(int i = 0 ; i < size ; i ++)
    {
        arr[i] = i * 10;
    }

    for(int i = 0 ; i < size ; i ++)
    {
        cout << arr[i] << " ";
    }

    delete[] arr;
}

void smart_alloc()
{
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    cout << "Value: " << *ptr << endl; // No need for delete
}

void user_array_memory_alloc()
{

    std::unique_ptr<int> size;
    cout << "Enter array size: ";
    int number;
    cin >> number;
    size = std::make_unique<int>(number);

    std::unique_ptr<int> arr[*size];
    for(int i = 0 ; i < *size ; i ++)
    {
        arr[i] = std::make_unique<int>(i * 10);
    }

    for(int i = 0 ; i < *size ; i ++)
    {
        cout << *arr[i] << " ";
    }

}

void alll()
{
    int* ptr = new int;
    *ptr = 42;


    delete ptr;
}

int main()
{
//    number_value();
//    for_loop();
//    std::cout << "Integer Sum: " << add(5, 3) << std::endl;
//    std::cout << "Double Sum: " << add(5.5, 2.3) << std::endl;
//    greet();
//    greet("Arad");
//show();
//    cout << multiply(3,4) << endl;
//    cout << multiply(3.1,4.0) << endl;
//    pointer();
//    cahnge_value();
//    reference();
//    updateValue();
//    swap_numbers();
//    double_value();
//    int_memory_alloc();
//    array_memory_alloc();
//    smart_alloc();
    user_array_memory_alloc();
    return 0;
}