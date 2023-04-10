#include <iostream>

using namespace std;
const int N = 3;

class KolejkaTab{
public:
    int array[N]{};
    int counter =0;
    int first = 0;
    int last = 0;
    KolejkaTab() = default;
    void enqueue (int x);
    int dequeue ();
    void view();
};
void KolejkaTab::enqueue(int x){
    if(counter < N){
        array[last%N] = x;
        last++;
        counter++;
    }
    else {
        cout<<"Queue full. Element not added: "<<x<<endl;
    }
}

int KolejkaTab::dequeue(){
    if(counter>0){
        first++;
        counter--;
        return array[(first-1)%N];
    }
    return -1;
}

void KolejkaTab::view(){
    cout<<"FIRST --> ";
    for(int i = first; i != last; i++) cout<<array[i%N]<<" ";
    cout<<" --> LAST ";
}

int main() {
    KolejkaTab kolejka{};
    kolejka.enqueue(10);
    kolejka.enqueue(11);
    kolejka.enqueue(12);
    kolejka.enqueue(13);
    cout<<"Dequeued "<<kolejka.dequeue()<<endl;
    kolejka.enqueue(13);
    cout<<"Dequeued "<<kolejka.dequeue()<<endl;
    kolejka.enqueue(14);
    kolejka.view();
}

struct Queue {
    int front, rear, capacity;
    int* queue;
    Queue(int c)
    {
        front = rear = 0;
        capacity = c;
        queue = new int;
    }

    ~Queue() { delete[] queue; }

    // function to insert an element
    // at the rear of the queue
    void queueEnqueue(int data)
    {
        // check queue is full or not
        if (capacity == rear) {
            printf("\nQueue is full\n");
            return;
        }

            // insert element at the rear
        else {
            queue[rear] = data;
            rear++;
        }
        return;
    }

    // function to delete an element
    // from the front of the queue
    void queueDequeue()
    {
        // if queue is empty
        if (front == rear) {
            printf("\nQueue is  empty\n");
            return;
        }

            // shift all the elements from index 2 till rear
            // to the left by one
        else {
            for (int i = 0; i < rear - 1; i++) {
                queue[i] = queue[i + 1];
            }

            // decrement rear
            rear--;
        }
        return;
    }

    // print queue elements
    void queueDisplay()
    {
        int i;
        if (front == rear) {
            printf("\nQueue is Empty\n");
            return;
        }

        // traverse front to rear and print elements
        for (i = front; i < rear; i++) {
            printf(" %d <-- ", queue[i]);
        }
        return;
    }

    // print front of queue
    void queueFront()
    {
        if (front == rear) {
            printf("\nQueue is Empty\n");
            return;
        }
        printf("\nFront Element is: %d", queue[front]);
        return;
    }
};