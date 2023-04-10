#include <iostream>
#include <string>

int max(int number1, int number2){
    if(number1>number2) return number1;
    return number2;
}
class Polynomial {
private:
    double *coefficients;
    int size;
public:
    Polynomial(double *arr, int size) {
        coefficients = new double [size*sizeof(double)];
        for(int i=0; i<size; i++)
        {
            coefficients[i] = arr[i];
        }
        this->size = size;
    }
    Polynomial() = default;

    int getSize() const { return size; }
    double getElement(int i) const {return coefficients[i];}

    Polynomial operator+(const Polynomial &p2) const{
        int resultSize = max(size, p2.size);
        double arr[resultSize];
        int i = 0;
        while (i < size && i < p2.size) {
            arr[i] = coefficients[i] + p2.coefficients[i];
            i++;
        }
        while (i < size) {
            arr[i] = coefficients[i];
            i++;
        }
        while (i < p2.size) {
            arr[i] = p2.coefficients[i];
            i++;
        }
        return {arr, resultSize};
//        int k = resultSize-1;
//        while (k >= 0) {
//            if(k>=p2.size)
//                arr[k] = coefficients[k];
//            else if (k>=size)
//                arr[k] = p2.coefficients[k];
//            else
//                arr[k] = coefficients[k] + p2.coefficients[k];
//            k--;
//        }
//        return {arr, resultSize};
    }

    Polynomial operator-(const Polynomial &p2) const{
        int resultSize = max(size, p2.size);
        double arr[resultSize];
        int i = 0;
        while (i < size && i < p2.size) {
            arr[i] = coefficients[i] - p2.coefficients[i];
            i++;
        }
        while (i < size) {
            arr[i] = coefficients[i];
            i++;
        }
        while (i < p2.size) {
            arr[i] = -p2.coefficients[i];
            i++;
        }
        return {arr, resultSize};
    }

    Polynomial operator*(const Polynomial &p2) const{
        int resultSize = size + p2.size -1;
        double arr[resultSize];
        for(int i = 0; i<resultSize; i++) arr[i] = 0.0;
        for(int i=0; i<size; i++)
            for(int j=0; j<p2.size; j++){
                arr[i+j] += coefficients[i] * p2.coefficients[j];
            }
        return {arr, resultSize};
    }

    double evaluate(double x){
        double result = coefficients[0];
        for(int i=1; i<size; i++)
            result = result*x + coefficients[i];

        return result;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            if (coefficients[i] == 0) continue;
            if (i == 0 && coefficients[i] == -1) std::cout<<"-x^"<<size - 1 - i;
            else if (i == 0 && coefficients[i] == 1) std::cout<<"x^"<<size - 1 - i;
            else if (i == 0) std::cout<<coefficients[i]<<"x^"<<size - 1 - i;
            else {  //printy elementów innych niż pierwszy
                if (i == size - 2) //przedostatni element (x zamiast x^1)
                    if(coefficients[i] == -1) std::cout<<"-x";
                    else if(coefficients[i] == 1) std::cout<<"+x";
                    else if(coefficients[i]<0) std::cout<<coefficients[i]<<"x";
                    else std::cout<<"+"<<coefficients[i]<<"x";
                else if (i == size - 1) //wyraz wolny
                    if(coefficients[i]<0) std::cout<<coefficients[i]<<std::endl;
                    else std::cout<<"+"<<coefficients[i]<<std::endl;
                else if (coefficients[i]<0 &&coefficients[i]!=-1) //od tej pory wyrazy pozostale
                    std::cout<<coefficients[i]<<"x^"<<size - 1 - i;
                else if (coefficients[i]>0 && coefficients[i] != 1)
                    std::cout<<"+"<<coefficients[i]<<"x^"<<size - 1 - i;
                else if (coefficients[i] == -1) std::cout<<"-x^"<<size - 1 - i;
                else std::cout<<"+x^"<<size - 1 - i;
            }
        }
        std::cout<<"\n";
    }
};

