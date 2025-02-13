#include "iostream"

class Node{
public:
    int data;
    // Node* next is just a pointer, not a full Node, so it doesn’t cause infinite recursion
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    int length;
    Node* head;
public:
    SinglyLinkedList():length(0), head(nullptr){}

    void insertFront(int val){
        /// Insert at the beginning (O(1))
        Node* node = new Node(val);
        node->next = head;
        head = node;
        length++;
    }
    void insertEnd(int val){
        /// Insert at the end (O(n))
        if (!head){
            head = new Node(val);
            return;
        }
        else{
            Node* node = head;
            while(node->next){
                node = node->next;
            }
            node->next = new Node(val);
        }
        length++;
    }
    void deleteFront(){
        /// Remove the first element (O(1))
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        length--;
    }
    void deleteEnd(){
        /// Remove the last element (O(n))
        if (!head) return;

        if (!head->next){
            delete head;
            head = nullptr;
        }else{
            Node *node = head;
            while (node->next->next) {
                node = node->next;
            }
            delete node->next;
            node->next = nullptr;
        }
        length--;
    }
    bool search(int val){
        /// Search for a value (O(n))
        Node* node = head;
        while (node){
            if (node->data == val)return true;
            node = node->next;
        }
        return false;
    }

    int& operator[](int index){
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of bounds");
        }
        Node* node = head;
        while (index > 0) {
            node = node->next;
            index--;
        }
        return node->data;
    }

    friend std::ostream& operator<<(std::ostream& os, SinglyLinkedList& sll){
        Node* node = sll.head;
        os << "Size: " << sll.size() << " | (HEAD) ";
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

    [[nodiscard]] int size() const{
        /// Return the number of elements
        return length;
    }

    ~SinglyLinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};


int main(){
    SinglyLinkedList sll {};
    sll.insertFront(1);
    sll.insertFront(2);
    sll.insertEnd(4);
    std::cout << sll << std::endl;
    sll.insertFront(2);
    sll.deleteFront();
    std::cout << sll << std::endl;
    std::cout << sll.search(3) << std::endl;
    std::cout << sll.search(4) << std::endl;
    std::cout << sll[0] << std::endl;
    return 0;
}
