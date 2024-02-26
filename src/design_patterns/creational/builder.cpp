/*
- Builder is a creational design pattern, that separates the construction process of complex object from its
  representation.
- By doing this we can create objects with different representation using the same build process.
- For a complex object (which requires several steps to create), there could be different types of this complex object.
  Eg. Pizza(complex object) - ChickenDominator, NonVegSupreme, Farmhouse, IndiePaneer (Different Types of the complex object).
- The builder design pattern will have the same construction process for all object types.
*/
#include <iostream>
#include <string>
using namespace std;

// Representation
class Pizza{
public:
    void set_base(const string& base){
        m_base = base;
    }
    void set_sauce(const string& sauce){
        m_sauce = sauce;
    }
    void set_toppings(const string& toppings){
        m_toppings = toppings;
    }
    void set_name(const string& name){
        m_name = name;
    }
    void show(){
        cout << "--" << m_name << " Pizza with--" << endl
             << "\"" << m_base << "\" " << "base." << endl
             << "\"" << m_sauce << "\" " << "sauce." << endl
             << "\"" << m_toppings << "\" " << "toppings." << endl;
    }
private:
    string m_base;
    string m_sauce;
    string m_toppings;
    string m_name;
};

// Construction
// Abstract Builder
class PizzaMaker{
public:
    virtual void make_base() = 0;
    virtual void add_sauce() = 0;
    virtual void add_toppings() = 0;
    virtual Pizza deliver_pizza() = 0;
};
// Concrete Builders
class ChickenDominator : public PizzaMaker{
public:
    ChickenDominator(){
        m_pizza.set_name("Chicken Dominator");
    }   
    void make_base() override{
        m_pizza.set_base("hand tossed");
    }
    void add_sauce() override{
        m_pizza.set_sauce("pizza");
    }
    void add_toppings() override{
        m_pizza.set_toppings("bbq chicken, chicken rashers, veggies");
    }
    Pizza deliver_pizza() override{
        return m_pizza;
    }
private:
    Pizza m_pizza;
};
class Farmhouse : public PizzaMaker{
public:
    Farmhouse(){
        m_pizza.set_name("Farmhouse");
    }
    void make_base() override{
        m_pizza.set_base("thin crust");
    }
    void add_sauce() override{
        m_pizza.set_sauce("tomato & jalapeno");
    }
    void add_toppings() override{
        m_pizza.set_toppings("onions, tomatos, capsicum, olive");
    }
    Pizza deliver_pizza() override{
        return m_pizza;
    }
private:
    Pizza m_pizza;
};

// Director
class Cook{
public:
    void make_pizza(PizzaMaker& maker){
        maker.make_base();
        maker.add_sauce();
        maker.add_toppings();
    }
};

int main(){
    Cook cook;

    cout << endl;
    ChickenDominator chk_dominator_builder;
    cook.make_pizza(chk_dominator_builder);
    Pizza chk_dom_pizza = chk_dominator_builder.deliver_pizza();
    chk_dom_pizza.show();

    cout << endl;
    Farmhouse farmhouse_builder;
    cook.make_pizza(farmhouse_builder);
    Pizza farmhouse_pizza = farmhouse_builder.deliver_pizza();
    farmhouse_pizza.show();

    return 0;
}