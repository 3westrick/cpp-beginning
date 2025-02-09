#include "iostream"

using namespace std;

// Function template
template <typename T>
T add(T a, T b) {
    return a + b;
}

template <typename T>
class Box{
private:
    T value;
public:
    explicit Box(T v): value(v)
    {}
    void display() {
        std::cout << "Value: " << value << std::endl;
    }
};

template <typename T1, typename T2>
class Pair{
private:
    T1 first;
    T2 second;
public:
    Pair(T1 a, T2 b): first(a), second(b)
    {}
    void display() {
        std::cout << "First: " << first << ", Second: " << second << std::endl;
    }
};


template <typename T1, typename T2>
void swap(T1& a, T2& b)
{
    T1 temp = b;
    b = a;
    a = temp;
}

template <typename T1, typename T2>
class Calculator{
private:
    T1 first;
    T2 second;
public:
    Calculator(T1 a, T2 b):
    first(a), second(b)
    {}
    auto add(){return first + second;}
    auto subtract(){return first - second;}
    auto multiply(){return first * second;}
    auto divide(){return first / second;}
};

int main()
{
//    cout <<add(1,2)<< endl;
//    cout <<add(1.2,2.4)<< endl;

//    Box<int> intBox(10);  // Box for integers
//    Box<double> doubleBox(5.5);  // Box for doubles
//    intBox.display();
//    doubleBox.display();


//    Pair<int, double> p1(10, 5.5);
//    Pair<std::string, char> p2("Hello", 'A');
//    p1.display();
//    p2.display();

//    int a = 10;
//    int b = 20;
//    swap(a, b);
//    cout << a << " " << b << endl;
    Calculator calc(10,5);
    cout << calc.add() << endl;
    cout << calc.subtract() << endl;
    cout << calc.multiply() << endl;
    cout << calc.divide() << endl;
    return 0;
}