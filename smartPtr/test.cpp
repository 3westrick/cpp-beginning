#include <iostream>
#include <memory>

void uniquePtr()
{
    std::unique_ptr<int> ptr = std::make_unique<int>(100);
    std::cout << "Value of Unique Ptr: " << *ptr << std::endl;
}

void sharedPtr()
{
    std::shared_ptr<int> ptr = std::make_shared<int>(88);
    std::cout << "Value of Shared Ptr: " << *ptr << std::endl;
}

std::weak_ptr<int> weakPtr()
{
    std::shared_ptr<int> shared = std::make_shared<int>(68);
    std::weak_ptr<int> weak = shared;
    std::cout << "Value of Shared Ptr: " << *shared << std::endl;
    if (auto locked = weak.lock()){
        std::cout << "Value of Weak (locked) Ptr: " << *locked << std::endl;
    }else{
        std::cout << "Object has been deleted." << std::endl;
    }
    return weak;
}

int main() {
    uniquePtr();
    sharedPtr();

    auto weak= weakPtr();
    if (auto locked = weak.lock()){
        std::cout << "Value of Weak (locked) Ptr: " << *locked << std::endl;
    }else{
        std::cout << "Object has been deleted." << std::endl;
    }


    return 0;
}