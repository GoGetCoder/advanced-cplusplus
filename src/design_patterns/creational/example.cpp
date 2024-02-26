#include <iostream>
#include <string>

using namespace std;

class CFblockOut{

};

class C84BitPipeOut : public CFblockOut{
public:
    uint32_t out;
};

class C36PipeBitOut : public CFblockOut{
public:
    uint32_t out[2];
};

class TB{
public:
    template <typename T>
    void output_from_fblock(T& fblock_out);
};

template <typename T>
void TB::output_from_fblock(T& fblock_out)
{
    cout << "Template Fblock out Catcher "  << fblock_out << endl;
}

///////////////////////////////////////////////////////////////////////
class Parent{
public:
    void print(){
        cout << "Parent: print()" << endl;
    }
};

class Child : public Parent{
public:
    void print(){
        cout << "Child: print()" << endl;
    }
};
int main(){
    
    /*TB tb;
    int a = 10;
    tb.output_from_fblock(a);

    float b = 100.0;
    tb.output_from_fblock(b);*/

    Parent* p = new Child();
    p->print();

    return 0;
}