#include "iostream"
#include "print"

class Node{
public:
    int data;
    Node* next;
    Node* prev;
    Node(int val):data(val), next(nullptr), prev(nullptr){}
};

class DoublyLinkedList{
private:
    Node* head;
    Node* tail;
    int length;
public:
    DoublyLinkedList(): head(nullptr), tail(nullptr), length(0){}

    void insertFront(int val) {  // Insert at the beginning
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    void insertEnd(int val){
        Node* newNode = new Node(val);
        if (!tail){
            head = tail = newNode;
        }else{
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }
    void deleteFront(){
        if (!head) return;
        // removing head
        Node* temp = head;
        head = head->next;

        // removing pointer to prev
        if (head) head->prev = nullptr;
        else tail = nullptr;  // If list becomes empty

        delete temp;
        length--;
    }
    void deleteEnd(){
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;

        if(tail) tail->next = nullptr;
        else head = nullptr;

        delete temp;
        length--;
    }

    [[nodiscard]] bool search(int val) {
        Node* node = head;
        while (node){
            if (node->data == val) return true;
            node = node->next;
        }
        return false;
    }

    [[nodiscard]] int size() const{
        return length;
    }

    friend std::ostream& operator<<(std::ostream& os, DoublyLinkedList& dll){
        Node* node = dll.head;
        os << "Size: " << dll.size() << " | (HEAD) ";
        while(node){

            if (node->next)
                os << node->data << " -> ";
            else
                os << node->data;

            node = node->next;
        }
        os << " (TAIL)";
        return os;
    }

    ~DoublyLinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main(){
    DoublyLinkedList dll{};

    dll.insertFront(5);
    dll.insertFront(4);
    dll.insertEnd(6);

    std::cout << dll << std::endl;

    dll.deleteFront();
    std::cout << dll << std::endl;

    dll.deleteEnd();
    std::cout << dll << std::endl;

    std::cout << dll.search(6) << " " <<  dll.search(5) << std::endl;

    return 0;
}