#include<iostream>
using namespace std;

int add(int a, int b){
    return (a + b);
}

int main(){
    auto retval = add(10, 20);
    cout << retval << endl;

    int (*pAdd)(int, int) = add;

    retval = pAdd(50, 50);
    cout << retval << endl;

    return 0;
}