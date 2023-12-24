#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // with 'auto', no need to enter the actual type while initializing a variable
    // char texts[] = {"one", "two", "three"}; // pre c++ 11.
    auto texts = {"one", "two", "three"}; // c++ 11.
    for(auto text: texts){
        cout << text << endl;
    }

    vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);

    for(auto n: numbers){
        cout << n << endl;
    }

    string name = "Hello";
    for(auto c: name){
        cout << c << endl;
    }


    return 0;
}