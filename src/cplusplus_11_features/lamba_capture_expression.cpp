#include <iostream>
using namespace std;

int main(){

    int one = 1;
    int two = 2;
    int three = 3;

    // capture one and two by value
    [one, two](){ 
        cout << "Capture one and two by value" << endl;
        cout << "----------------------------" << endl;
        cout << one << ", " << two << endl; 
        }();
        
    // default capture all local variables by value but capture three by reference
    [=, &three](){ 
        cout << "Capture only three by reference" << endl;
        cout << "-------------------------------" << endl;
        three = 7;
        cout << one << ", " << two << endl; 
        }();
        cout << three << endl;

    // default capture all local variables by reference
    [&](){ 
        cout << "Capture all locals by reference" << endl;
        cout << "-------------------------------" << endl;
        one = 3;
        two = 6;
        three = 9;        
        }();
        cout << one << ", " << two << ", " << three << endl; 

    // default capture all locals by reference, but two and three by value
    [&, two, three](){ 
        cout << "Capture all locals by reference, but two and three by value" << endl;
        cout << "------------------------------------------------------------" << endl;
        one = 300;        
        }();
        cout << one << ", " << two << ", " << three << endl; 

    return 0;
}