#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

struct SingleLinkedListNode
{
    int data;
    SingleLinkedListNode *next;
};

void add(SingleLinkedListNode** head, int data, SingleLinkedListNode* nodeBefore = nullptr)
{
    auto* newNode = new SingleLinkedListNode{data, nullptr};

    if (*head == nullptr){
        *head = newNode;
        return;
    }
    SingleLinkedListNode *currentNode = *head;
    while (currentNode->next != nullptr && currentNode != nodeBefore) currentNode = currentNode->next;
    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

void remove(SingleLinkedListNode** head, SingleLinkedListNode* nodeToDelete)
{
    if (*head == nullptr){
        return;
    }

    SingleLinkedListNode *currentNode = *head;
    if(currentNode == nodeToDelete){
        *head = nodeToDelete->next;
        delete nodeToDelete;
        return;
    }

    while (currentNode->next != nullptr && currentNode->next != nodeToDelete) currentNode = currentNode->next;
    if(currentNode->next == nullptr) return;
    currentNode->next = currentNode->next->next;
    delete nodeToDelete;
}

SingleLinkedListNode* find(SingleLinkedListNode* head, int data)
{
    SingleLinkedListNode *currentNode = head;

    if (head == nullptr){
        return nullptr;
    }

    while (currentNode->next != nullptr && currentNode->data != data) currentNode = currentNode->next;
    if(currentNode->data == data) return currentNode;
    return nullptr;
}

void displayList(SingleLinkedListNode *node)
{
    while (node != nullptr)
    {
        cout<<node->data<<"-->";
        node = node->next;
    }
    cout << "null";
}

void test (SingleLinkedListNode** head){
    auto start = std::chrono::high_resolution_clock::now();
    add(head, 15);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    start = std::chrono::high_resolution_clock::now();
    SingleLinkedListNode* x = find(*head, 15);
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    start = std::chrono::high_resolution_clock::now();
    remove(head, x);
    stop = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    ofstream a;
    a.open("SP.txt", std::ios_base::out);
    if (a.is_open())
    {
        a<<duration1.count()<<" "<<duration2.count()<<" "<<duration3.count()<<endl;
        a.close();
    }
    else cout << "Unable to open file";
}

int main()
{
    SingleLinkedListNode* head = nullptr;

    add(&head, 12);
    add(&head, 9);
    add(&head, 13);
    add(&head, 1);
    add(&head, 50, find(head, 12));
    remove(&head, find(head, 12));
    add(&head, 20);

    cout<<"Final linked list: "<<endl;
    displayList(head);
    //test(&head);
    return 0;
}