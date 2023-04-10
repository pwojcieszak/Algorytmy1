#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

void insertionSort(int tab[], int n) {
    int pom, j;
    for(int i=1; i<n; i++)
    {
        pom = tab[i];
        j = i-1;
        while(j>=0 && tab[j]>pom)
        {
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = pom;
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
            insertionSort(tab, n);
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
    insertionSort(tab, n);
    end = chrono::steady_clock::now();

    cout << "\nElementy po sortowaniu" << endl;
    for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
    cout << "\nCzas = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;

    //tester("insertion.dat");
}