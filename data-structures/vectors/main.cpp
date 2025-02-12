#include "iostream"
#include "vector"

void print(std::vector<int> arr){
    for (auto& entry : arr){
        std::cout << entry << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> arr = {3,4,7,8};
    print(arr);
    arr.push_back(6);
    arr.insert(arr.begin(), 4);
    print(arr);
    arr.pop_back();
    arr.erase(arr.begin());
    print(arr);

    std::vector<int> c2(2, 400);
    arr.insert(std::next(arr.begin(), 2), c2.begin(), c2.end());
    print(arr);

    return 0;
}