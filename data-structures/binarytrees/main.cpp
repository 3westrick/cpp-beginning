#include "iostream"

class Node{
public:
    Node* left;
    Node* right;
    int data;
    Node(int val): data(val), left(nullptr), right(nullptr){}
    bool isLeaf() const {return !left && !right;}
};

class BinaryTree{
private:
    Node* root;

    Node* insertHelper(Node* node, int val) {
        if (!node) return new Node(val);
        if (val > node->data){
            node->right = insertHelper(node->right, val);
        }else if (val < node->data){
            node->left = insertHelper(node->left, val);
        }
        return node;
    }


    Node* searchHelper(Node* node, int val){
        if (!node) return nullptr;
        if (node->data == val) return node;
        return val > node->data ? searchHelper(node->right, val) : searchHelper(node->left, val);
    }

    Node* findMinHelper(Node* node){
        while (node && node->left) node = node->left;
        return node;
    }
    Node* findMaxHelper(Node* node){
        while (node && node->right) node = node->right;
        return node;
    }

    Node* removeHelper(Node* node, int val){
        if (!node) return nullptr;

        if (val == node->data){
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            Node* minNode = findMinHelper(node->right);
            node->data = minNode->data;
            node->right = removeHelper(node->right, minNode->data);
        }else if (val > node->data){
            node->right = removeHelper(node->right, val);
        }else{
            // val < node->data
            node->left = removeHelper(node->left, val);
        }
        return node;
    }

    void inorderHelper(Node* node) {
        if (!node) return;
        inorderHelper(node->left);
        std::cout << node->data << " ";
        inorderHelper(node->right);
    }

    void preorderHelper(Node* node) {
        if (!node) return;
        std::cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    void postorderHelper(Node* node) {
        if (!node) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        std::cout << node->data << " ";
    }

public:
    BinaryTree(): root(nullptr){}

    void insert(int val){
        root = insertHelper(root, val);
    }

    int findMin(){
        return findMinHelper(root)->data;
    }

    int findMax(){
        return findMaxHelper(root)->data;
    }

    bool search(int val){
        return searchHelper(root, val);
    }

    void remove(int val){
        root = removeHelper(root, val);
    }

    void inorderTraversal(){
        inorderHelper(root);
        std::cout << std::endl;
    }

    void preorderTraversal(){
        preorderHelper(root);
        std::cout << std::endl;
    }
    void postorderTraversal(){
        postorderHelper(root);
        std::cout << std::endl;
    }
};

int main(){
    BinaryTree bt{};
    bt.insert(4);
    bt.insert(3);
    bt.insert(6);
    bt.insert(6);
    bt.insert(2);
    bt.insert(5);
    bt.insert(7);
    bt.preorderTraversal();
    bt.postorderTraversal();
    std::cout << bt.findMax() << std::endl;
    std::cout << bt.findMin() << std::endl;
    std::cout << bt.search(1) << std::endl;
    std::cout << bt.search(7) << std::endl;
    bt.remove(4);
    bt.preorderTraversal();

    return 0;
}