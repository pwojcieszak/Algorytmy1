#include <iostream>

using namespace std;
const int N = 3;

class StosTab{
public:
    int array[N];
    int topIndex = -1;
    StosTab() = default;
    void push( int x);
    int pop();
    void view();
};

void StosTab::push(int x){
    if(topIndex < N-1){
        array[++topIndex] = x;
    }
    else
        cout<<"Stack full! Element not added: "<<x<<endl;
}

int StosTab::pop(){
    if(topIndex>=0)
        return array[topIndex--];
    return -1;
}

void StosTab::view(){
    for(int i=0; i<=topIndex; i++) cout<<array[i]<<" ";
    cout<<endl;
}

int main(){
    StosTab stos{};
    stos.push(10);
    stos.push(11);
    stos.push(12);
    stos.push(13);
    stos.push(14);
    cout<<"POPPED "<<stos.pop()<<endl;
    stos.push(15);
    stos.view();
}

