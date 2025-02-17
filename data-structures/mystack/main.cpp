#include "iostream"

class StackArray{
private:
    int* arr;
    int capacity;
    int topIndex;
public:
    StackArray(int cap = 10):capacity(cap), topIndex(-1){
        arr = new int[capacity];
    }

    void push(int val){
        if (topIndex == capacity - 1) {
            std::cerr << "Stack is full.\n";
            return;
        }
        arr[++topIndex] = val;
    }
    void pop(){
        if (topIndex == -1){
            std::cerr << "Stack is empty.\n";
            return;
        }
        topIndex--;
    }
    int top(){
        if (topIndex == -1)throw std::out_of_range("Stack is empty");
        return arr[topIndex];
    }

    [[nodiscard]] bool isEmpty() const{return topIndex == -1;}

    [[nodiscard]] int size() const{ return topIndex + 1; }

    friend std::ostream& operator<<(std::ostream& os, StackArray& s){
        if (s.topIndex == -1){
            os << "Stack is empty";
        }else{
            for(int i = 0; i <= s.topIndex; i++){
                os << "| " << s.arr[i] << " ";
            }
            os << "|";
        }

        return os;
    }

    ~StackArray() { delete[] arr; }

};

int main(){
    StackArray s{};
    std::cout << s << std::endl;

    s.push(2);
    s.push(3);
    s.push(5);

    std::cout << s << std::endl;


    return 0;
}