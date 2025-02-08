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

void assigning_values()
{
    int x = 2;
    int y = 3;
    int* p = &x;
    int* q = &y; // now p!=q and *p!=*q
    cout << p << " " << *p << endl;
    cout << q << " " << *q << endl;

    p = q; // p becomes &y; now p==q, so (obviously)*p == *q

    cout << p << " " << *p <<  endl;
    cout << q << " " << *q << endl;

}

void ref_point(){
    int x = 2;
    int y = 3;
    int& r = x; // r refers to x
    int& r2 = y; // now r2 refers to y
    r = r2; // read through r2, write through r: x becomes 3

}

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

    assigning_values();
    ref_point();


    return 0;
}