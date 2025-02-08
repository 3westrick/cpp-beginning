#include <complex>
#include "iostream"
using namespace std;

constexpr double square(double x)
{
    return x * x;
}

int main()
{
    int x = 16;
    int y = 4;

    cout << "(x+y): " << x+y << endl; // plus
    cout << "(+x): " << +x << endl;   // unary plus
    cout << "(x-y): " << x-y << endl; // minus
    cout << "(-x): " << -x << endl;   // unary minus
    cout << "(x*y): " << x*y << endl; // multiply
    cout << "(x/y): " << x/y << endl; // divide
    cout << "(x%y): " << x%y << endl; // remainder (modulus) for integers

    cout << "(x==y): " << (x==y) << endl; // equal
    cout << "(x!=y): " << (x!=y) << endl; // not equal
    cout << "(x<y): " << (x<y) << endl; // less than
    cout << "(x>y): " << (x>y) << endl; // greater than
    cout << "(x<=y): " << (x<=y) << endl; // less than or equal
    cout << "(x>=y): " << (x>=y) << endl; // greater than or equal


    cout << "(x&y): " << (x&y) << endl; // bitwise and
    cout << "(x|y): " << (x|y) << endl; // bitwise or
    cout << "(x^y): " << (x^y) << endl; // bitwise exclusive or
    cout << "(~x): " << ~x << endl; // bitwise complement
    cout << "(x&&y): " << (x&&y) << endl; // logical and
    cout << "(x||y): " << (x||y) << endl; // logical or
    cout << "(!x): " << !x << endl; // logical not (negation)

    cout << "x: " << x << endl;
    x+=y; // x = x+y
    cout << "x: " << x << endl;
    ++x; // increment: x = x+1
    cout << "x: " << x << endl;
    x-=y; // x = x-y
    cout << "x: " << x << endl;
    --x; // decrement: x = x-1
    cout << "x: " << x << endl;
    x*=y; // scaling: x = x*y
    cout << "x: " << x << endl;
    x/=y; // scaling: x = x/y
    cout << "x: " << x << endl;
    x%=y; // x = x%y
    cout << "x: " << x << endl;

    double d1 = 2.3; // initialize d1 to 2.3
    double d2 {2.3}; // initialize d2 to 2.3
    double d3 = {2.3}; // initialize d3 to 2.3 (the = is optional with { ... })
    complex<double> z = 1;
    complex<double> z2 {d1,d2};
    complex<double> z3 = {d1,d2}; // the = is optional with { ... }

    vector<int> v {1,2,3,4,5,6}; // a vector of ints

    int i1 = 7.8; // i1 becomes 7
//    int i2 {7.8}; // error : floating-point to integer conversion

    auto b = true; // a bool
    auto ch = 'x'; // a char
    auto i = 123; // an int
    auto d = 1.2; // a double
    auto w = square(y); // z has the type of whatever sqr t(y) retur ns
    auto bb {true}; // bb is a bool

    constexpr int dmv = 17; // dmv is a named constant
    int var = 17; // var is not a constant
    const double sqv = square(var); // sqv is a named constant, possibly computed at run time

    return 0;
}