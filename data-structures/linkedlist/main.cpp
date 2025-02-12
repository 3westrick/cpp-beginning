#include "iostream"

class Node{
public:
    int data;
    // Node* next is just a pointer, not a full Node, so it doesn’t cause infinite recursion
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList{
    Node* head;
};