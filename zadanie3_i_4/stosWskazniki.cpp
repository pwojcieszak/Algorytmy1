#include <iostream>

using namespace std;

struct node {
    int data;
    node *next;
};

class StosWsk{
public:
    node* topIndex = nullptr;
    StosWsk() = default;
    void push( int x);
    int pop();
    void view(node* el);
};

void StosWsk::push(int x){
    node* el = new node{x, nullptr};
    el->next = topIndex;
    topIndex = el;
}

int StosWsk::pop(){
    if(topIndex != nullptr){
        node* temp = topIndex;
        int tempV = topIndex -> data;
        topIndex = topIndex->next;
        delete temp;
        return tempV;
    }
    return -1;
}

void StosWsk::view(node* el) {
    if( el == nullptr ) return;
    view(el->next);
    cout << el->data << " ";
}

int main(){
    StosWsk stos{};
    stos.push(10);
    stos.push(11);
    stos.push(12);
    stos.push(13);
    stos.push(14);
    cout<<"POPPED "<<stos.pop()<<endl;
    stos.push(15);
    stos.view(stos.topIndex);
}

