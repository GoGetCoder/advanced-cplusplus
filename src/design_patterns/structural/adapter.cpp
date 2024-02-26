/*
- Adapter is a structural design pattern, that converts an interface of a class into another inetrface which the client expects.
- It lets classes with incompatible interfaces communicate with each other.
- It acts as a bridge between incompatibale classes.

Components of Adapter design pattern.
--------------------------------------
1. Target interface
   ----------------
   This is the interface the client expects and can work with.

2. Adaptee interface
   ----------------
   This is an existing class with an incompatible interface which needs to be integrated into
   the existing system which the client code operates in.

3. Adapter interface
   ----------------
   This class implements the target interface and internally uses the adaptee instance to make it
   compatible with the target.
*/

#include <iostream>
using namespace std;

// Target interface
class Printer{
public:
    virtual void print() = 0;
};
// Adaptee interface
class LegacyPrinter{
public:
    void print_legacy_method(){
        cout << "Printing in the legacy method" << endl;
    }
};
// Adapter interface - Implements target and declares adaptee as member.
class PrinterAdapter : public Printer{
public:
    void print() override{
        m_legacy_printer.print_legacy_method();
    }
private:
    LegacyPrinter m_legacy_printer;
};

void client_code(Printer& printer){
    printer.print();
}

int main(){
    PrinterAdapter adapter;
    client_code(adapter);
    return 0;
}