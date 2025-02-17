#include "iostream"

class Node{
private:
public:
    Node* next;
    int data;
    Node(int val):data(val), next(nullptr){}
};

class Stack{
private:
    Node* head;
    int length;
public:
    Stack():head(nullptr), length(0){}

    void push(int val){
        Node* node = new Node(val);
        node->next = head;
        head = node;
        length++;
    }

    void pop(){
        if (!head) return;
        Node* temp = head;
        head = temp->next;
        delete temp;
        length--;
    }

    int top(){
        if(!head) throw std::out_of_range("Stack is empty");
        return head->data;
    }

    bool isEmpty() { return head == nullptr; }

    int size() { return length; }

    friend std::ostream& operator<<(std::ostream& os, Stack& s){
        if (s.isEmpty()) {
            os << "Stack is empty";
        }else{
            Node* node = s.head;
            while(node){
                os << "| " << node->data << " ";
                node = node->next;
            }
            os << "|";
        }
        return os;
    }

    ~Stack(){
        while(head){
            Node* node = head;
            head = node->next;
            delete node;
        }
    }

};

int main(){
    Stack s{};
    std::cout << s << std::endl;
    s.push(2);
    s.push(4);
    std::cout << s << std::endl;
    return 0;
}