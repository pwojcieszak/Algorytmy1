#include "iostream"
#include <chrono>
#include <fstream>
using namespace std;

const int MAX_SIZE = 6;

void add(int head_index, int tab[][2], int data, int index_of_el_before = -1){
    if(index_of_el_before != -1 && tab[index_of_el_before][0] != 0 && index_of_el_before < MAX_SIZE){
        for(int i=head_index+1; i<MAX_SIZE; i++) {
            if (tab[i][0] == 0 && tab[i][1] == 0) {
                tab[i][1] = tab[index_of_el_before][1];
                tab[index_of_el_before][1] = i;
                tab[i][0] = data;
                return;
            }
        }
        cout<<"No space"<<endl;
        return;
    }
    else if(index_of_el_before == -1){
        for(int i=head_index; i<MAX_SIZE; i++){
            if(tab[i][1] == index_of_el_before){
                for(int j=1; j<MAX_SIZE; j++){
                    if(tab[j][0] == 0 && tab[j][1] == 0) {
                        tab[j][1] = tab[i][1];
                        tab[i][1] = j;
                        tab[j][0] = data;
                        return;
                    }
                }
                cout<<"No space"<<endl;
                return;
            }
        }
    }
    else cout<<"incorrect index"<<endl;
}

void remove (int head_index, int tab[][2], int index_of_element){
    for (int i = head_index; i < MAX_SIZE; i++)
        if (tab[i][1] == index_of_element && index_of_element < MAX_SIZE){
            tab[i][1] = tab[index_of_element][1];
            tab[index_of_element][0] = 0;
            tab[index_of_element][1] = 0;
            return;
        }

}
int find (int head_index, int tab[][2], int data){
    for (int i = head_index+1; i < MAX_SIZE; i++)
        if (tab[i][0] == data)
            return i;
    return -1;
}

void initializeList(int tab[][2]){
    tab[0][0] = -1;
    tab[0][1] = -1;
    for(int i=1; i<MAX_SIZE; i++)
        for (int j = 0; j < 2; j++) {
            tab[i][j] = 0;
        }
}

void displayList(int tab[][2]){
    for(int i = 0; i < MAX_SIZE; i++)
    {
        cout<<i<<" ";
        for(int j = 0; j < 2; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

void test (int tab[][2]){
    auto start = std::chrono::high_resolution_clock::now();
    add(0, tab, 15);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    start = std::chrono::high_resolution_clock::now();
    int x = find(0, tab, 15);
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    start = std::chrono::high_resolution_clock::now();
    remove(0, tab, x);
    stop = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    ofstream a;
    a.open("SC.txt", std::ios_base::out);
    if (a.is_open())
    {
        a<<duration1.count()<<" "<<duration2.count()<<" "<<duration3.count()<<endl;
        a.close();
    }
    else cout << "Unable to open file";
}

int main(){
    int tab[MAX_SIZE][2];
    initializeList(tab);

    add(0, tab, 10);
    add(0, tab, 20);
    add(0, tab, 30);
    add(0, tab, 40);
    add(0, tab, 25, find(0, tab, 20));
    remove(0, tab, find(0, tab, 40));
    add(0, tab, 45 , 3);
    remove(0, tab, find(0, tab, 45));


    displayList(tab);
    //test(tab);
    return 1;
}