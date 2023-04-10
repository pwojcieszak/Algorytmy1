#include <iostream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

bool is_number(char input){
    return (input<='9' && input>='0');
}

double convert (string input, int &poz){
    double liczba = 0;
    while(poz < input.length() && is_number(input[poz]))
    {
        liczba = liczba * 10 + input[poz] - '0';
        ++poz;
    }
    --poz;
    return liczba;
}

double calculate (double a, double b, char c){
    switch (c) {
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '/':
            return a/b;
        case '*':
            return a*b;
        case '^':
            return pow(a,b);
        case 's':
            return sqrt(b);
        default:
            return 0;
    }
}

int main(int argc, char *argv[]){
    stack<double> stack;
    string input= "";
    for (int i = 1; i < argc; ++i){
        input += argv[i];
        input += " ";
    }
    double a, b;
    for(int i=0; i<input.length(); i++){
        if(is_number(input[i])) stack.push(convert(input, i));
        else if(input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*' || input[i] == '^') {
            if(stack.size() < 2)
            {
                cout<<"Incorrect ONP equation";
                return 0;
            }
            a = stack.top();
            stack.pop();
            b = stack.top();
            stack.pop();
            stack.push(calculate(b, a, input[i]));
        }
        else if(input[i] == 's'){
            if(stack.size() < 1)
            {
                cout<<"Incorrect ONP equation";
                return 0;
            }
            a = stack.top();
            stack.pop();
            stack.push(calculate(b, a, input[i]));
            i+=3;
        }
    }
    if(stack.size() != 1)
    {
        cout<<"Incorrect ONP equation";
        return 0;
    }
    cout<<"Result: "<<stack.top();
    return 1;
}
