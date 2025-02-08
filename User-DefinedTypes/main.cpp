#include "iostream"
using namespace std;

/// Vector Struct

void print(auto x)
{
    cout << x << endl;
}

struct Vector {
    int sz; // number of elements
    double* elem; // pointer to elements
};

void vector_init(Vector& v, int s)
{
    v.elem = new double[s]; // allocate an array of s doubles
    v.sz = s;
}

double read_and_sum(int s)
{
    Vector v;

    vector_init(v, s);

    for (int i=0; i!=s; ++i)
        cin>>v.elem[i];

    double sum = 0;
    for (int i=0; i!=s; ++i)
        sum+=v.elem[i];

    return sum;

}

void f(Vector v, Vector& rv, Vector* pv)
{
    int i1 = v.sz; // access through name
    int i2 = rv.sz; // access through reference
    int i3 = pv->sz; // access through pointer

    cout << i1 << endl;
    cout << i2 << endl;
    cout << i3 << endl;
}

/// Vector Class

class VectorCls {
public:
    VectorCls(int s) :elem{new double[s]}, sz{s} { } // construct a Vector
    double& operator[](int i) { return elem[i]; } // element access: subscripting
    int size() { return sz; }
private:
    double* elem; // pointer to the elements
    int sz; // the number of elements
};

double vec_read_and_sum(int s) {
    VectorCls v(s); // make a vector of s elements
    for (int i=0; i!=v.size(); ++i)
        cin>>v[i]; // read into elements

    double sum = 0;
    for (int i=0; i!=v.size(); ++i)
        sum+=v[i]; // take the sum of the elements
    return sum;
}

class Node{
public:
    Node(int s): size{s}{}
    int get_size(){return size;}
private:
    int size;
};

enum Type { ptr, num }; // a Type can hold values ptr and num
struct Entry {
    string name; // string is a standard-library type Type t;
    Node* p; // use p if t==ptr
    int i; // use i if t==num
};

void unionF(Entry* pe)
{
    if (pe->i == num){
        print(33);
    }else{
        print(44);
    }
}
enum class Color { red, blue, green };
enum class Traffic_light { green, yellow, red };

int main()
{
//    cout << read_and_sum(4) << endl;

    Vector v;
    vector_init(v, 3);
    f(v, v, &v);

//    auto vev = VectorCls(6);
    VectorCls vec(6);

    print(vec.size());
    print(vec[0]);
//    print(vec_read_and_sum(3));
    unionF(new Entry());

    Color col = Color::red;
    Traffic_light light = Traffic_light::red;

//    Color x = red; // error : which red?
//    Color y = Traffic_light::red; // error: that red is not a Color
    Color z = Color::red; // OK
//    int i = Color::red; // error: Color::red is not an int
//    Color c = 2; // initialization error: 2 is not a Color

    return 0;
}