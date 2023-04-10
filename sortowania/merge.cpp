#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

void merge(int tab[], int l, int mid, int r){
    int nL = mid - l + 1;
    int nR = r - mid;
    int L[nL], R[nR];

    for (int i = 0; i < nL; i++)
        L[i] = tab[l + i];
    for (int j = 0; j < nR; j++)
        R[j] = tab[mid + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < nL && j < nR) {
        if (L[i] <= R[j]) {
            tab[k] = L[i];
            i++;
        }
        else {
            tab[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < nL) {
        tab[k] = L[i];
        i++;
        k++;
    }
    while (j < nR) {
        tab[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int tab[], int l, int r) {
    if (l>=r) return;
    int mid = (l+r)/2;
    mergeSort(tab, l, mid);
    mergeSort(tab, mid+1, r);
    merge(tab, l, mid, r);
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
            mergeSort(tab, 0, n-1);
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
    mergeSort(tab, 0, n-1);
    end = chrono::steady_clock::now();

    cout << "\nElementy po sortowaniu" << endl;
    for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
    cout << "\nCzas = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;

    //tester("merge.dat");
}