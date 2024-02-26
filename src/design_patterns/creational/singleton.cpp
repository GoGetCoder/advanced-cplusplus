/*
 - "Singleton" is a creational design pattern which ensures only one instance of a class is created &
    it provides a global point of access to that instance (static method to return the instance).
 - It provides an encapsulated "just-in-time" or "first-use" initialization.
   (instance is "static private" and accessor is "static public")
*/
#include <iostream>
using namespace std;

class Singleton{
public:
    static Singleton* get_instance(){
        if(m_instance == nullptr)
            m_instance = new Singleton;
        return m_instance;
    }
    void set_value(int v){
        m_value = v;
    }
    void show(){
        cout << "Value: " << m_value << endl;
    }
private:
    Singleton(){}
    static Singleton* m_instance;
    int m_value;
};

Singleton* Singleton::m_instance = nullptr;

int main(){
    cout << endl;
    Singleton* instance1 = Singleton::get_instance();
    instance1->set_value(20);
    cout << "--instance1--" << endl;
    instance1->show();

    cout << endl;
    Singleton* instance2 = Singleton::get_instance(); // actually same as instance1
    instance2->set_value(200);
    cout << "--instance2--" << endl;
    instance2->show();

    cout << endl;
    cout << "--instance1--" << endl;
    instance1->show();

    return 0;
}