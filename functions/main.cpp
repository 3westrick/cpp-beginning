#include <iostream>
#include "string"
using namespace std;

void print(double x)
{
    cout << x << endl;
}

void print(int x)
{
    cout << x << endl;
}

void print(string x)
{
    cout << x << endl;
}

int main()
{
    print(3);
    print(0.4);
    print("Hello");
    return 0;
}