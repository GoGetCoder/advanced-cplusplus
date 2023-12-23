#include <iostream>
using namespace std;

//lambdas are similar to anonymous functions

void test(void (*pfunc)()){
    pfunc();
}

int main(){
    auto func = [](){ cout << "Hello from 'func()'" << endl; };
    
    // Usage 1
    [](){ cout << "Hello 'direct lambda call" << endl; }();

    //Usage 2
    func();

    //Usage 3 - Passing code to other functions
    test(func);

    //Usage 4 - Passing code directly to other functions
    test([](){ cout << "Hello from 'direct code sent to test()'" << endl; });

    return 0;
}