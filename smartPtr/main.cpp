#include <iostream>
/// Required for smart pointers
#include <memory>

int main() {
    /// <h3>Smart pointers</h3> are modern alternatives to raw pointers that automatically
    /// deallocate memory when no longer needed.
    /// <ul>
    ///     <li>Prevents memory leaks</li>
    ///     <li>Handles dynamic memory safely</li>
    ///     <li>No need for manual delete</li>
    /// </ul>
    std::unique_ptr<int> ptr = std::make_unique<int>(42);  // Allocate memory
    std::cout << "Value: " << *ptr << std::endl;  // Dereference pointer
    /// Memory is automatically deallocated when ptr goes out of scope
    //

    /// <h3>shared_ptr (Reference Counting)</h3>
    /// A shared_ptr allows multiple pointers to share ownership of an object.
    /// The object is deleted when the last shared_ptr goes out of scope.
    std::shared_ptr<int> ptr1 = std::make_shared<int>(10);  // Shared ownership
    std::shared_ptr<int> ptr2 = ptr1;  // ptr2 shares ownership
    std::cout << "Value *ptr1: " << *ptr1 << std::endl;
    std::cout << "Value *ptr2: " << *ptr2 << std::endl;
    std::cout << "Reference Count: " << ptr1.use_count() << std::endl;  // Count references

    /// <h3>weak_ptr (Avoid Circular References)</h3>
    /// A weak_ptr is a non-owning reference to a shared_ptr object.<br>
    /// Prevents circular references that could cause memory leaks.<br>
    /// Use lock() to convert it into a shared_ptr.
    std::shared_ptr<int> shared = std::make_shared<int>(100);
    std::weak_ptr<int> weak = shared;  // weak_ptr does not increase ref count

    if (auto locked = weak.lock()) {  // Convert weak_ptr to shared_ptr safely
        std::cout << "Value: " << *locked << std::endl;
    } else {
        std::cout << "Object has been deleted." << std::endl;
    }

    return 0;
}
