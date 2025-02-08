#include <iostream>
using namespace std;

void print(double x)
{
    cout << "Double: " << sizeof(double )<< endl;
    cout << x << endl;
}

void print(int x)
{
    cout << "Int: " << sizeof(int )<< endl;
    cout << x << endl;
}

void print(char x)
{
    cout << "Char: " << sizeof(char)<< endl;
    cout << x << endl;
}

int main()
{
    print(3);
    print(0.4);
    print('c');
    return 0;
}