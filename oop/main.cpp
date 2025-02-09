#include <iostream>
#include <utility>

using namespace std;

class Car{
public:
    int year;
    string brand;
    Car(const string& car_brand, int car_year)
    {
        brand = car_brand;
        year = car_year;
    }

    void show() const
    {
        cout << "Brand: " << brand << " | Year: " << year << endl;
    }
};

class BankAccount{
private:
    int balance;
public:
    BankAccount(int initialBalance):
    balance {initialBalance}
    {}

    void deposit(int amount)
    {
        balance += amount;
        getBalance();
    }

    void getBalance() const
    {
        cout << balance << endl;
    }
};

class Animal{
public:
    virtual void eat()
    {
        cout << "This animal eats food." << endl;
    }
};

class Dog : public Animal{
public:
    void eat() override
    {
        cout << "The dog eats." << endl;
    }
    void bark()
    {
        cout << "The dog barks." << endl;
    }
};

class Person{
public:
    int age;
    string name;
    Person(string name, int age):
    name {std::move(name)}, age {age}
    {}

    void display()
    {
        cout << "Name: "<< name << " | Age: " << age << endl;
    }

    virtual void introduce()
    {
        cout << "This person introduces himself." << endl;
    }
};

class Student : public Person{
private:
    int id;
public:
    Student(string name, int age, int id):
    Person(std::move(name), age), id {id}
    {}

    void introduce() override
    {
        cout << "Hi, my name is " << name;
    }
};


class Point {
public:
    int x, y;

    Point(int x, int y):
    x(x), y(y)
    {}

    Point operator+(const Point& other)
    {
        return {x + other.x, y + other.y};
//        return Point{x + other.x, y + other.y};
//        return Point(x + other.x, y + other.y);
    }

    bool operator==(const Point& other)
    {
        return (x == other.x && y == other.y);
    }

    // Overloading <<
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    void display() {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};

class Fraction{
private:
    int numerator;
    int denominator;

public:
    Fraction(int numerator, int denominator):
    numerator(numerator), denominator(denominator)
    {
        if (denominator == 0) {
            throw ("aaaa");
        }
    }

    Fraction operator+(const Fraction& other)
    {
        if (other.denominator == denominator)
        {
            return Fraction(numerator + other.numerator, denominator);
        }else
        {
            return Fraction((denominator * other.numerator) + (numerator * other.denominator),
                            (denominator * other.denominator));
        }
    }

    friend ostream& operator<<(ostream& os, const Fraction& f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }
};

int main()
{
//    Car car_1("BMW", 1996);
//    Car car_2("Audi", 2002);
//    car_1.show();
//    car_2.show();

//    BankAccount b(10000);
//    b.getBalance();
//    b.deposit(100);

//    Dog dog;
//    dog.eat();
//    dog.bark();

//    Animal* animal = new Dog();
//    animal->eat();
//    animal.eat(); // Error
//    animal.bark(); // Error
//    delete animal;

//    Person p("arad", 22);
//    p.display();

//    Person* person = new Student("Arad", 23, 9901226);
//    person->introduce();

//    delete person;

//    Point p1(2, 3), p2(4, 5);
//    Point p3 = p1 + p2;  // Calls overloaded operator+
//    p3.display();  // Output: (6, 8)
//    cout << p3;
//    Fraction f1(2,3);
//    Fraction f2(3,3);
//    Fraction f3 = f1 + f1;
//    cout << f1 << " " << f2 << " " << f3;
    return 0;
}