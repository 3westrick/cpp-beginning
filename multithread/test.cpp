#include "iostream"
#include "thread"
#include "mutex"

//void printHello(){
//    std::cout << "Hello from thread!" << std::endl;
//}

//void printMessage(std::string msg){
//    std::cout << msg << std::endl;
//}

std::mutex mtx;

void changeValueSafe(int* ptr, int val){
    std::lock_guard<std::mutex> lock(mtx);  // Lock automatically
    *ptr = val;
    std::cout << "Changed value to " << val << std::endl;
}

int main()
{
//    std::thread singleT(printHello);
//    singleT.join();
//
//    std::thread t1(printMessage, "Hello");
//    std::thread t2(printMessage, "Hi");
//    t1.join();
//    t2.join();
//
//    std::cout << "Main function done!" << std::endl;

    int x {10};
    int* ptr = &x;

    std::thread t1(changeValueSafe, ptr, 12);
    std::thread t2(changeValueSafe, ptr, 17);
    t1.join();
    t2.join();

    std::cout << x << std::endl;

    return 0;
}