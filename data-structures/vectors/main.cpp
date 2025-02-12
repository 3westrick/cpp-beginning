#include "iostream"
using namespace std;

class Vector{
private:
    int* arr;
    int capacity_ = 4;
    int size_ = 0;

    void resize(){
        capacity_ = capacity_ * 2;
        int* newArr = new int[capacity_];
        for (int i = 0; i < size_; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    Vector(int cap): capacity_(cap), size_(0){
        arr = new int[capacity_];
    }

    int capacity() const {
        return capacity_;
    }
    int size() const{
        return size_;
    }
    void append(int val){
        if (size_ == capacity_) resize();
        arr[size_++] = val;
    }

    void prepend(int val){
        if (size_ == capacity_) resize();
        for (int i = size_; i > 0; i--)
            arr[i] = arr[i - 1];
        size_++;
        arr[0] = val;
    }

    int pop(){
        if (size_ > 0) {
            int val = arr[size_ - 1];
            size_ --;
            return val;
        } else return 0;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << v.size() << " Out of " << v.capacity() << endl;

        for(int i = 0 ; i < v.size_; i ++){
            os << v.arr[i] << " ";
        }

        return os;
    }

    ~Vector() { delete[] arr; }
};

int main(){
    Vector vec(4);
    vec.append(4);
    vec.append(8);
    vec.append(8);
    cout << vec << endl;
    vec.pop();
    cout << vec << endl;
    vec.prepend(3);
    vec.prepend(2);
    cout << vec << endl;
    vec.prepend(1);
    cout << vec << endl;
    return 0;
}