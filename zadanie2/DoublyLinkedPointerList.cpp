#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

struct DoublyLinkedListNode
{
    int data;
    DoublyLinkedListNode *next;
    DoublyLinkedListNode *prev;
};

void add(DoublyLinkedListNode** head, int data, DoublyLinkedListNode* nodeBefore = nullptr)
{
    auto* newNode = new DoublyLinkedListNode{data, nullptr, nullptr};
    if (*head == nullptr) {
        *head = newNode;
        return;
    }
    if(nodeBefore != nullptr){
        newNode->next = nodeBefore->next;
        nodeBefore->next = newNode;
        newNode->prev = nodeBefore;
        return;
    }
    DoublyLinkedListNode *currentNode = *head;
    while (currentNode->next != nullptr) currentNode = currentNode->next;
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    newNode->prev = currentNode;
    if (newNode->next != nullptr) newNode->next->prev = newNode;
}

void remove(DoublyLinkedListNode** head, DoublyLinkedListNode* nodeToDelete)
{
    if (*head == nullptr)
        return;

    if (*head == nodeToDelete)
        *head = nodeToDelete->next;

    if (nodeToDelete->next != nullptr)
        nodeToDelete->next->prev = nodeToDelete->prev;

    if (nodeToDelete->prev != nullptr)
        nodeToDelete->prev->next = nodeToDelete->next;

    delete nodeToDelete;
}

DoublyLinkedListNode* find(DoublyLinkedListNode* head, int data)
{
    DoublyLinkedListNode *currentNode = head;

    if (head == nullptr){
        return nullptr;
    }

    while (currentNode->next != nullptr && currentNode->data != data) currentNode = currentNode->next;
    if(currentNode->data != data) return nullptr;
    return currentNode;
}

void displayList(DoublyLinkedListNode *node)
{
    if(node->prev == nullptr) cout<<"null-->";
    while (node != nullptr)
    {
        cout<<node->data<<"-->";
        node = node->next;
    }
    cout << "null";
}

void test (DoublyLinkedListNode** head){
    auto start = std::chrono::high_resolution_clock::now();
    add(head, 15);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    start = std::chrono::high_resolution_clock::now();
    DoublyLinkedListNode* x = find(*head, 15);
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    start = std::chrono::high_resolution_clock::now();
    remove(head, x);
    stop = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    ofstream a;
    a.open("DP.txt", std::ios_base::out);
    if (a.is_open())
    {
        a<<duration1.count()<<" "<<duration2.count()<<" "<<duration3.count()<<endl;
        a.close();
    }
    else cout << "Unable to open file";
}

int main()
{
    DoublyLinkedListNode* head = nullptr;

    add(&head, 1);
    add(&head, 2);
    add(&head, 3);
    add(&head, 4, find(head, 1));
    add(&head, 5);
    remove(&head, find(head, 1));

    cout<<"Final linked list: "<<endl;
    displayList(head);
    //test(&head);
    return 0;
}