#include<iostream>
using namespace std;

// static_cast:      compile-time cast, wont check for unsafe type casting.
// dynamic_cast:     runt-ime cast, checks for safe type casting. Assigns nullptr when casting is not makin sense.
// reinterpret_cast: least preferred, brute force cast. Wont check for any unsafe type casting.

class Parent{
public:
    virtual void speak(){

    }
};

class Brother : public Parent{

};

class Sister : public Parent{

};

int main(){

    double d = 1.389;
    int i = static_cast<int>(d);

    Parent parent;
    Brother brother;
    Sister sister;

    Parent *ptrParent = &parent;
    
    // this is unsafe, Brother may have some methods not in parent.
    // below cast wont report this issue, when we use ptrBrother1 to call
    // Brother exclusive methods, it fails. This is actually a parent obj
    Brother *ptrBrother1 = static_cast<Brother*>(ptrParent);
    cout << ptrBrother1 << endl;

    // this is where dynamic_cast is useful, it can figure out casting is unsafe
    // in this situation, it wont cast and assigns nullptr
    Brother *ptrBrother2 = dynamic_cast<Brother*>(ptrParent);

    if(ptrBrother2 == nullptr){
        cout << "Invalid cast." << endl;
    }
    else{
        cout << ptrBrother2 << endl;
    }
    
    //Brother *ptrBrother3 = static_cast<Brother*>(&sister); // static_cast rightly complains, these are incompatible types

    Brother *ptrBrother4 = dynamic_cast<Brother*>(&sister); // dynamic_cast rightly assigns nullptr at runtime
    if(ptrBrother4 == nullptr){
        cout << "Invalid cast." << endl;
    }
    else{
        cout << ptrBrother4 << endl;
    }

    // reinterpret_cast simple casts the sister ptr to brother, this is very dangerous!!!
    // reinterpret_cast should be used only when we're not in a position to use static/dynamic cast
    // & we're absolutely sure the types are compatible
    Brother *ptrBrother5 = reinterpret_cast<Brother*>(&sister);
    if(ptrBrother5 == nullptr){
        cout << "Invalid cast." << endl;
    }
    else{
        cout << ptrBrother5 << endl;
    }

    return 0;
}