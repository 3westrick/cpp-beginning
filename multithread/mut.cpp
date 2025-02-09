#include <iostream>
#include <thread>
#include <mutex>

/// Synchronization: Using mutex

/// Prevents simultaneous access to shared data
std::mutex mtx;  // Mutex for synchronization

void printSafe(int id) {
    /// Automatically locks and unlocks
    std::lock_guard<std::mutex> lock(mtx);  // Lock automatically

    std::cout << "Thread " << id << " is running safely." << std::endl;
}

int main() {

    std::thread t1(printSafe, 1);
    std::thread t2(printSafe, 2);

    t1.join();
    t2.join();

    return 0;
}
