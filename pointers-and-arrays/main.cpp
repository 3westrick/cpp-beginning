#include "iostream"

using namespace std;

void print(auto x)
{
    cout << x << endl;
}

void print_array()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9};

    // for loop
    for(int i = 0; i < size(v); i++){
        cout << v[i] << ", ";
    }
    cout << endl;

    // for each
    for(int x : v){
        cout << x << ", ";
    }
    cout << endl;
}

void sort(vector<double>& v); // sort v (v is a vector of doubles)

int main()
{
    int v[6]; // array of 6 characters
    v[0] = 0;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    v[5] = 6;

    // char* p; // pointer to character

    int* p = &v[3]; // p points to v’s fourth element | &v[3] is the pointer of v’s fourth element
    int x = *p; // *p is the object that p points to

    print(p);
    print(v[3]);
    print(x);

    int* q = p + 1; // q points to v's fifth element
    print(*q); // *q is the object that q points to

    print_array();

    return 0;
}