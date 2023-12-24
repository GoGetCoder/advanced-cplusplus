#include<iostream>
using namespace std;

// A functor is a class or struct that overloads () operator

struct Test{
    virtual bool operator()(string&) = 0;
};

struct Match : public Test{
    virtual bool operator()(string& text){
        return text == "lion";
    }
};

void check(string text, Test& test){
    if(test(text)){
        cout << "Text matches!!" << endl;
    }
    else{
        cout << "No match!!" << endl;
    }
}

int main(){
    Match m;
    check("lione", m);
    return 0;
}