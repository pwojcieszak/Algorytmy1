#include <iostream>
#include <fstream>
#include <cmath>


int funkcja_haszujaca(int i){
    return pow(pow(i%9973,2), 0.5);
}

//int najlepsza_funkcja_haszujaca(int i){
//    int tmp = i*13379;
//    if(tmp<0){
//        tmp = -(tmp+1);
//    }
//    return tmp%INT_MAX;
//}

int main(int argc, char *argv[]) {
    std::ifstream plik_z_liczbami;
    plik_z_liczbami.open (argv[1]);
    int rozmiar_tablicy = atoi(argv[2]);
    int tablica[rozmiar_tablicy];

    int index;
    for (index=0; index<rozmiar_tablicy; index++){
        tablica[index] = 0;
    }
    int i;
    while (plik_z_liczbami >> i){
        index = funkcja_haszujaca(i) % rozmiar_tablicy;
        tablica[index]++;
    }
    float sum=0, sum2=0;
    for (index=0; index<rozmiar_tablicy; index++){
        sum += tablica[index];
        sum2 += tablica[index]*tablica[index];
    }
    plik_z_liczbami.close();
    sum /= rozmiar_tablicy;
    sum2 /= rozmiar_tablicy;
    std::cout<<sum<<" "<<sum2-sum*sum<<std::endl;
    return 1;
}
