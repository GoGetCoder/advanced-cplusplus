/*
 - Useful when creating multiple objects of same type, but we dont know object type
   until runtime.
 - We need an if-else structure for object creation, but not in client class/code.
 - Add an additional level of indirection, factor_class/fcatory_method, which is used by client.
 - Client passes object type to factory_method and gets the object
 - This way client code is decoupled and doesn't change with additional object creation
*/

#include <iostream>
using namespace std;

// Without factory
class CVehicle{
public:
    virtual void print_vehicle_info() = 0;
    virtual ~CVehicle(){}
};
class CFourWheeler : public CVehicle{
public:
    CFourWheeler(){
        cout << "Creating a 4-Wheeler" << endl;
    }
    void print_vehicle_info() override{
        cout << "I'm a 4-wheeler" << endl;
    }
};
class CTwoWheeler : public CVehicle{
public:
    CTwoWheeler(){
        cout << "Creating a 2-Wheeler" << endl;
    }
    void print_vehicle_info() override{
        cout << "I'm a 2-wheeler" << endl;
    }
};
class CThreeWheeler : public CVehicle{
public:
    CThreeWheeler(){
        cout << "Creating a 3-Wheeler" << endl;
    }
    void print_vehicle_info() override{
        cout << "I'm a 3-wheeler" << endl;
    }
};

// With factory method
class CVehicleFactoryMethod{
public:
    static CVehicleFactoryMethod* build_vehicle_factory_method(int type);
    virtual void print_vehicle_info() = 0;
    virtual ~CVehicleFactoryMethod(){}
};
class CFourWheeler2 : public CVehicleFactoryMethod{
public:
    CFourWheeler2(){
        cout << "Creating a 4-Wheeler" << endl;
    }
    void print_vehicle_info() override{
        cout << "I'm a 4-wheeler" << endl;
    }
};
class CTwoWheeler2 : public CVehicleFactoryMethod{
public:
    CTwoWheeler2(){
        cout << "Creating a 2-Wheeler" << endl;
    }
    void print_vehicle_info() override{
        cout << "I'm a 2-wheeler" << endl;
    }
};
class CThreeWheeler2 : public CVehicleFactoryMethod{
public:
    CThreeWheeler2(){
        cout << "Creating a 3-Wheeler" << endl;
    }
    void print_vehicle_info() override{
        cout << "I'm a 3-wheeler" << endl;
    }
};

CVehicleFactoryMethod* CVehicleFactoryMethod::build_vehicle_factory_method(int type){
    if(type == 2)
        return (new CTwoWheeler2);
    else if(type == 3)
        return (new CThreeWheeler2);
    else
        return (new CFourWheeler2);
}

int main(){
    vector<CVehicle*> no_factory_vehicles;
    vector<CVehicleFactoryMethod*> factory_vehicles;
    int is_not_factory;
    int choice2;

    cout << "1. WITHOUT FACTORY METHOD \n2. WITH FACTORY METHOD \n";
    cin >> is_not_factory;

    while(true){
        cout << "FourWheeler(4)\nTwoWheeler(2)\nThreeWheeler(3)\nRun(0)" << endl;
        cin >> choice2;
        if(choice2 == 0)
            break;
        if(is_not_factory){
            if(choice2 == 4){                
                no_factory_vehicles.push_back(new CFourWheeler());
            }
            else if(choice2 == 3){
                cout << "Creating a 3-Wheeler" << endl;        
                no_factory_vehicles.push_back(new CThreeWheeler());
            }
            else if(choice2 == 2){
                cout << "Creating a 2-Wheeler" << endl;
                no_factory_vehicles.push_back(new CTwoWheeler());
            }
        }    
        else{
            factory_vehicles.push_back(CVehicleFactoryMethod::build_vehicle_factory_method(choice2));
        }
    }

    if(is_not_factory){
        for(auto v : no_factory_vehicles)
        v->print_vehicle_info();
    }
    else{
        for(auto v : factory_vehicles)
        v->print_vehicle_info();
    }

    if(is_not_factory){
        for(auto v : no_factory_vehicles)
        delete v;
    }
    else{
        for(auto v : factory_vehicles)
        delete v;
    }    
    return 0;
}