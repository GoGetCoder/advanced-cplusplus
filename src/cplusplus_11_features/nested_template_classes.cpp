#include<iostream>
#include "ring.h"
using namespace std;

int main()
{   
    ring<string> textring(3);

    textring.add({"one", "two", "three", "four"}); 

    cout << endl;
    cout << "Using get()" << endl;
    cout << "-------------" << endl;
    for(int i=0; i<textring.size(); i++){
        cout << textring.get(i) << endl;
    }
 
    // c++ 98 style
    cout << endl;
    cout << "Using iterator" << endl;
    cout << "---------------" << endl;
    for(ring<string>::iterator it=textring.begin(); it != textring.end(); it++){
        cout << *it << endl;
    }
    
    // c++ 11 style
    cout << endl;
    cout << "Using range-based loop" << endl;
    cout << "-----------------------" << endl;
    for(auto value: textring){
        cout << value << endl;
    }

    // Output - 
    // four
    // two
    // three   

    
    return 0;
}