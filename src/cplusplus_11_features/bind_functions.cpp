#include<iostream>
#include<functional>
using namespace std;
using namespace placeholders;

// bind allows you to create aliases for functions, like function pointers

int add(int a, int b, int c){
    cout << a << ", " << b << ", " << c << endl;
    return (a + b +c);
}

class Test{
public:
    int add(int a, int b, int c){
        cout << a << ", " << b << ", " << c << endl;
        return (a + b +c);
    }
};

int run(function<int(int, int)> func){
    return func(7, 3); // add(3, 100, 7)
}

int main(){
    
    auto calculate1 = bind(add, 3, 4, 5);
    auto calculate2 = bind(add, _1, _2, _3); // using placeholders for args
    auto calculate3 = bind(add, _2, _3, _1);
    auto calculate4 = bind(add, _2, 100, _1);

    cout << calculate1() << endl;

    cout << calculate2(10, 20, 30) << endl;

    cout << calculate3(10, 20, 30) << endl; // will be called as 'add(20, 30, 10)'

    cout << calculate4(10, 20) << endl; // will be called as 'add(20, 30, 10)'

    cout << run(calculate4) << endl;

    // we can also bind to class methods
    Test test;
    auto calculate5 = bind(&Test::add, test, _2, 100, _1);
    cout << run(calculate5) << endl;
    
    return 0;

}