/*
 - Decorator design pattern is a structural desing pattern that enables dynamic addition of new behavior or responsibility
   to individual objects without altering their underlying class structure.
 - It achieves this by creating a set of decorator classes that wrap concrete components, which represent core functionality.
*/
#include <iostream>
#include <string>
using namespace std;

class IceCream{
public:
    virtual string get_descrption() const = 0;
    virtual double get_cost() const = 0;
};

class VanillaIcecream : public IceCream{
public:
    string get_descrption() const override{
        return "Vanilla IceCream" ;
    }
    double get_cost() const override{
        return 160.0;
    }
};

class IceCreamDecorator : public IceCream{
protected:
    IceCream* m_icecream;
public:
    IceCreamDecorator(IceCream* ic) : m_icecream(ic){ }
    string get_descrption() const override{
        return m_icecream->get_descrption();
    }
    double get_cost() const override{
        return m_icecream->get_cost();
    }
};

class ChocolateDecorator : public IceCreamDecorator{
public:
    ChocolateDecorator(IceCream* ic) : IceCreamDecorator(ic){ }
    string get_descrption() const override{
        return m_icecream->get_descrption() + " with chocolate";
    }
    double get_cost() const override{
        return m_icecream->get_cost() + 100.0;
    }
};

int main(){
    VanillaIcecream* vanilla = new VanillaIcecream();
    cout << vanilla->get_descrption() << endl;
    cout << vanilla->get_cost() << endl;

    cout << "-------------------------------------" << endl;

    ChocolateDecorator* choc_dec = new ChocolateDecorator(vanilla);
    cout << choc_dec->get_descrption() << endl;
    cout << choc_dec->get_cost() << endl;

    delete vanilla;
    delete choc_dec;

    return 0;
}