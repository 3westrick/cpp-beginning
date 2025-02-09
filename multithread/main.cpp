#include "iostream"
#include "thread"

void hello() {
    std::cout << "Hello from thread!" << std::endl;
}

void independentTask() {
    std::cout << "This is running in a separate thread!" << std::endl;
}

void printMessage(std::string msg, int repeat) {
    for (int i = 0; i < repeat; i++) {
        std::cout << msg << std::endl;
    }
}

void task(int id) {
    std::cout << "Task " << id << " running..." << std::endl;
}

int main()
{
    //std::thread t(hello);  // Start a new thread
    //t.join();  // Wait for thread to finish

    //std::thread it(independentTask);

    /// If the task is not done by the end of the program, it does not show its massage
    //it.detach();  // Run thread independently

//    std::thread t(printMessage, "Hello from thread!", 3);
//    t.detach();
//    int num;
//    std::cout << "Enter a number: ";
//    std::cin >> num;

    std::thread t1(task, 1);
    std::thread t2(task, 2);

    /// join() ensures they complete before exiting
    t1.join();
    t2.join();


    std::cout << "Main function done!" << std::endl;
    return 0;
}