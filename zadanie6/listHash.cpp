#include <iostream>
#include <list>
#include <chrono>

using namespace std::chrono;
using namespace std;
class HashTable{
private:
    int length;
    list<int> *table;
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
    table = new list<int>[length];
}

void HashTable::insert(int value) {
    table[hashFun(value)].push_back(value);
}

bool HashTable::search(int value) {
    int key = hashFun(value);
    list<int>::iterator i;
    for(i = table[key].begin(); i!=table[key].end(); i++)
        if(*i == value) break;
    if(i!=table[key].end()) return true;
    else return false;
}

void HashTable::deleteEl(int value) {
    int key = hashFun(value);
    list<int>::iterator i;
    for(i = table[key].begin(); i!=table[key].end(); i++)
        if(*i == value) break;
    if(i!=table[key].end()) table[key].erase(i);
}

int HashTable::hashFun(int x) const {
    return x%length;
}

void HashTable::print() {
    cout<<"Printing"<<endl;
    for (int i = 0; i < length; i++) {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x;
        cout << endl;
    }
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
    int a[] = {3, 6, 5, 11, 16};
    int n = sizeof(a)/sizeof(a[0]);

    HashTable hashTable(5);
    for (int i = 0; i < n; i++)
        hashTable.insert(a[i]);
    hashTable.print();

    if (hashTable.search(11)) cout<<"Found"<<endl;
    else cout<<"Not found"<<endl;

    hashTable.deleteEl(11);
    hashTable.print();

    test();
}
