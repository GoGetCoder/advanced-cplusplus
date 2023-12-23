#include<iostream>
using namespace std;

void testGreet(void (*greet)(string)){
    greet("Jesse");
}

void testDivide(double (*divide)(double, double)){
    auto rval = divide(9.0, 3.0);
    cout << rval << endl;
}

int main(){

    // lambda with a string param and void return
    auto pGreet = [](string name){ cout << "Hello " << name << endl; };

    pGreet("Walt");

    testGreet(pGreet);

    // lambda with 2 double params and a double return type
    auto pDivide = [](double a, double b) -> double{ 
        /* Conflicting return types - int Vs double
           Resolved by specifying trailing return type as double */
        if(b == 0){
            return 0; //return an int
        }
        return a/b; // return a double
    };

    cout << pDivide(10.0, 5.0) << endl;
    cout << pDivide(10.0, 0) << endl;

    testDivide(pDivide);

    return 0;
}