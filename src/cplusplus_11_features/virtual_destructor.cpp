/*
Virtual drstructors are used to take care of deleting the derived and base class objects in the correct order.
Correct  destruction sequence is reverse of construction, first call derived class destructor then base 
class destructor.

Use-case:
Derived* d = new Derived()
Base* b = d;

delete b;   // Here only base class destructor is called, since type of b is base.
            // It goes by early-binding principle.
            // If we make base class destructor as virtual, late-binding kicks in and both derived & base
            // class destructors are called in the right sequence.
*/

#include <iostream>
using namespace std;

class Base{
public:
    Base(){
        cout << "Base constructor." << endl;
    }
    ~Base(){
        cout << "Base destructor." << endl;
    } // Derived class destructor never called.
    /*
    virtual ~Base(){
        cout << "Base destructor." << endl;
    } // Calls Derived class destructor.
    */      
};

class Derived : public Base{
public:
    Derived(){
        cout << "Derived constructor." << endl;
    }
    ~Derived(){
        cout << "Derived destructor." << endl;
    }
};

int main(){
    Derived* d = new Derived();
    Base* b = d;
    delete b;
    return 0;
}
