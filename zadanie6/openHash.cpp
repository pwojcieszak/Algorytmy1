#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std;

const int k = 3;

class HashTable{
private:
    int length;
    int *table;
    int size;
public:
    explicit HashTable(int length);
    void insert(int value);
    bool search(int value);
    void deleteEl(int value);
    int hashFun(int x) const;
    void print();
};

HashTable::HashTable(int length) {
    this->length=length;
    table = (int*)calloc(length, sizeof(int));
    this->size = 0;
}

void HashTable::insert(int value) {
    if(size<length){
        int key = hashFun(value);
        while(table[key]!=0){
            key=(key+k)%length;
        }
        size++;
        table[key]=value;
    }
    else cout<<"Table is full"<<endl;
}

bool HashTable::search(int value) {
    if(size!=0){
        int key = hashFun(value);
        int n = 0;
        while(table[key]!=0 && n!=length-1){
            if(table[key]==value){
                return true;
            }
            key=(key+k)%length;
            n++;
        }
        return false;
    }
    return false;
}

void HashTable::deleteEl(int value) {
    if(size!=0){
        int key = hashFun(value);
        while(table[key]!=0){
            if(table[key]==value){
                table[key]=0;
                size--;
            }
            key=(key+k)%length;
        }
    }
}

int HashTable::hashFun(int x) const {
    return x%length;
}

void HashTable::print() {
    cout<<"Printing"<<endl;
    for (int i = 0; i < length; i++)
        cout<<i<< "   "<<table[i]<<endl;
}

void test(){
    int N=100;
    int b[N];
    srand(time(0));
    for(int i=0; i<N;i++)
        b[i] = 1 + ( std::rand() % ( 499 - 1 + 1 ) );

    HashTable hashTest(N);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        hashTest.insert(b[i]);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Sredni czas insert "<<duration.count()/N<<endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        hashTest.search(b[i]);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Sredni czas search "<<duration.count()/N<<endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        hashTest.deleteEl(b[i]);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout<<"Sredni czas delete "<<duration.count()/N<<endl;
}

int main() {
    int a[] = {3, 5, 6, 11, 16};
    int n = sizeof(a)/sizeof(a[0]);

    HashTable hashTable(5);
    for (int i = 0; i < n; i++)
        hashTable.insert(a[i]);
    hashTable.print();
    if (hashTable.search(11)) cout<<"Found"<<endl;
    else cout<<"Not found"<<endl;

    hashTable.deleteEl(11);
    hashTable.print();

    //test();
}
