#include "iostream"
using namespace std;

bool accept()
{
    cout << "Do you want to proceed (y or n)?\n"; // wr ite question
    char answer = 0; // initialize to a value that will not appear on input

    //the >> operator ("get from") is used for input; cin is the standard input stream
    cin >> answer; // read answer
    if (answer == 'y')
        return true;
    return false;
}

bool accept2()
{
    cout << "Do you want to proceed (y or n)?\n"; // write question
    char answer = 0; // initialize to a value that will not appear on input
    cin >> answer; // read answer
    switch (answer) {
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            cout << "I'll take that for a no.\n";
            return false;
    }
}

int main()
{
    cout << accept() << endl;
    cout << accept2() << endl;
    return 0;
}