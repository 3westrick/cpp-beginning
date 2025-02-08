#include "iostream"
using namespace std;

int count_x(const char* p, char x)
// count the number of occurrences of x in p[]
// p is assumed to point to a zero-terminated array of char (or to nothing)
// char* is a c-style string that the pointer
// points to a zero-terminated array of char.
{

    if (p==nullptr) return 0;

    int count = 0;

    for (; *p!=0; ++p)
    {
        if (*p==x) ++count;
    }
    return count;
}

int count_x_refactored(const char* p, char x)
{
    if (p==nullptr)
    {
        cout << "Null Pointer" << endl;
        return 0;
    }
    int count = 0;
    while (*p) {
        if (*p==x)
            ++count;
        ++p;
    }
    return count;
}

int main()
{
    double* pd = nullptr;
    //int x = nullptr; // error : nullptr is a pointer not an integer

    char arr[3] = {'a','b','a'};
    char* p = &arr[0];
    cout << count_x("aaabbaa", 'a') << endl;
    cout << count_x_refactored("aaabbaa", 'a') << endl;
    cout << count_x_refactored(NULL, 'a') << endl;

    return 0;
}