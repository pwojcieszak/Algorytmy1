#include <iostream>

class Node{
public:
    int data;
    Node* left;
    Node* right;
    explicit Node(int d){
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

class Bst{
public:
    Node* root;
    Bst(){root = nullptr;}
    void insert(int);
    bool search(int);
    void deleteN(int);
    void inorder(Node*);
};

void Bst::insert(int data) {
    Node* cur_parent = root;
    Node* prev_parent;
    while(cur_parent){
        prev_parent = cur_parent;
        if (data < cur_parent->data)
            cur_parent = cur_parent->left;
        else
            cur_parent = cur_parent->right;
    }
    if(cur_parent == root) root = new Node(data);
    else if(prev_parent->data < data) prev_parent->right = new Node(data);
    else prev_parent->left = new Node(data);

}

bool Bst::search(int data) {
    Node* parent = root;
    while(parent) {
        if (parent->data == data) return true;
        else if(parent->data < data) parent = parent -> right;
        else parent = parent -> left;
    }
    return false;
}


void Bst::deleteN(int data) {
    Node* cur_parent = root;
    Node* prev_parent;
    while(true){
        if(cur_parent == nullptr) break;
        if (data < cur_parent->data){
            prev_parent = cur_parent;
            cur_parent = cur_parent->left;
        }
        else if (data > cur_parent->data) {
            prev_parent = cur_parent;
            cur_parent = cur_parent->right;
        }
        else {
            Node* temp;
            if (cur_parent->left == nullptr && cur_parent->right == nullptr)
                temp = nullptr;
            else if (cur_parent->left == nullptr) {
                temp = cur_parent->right;
            } else if (cur_parent->right == nullptr) {
                temp = cur_parent->left;
            }
            else{
                temp = cur_parent->right;
                Node* prev_temp = temp;
                while(temp->left) {
                    prev_temp = temp;
                    temp = temp -> left;
                }
                cur_parent -> data = temp -> data;
                prev_temp -> left = nullptr;
                delete(temp);
                break;
            }
            delete(cur_parent);
            if(prev_parent->data < data) prev_parent->right = temp;
            else prev_parent->left = temp;
            break;

        }
    }
}

void Bst::inorder(Node *parent) {
    if (parent != nullptr) {
        inorder(parent->left);
        std::cout<<parent->data<<" -> ";
        inorder(parent->right);
    }
}

int main() {
    Bst tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(4);
    tree.insert(8);
    tree.insert(12);
    tree.inorder(tree.root);
    if(tree.search(1)) std::cout<<"\nFound"<<std::endl;
    else std::cout<<"\nNot Found"<<std::endl;
    tree.deleteN(4);
    tree.inorder(tree.root);
    return 0;
}
