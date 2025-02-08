#include "iostream" // include ("import") the declarations for the I/O stream library
using namespace std; // make names from std visible without std::

float square(float x)
{
    return x * x;
}

void print_square(float x)
{
    cout << square(x) << endl;
}

int main()
{
    print_square(3);
    print_square(5);
    print_square(1.234);
    return 0;
}