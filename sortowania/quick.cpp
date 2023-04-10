#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int partition(int arr[], int l, int r)
{
    int pivot = arr[r];
    int i = l - 1;

    for (int j = l; j <= r - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return (i + 1);
}

void quickSort(int tab[], int l, int r) {
    if (l < r) {
        int pivotNowy = partition(tab, l, r);

        quickSort(tab, l, pivotNowy - 1);
        quickSort(tab, pivotNowy + 1, r);
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
            quickSort(tab, 0, n-1);
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
    quickSort(tab, 0, n-1);
    end = chrono::steady_clock::now();

    cout << "\nElementy po sortowaniu" << endl;
    for (int i = 0; i < n; i++)
        cout << tab[i] << " ";
    cout << "\nCzas = " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;

    //tester("quick.dat");
}
