#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

void parentCondition(int tab[], int n, int r){
    int lChild = 2*r+1;
    int rChild = 2*r+2;
    int max = r;
    if (lChild < n && tab[lChild] > tab[max]) max = lChild;

    if (rChild < n && tab[rChild] > tab[max]) max = rChild;
    if(max != r) {
        swap(tab[r], tab[max]);
        parentCondition(tab, n, max);
    }
}

void heapSort(int tab[], int n) {
    for (int i = (n-2)/2; i>=0; i--)    //(n-2)/2   =   n/2 - 1
        parentCondition( tab, n, i);
    for( int i = n-1; i>0; i--){
        swap(tab[i], tab[0]);
        parentCondition(tab, i, 0);
    }
}

void tester(const char* algo) {
    chrono::steady_clock::time_point begin, end;
    ofstream a;
    for(int n=0; n<=5000; n+=500){
        a.open(algo, std::ios_base::app);
        int* tab = new int[n];
        for(int j=0;j<n;j++){
            int num = rand()%10000;
            tab[j]=num;
        }
        if (a.is_open())
        {
            begin = chrono::steady_clock::now();
            heapSort(tab, n);
            end = chrono::steady_clock::now();
            a<<n<<" "<<chrono::duration_cast<chrono::nanoseconds>(end - begin).count()<<endl;
            a.close();
        }
        else cout << "Unable to open file";
        delete[] tab;
    }
}

int main() {
    chrono::steady_clock::time_point begin, end;
    int n = 30, range = 100;
    int tab[n];

    srand(time(NULL));;
    for(int i=0;i<n;i++){
        int num = rand()%range;
        tab[i]=num;
    }

    cout<<"Elementy przed sortowaniem"<<endl;
    for(int i=0;i<n;i++)
        cout<<tab[i]<<" ";
    cout<<endl;

    begin = chrono::steady_clock::now();
    heapSort(tab, n);
    end = chrono::steady_clock::now();

    cout << "\nElementy po sortowaniu" << endl;
    for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
    cout << "\nCzas = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;

    //tester("heap.dat");
}