std::ostream &operator<<(std::ostream &os, const Polynomial p) {
    double value;
    int size = p.getSize();
    for (int i = 0; i < size; i++) {
        value = p.getElement(i);
        if (value == 0) continue;
        if (i == 0 && value == -1) std::cout<<"-x^"<<size - 1 - i;
        else if (i == 0 && value == 1) std::cout<<"x^"<<size - 1 - i;
        else if (i == 0) std::cout<<value<<"x^"<<size - 1 - i;
        else {  //printy elementów innych niż pierwszy
            if (i == size - 2) //przedostatni element (x zamiast x^1)
                if(value == -1) std::cout<<"-x";
                else if(value == 1) std::cout<<"+x";
                else if(value<0) std::cout<<value<<"x";
                else std::cout<<"+"<<value<<"x";
            else if (i == size - 1) //wyraz wolny
                if(value<0) std::cout<<value<<std::endl;
                else std::cout<<"+"<<value<<std::endl;
            else if (value<0 && value !=-1)
                std::cout<<value<<"x^"<<size - 1 - i;
            else if (value>0 && value != 1)
                std::cout<<"+"<<value<<"x^"<<size - 1 - i;
            else if (value == -1) std::cout<<"-x^"<<size - 1 - i;
            else std::cout<<"+x^"<<size - 1 - i;
        }
    }
    return os;
}


int maxPower(std::string polynomial){
    for(int i=0; i<polynomial.length(); i++)
        if (polynomial[i] == '^') return int(polynomial[i+1] -'0')+1;
    return 1;
}

bool is_number(char input){
    return (input<='9' && input>='0');
}

double convert (std::string input, int &poz){
    double liczba = 0;
    char znak = input[poz-1];
    bool przecinek = false;
    double k =1;
    while(poz < input.length() && (is_number(input[poz]) || input[poz] =='.' || input[poz] ==',')) {
        if (input[poz] == '.' || input[poz] == ',') przecinek = true;
        if (!przecinek) {
            liczba = liczba * 10 + input[poz] - '0';
            ++poz;
        } else {
            liczba = liczba + (input[++poz] - '0') / (10 * k);
            ++poz;
            k++;
        }
    }
    --poz;
    return (znak == '-' ? -liczba : liczba);
}

void fill(double* array, int arr_size, const std::string& input){
    for(int i=0; i<arr_size; i++) array[i] = 0;
    for(int i=0; i<input.length(); i++){
        if(is_number(input[i]) && input[i-1] != '^' && input[i-1] != 'x') {
            double liczba = convert(input, i);
            if (input[i+2] == '^')
                array[arr_size - input[i + 3] + '0' - 1] = liczba;
            else if(input[i+1] != 'x') array[arr_size - 1] = liczba;
            else array[arr_size -2] = liczba;
        }
        else if(input[i] =='x' && !is_number(input[i-1])) {
            if(input[i+1]=='^' && input[i-1]=='-') array[arr_size- input[i + 2] + '0' - 1] = -1;
            else if(input[i+1]=='^' && input[i-1]=='+') array[arr_size- input[i + 2] + '0' - 1] = 1;
            else if(input[i+1]!='^' && input[i-1]=='-') array[arr_size-2] = -1;
            else if(input[i+1]!='^' && input[i-1]=='+') array[arr_size-2] = 1;
        }
    }
}

int main() {
    std::string string1, string2;

    std::cout<<"Podaj w1: "<<std::endl;
    std::cin>>string1;
    int howManyCoefs1 = maxPower(string1);
    double arr1[howManyCoefs1];
    fill(arr1, howManyCoefs1, string1);
    Polynomial p1(arr1, howManyCoefs1);


    std::cout<<"Podaj w2: "<<std::endl;
    std::cin>>string2;
    int howManyCoefs2 = maxPower(string2);
    double arr2[howManyCoefs2];
    fill(arr2, howManyCoefs2, string2);
    Polynomial p2(arr2, howManyCoefs2);

    std::cout<<"\nWielomian1:\n";
    p1.print();
    std::cout<<"Wielomian2:\n";
    p2.print();

    //Podstawowe operacje
    std::cout<<"\n\nWynik dodawania: \n"<<p1+p2<<std::endl;
    std::cout<<"Wynik odejmowania: \n"<<p1-p2<<std::endl;
    std::cout<<"Wynik mnozenia: \n"<<p1*p2<<std::endl;
    std::cout<<"\nWartosc wielomianu1 dla x=2.4:  "<<p1.evaluate(2.4)<<std::endl;

    //Piaskownica
    std::cout<<"\n\nPiaskownica"<<std::endl;
    Polynomial test = ((p1-p2)*p1);
    std::cout<<test.evaluate(3.36);
    //24x^3-x^2-x+21
    //-x^3-1
    return 0;
}
