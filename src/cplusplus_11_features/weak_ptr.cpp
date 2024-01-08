/*
A std::weak_ptr is an observer -- it can observe and access the same object as a 
std::shared_ptr (or other std::weak_ptrs) but it is not considered an owner. 
Remember, when a std::shared pointer goes out of scope, it only considers whether 
other std::shared_ptr are co-owning the object. std::weak_ptr does not count!

std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object t
hat is managed by std::shared_ptr. It must be converted to std::shared_ptr in order to 
access the referenced object.
std::weak_ptr models temporary ownership: when an object needs to be accessed only if it 
exists, and it may be deleted at any time by someone else, std::weak_ptr is used to 
track the object, and it is converted to std::shared_ptr to assume temporary ownership. 
If the original std::shared_ptr is destroyed at this time, the object's lifetime is extended 
until the temporary std::shared_ptr is destroyed as well.
Another use for std::weak_ptr is to break reference cycles formed by objects managed by 
std::shared_ptr. If such cycle is orphaned (i.e., there are no outside shared pointers into the cycle),
the shared_ptr reference counts cannot reach zero and the memory is leaked. To prevent this, 
one of the pointers in the cycle can be made weak.
*/

#include <iostream>
using namespace std;

class Person{
private:
    string m_name;
    // shared_ptr<Person> m_partner; // creates a cyclic dependency
                                     // ref count never becomes 0
        weak_ptr<Person> m_partner;
public:
    Person(string name) : m_name(name){
        cout << m_name << " is created." << endl;
    }
    ~Person(){
        cout << m_name << " is destroyed." << endl;
    }
    friend void partnerUp(shared_ptr<Person>& sp1, shared_ptr<Person>& sp2){

        sp1->m_partner = sp2;
        sp2->m_partner = sp1;
    }

    shared_ptr<Person> getPartner(){
        return m_partner.lock();
    }

    string& getName(){
        return m_name;
    }
};

int main(){

    auto ricky = make_shared<Person>("Ricky");
    auto lucy = make_shared<Person>("Lucy");

    partnerUp(ricky, lucy);

    //cout << "There's a cyclic dependency between ricky and lucy, none get destroyed" << endl;
/*
    One downside of std::weak_ptr is that std::weak_ptr are not directly usable (they have no operator->). 
    To use a std::weak_ptr, you must first convert it into a std::shared_ptr. 
    Then you can use the std::shared_ptr. To convert a std::weak_ptr into a std::shared_ptr, you can use the lock()
    member function.
  */
    auto rickys_partner = ricky->getPartner();
    cout << ricky->getName() << "'s partner is " << rickys_partner->getName() << endl; 
    return 0;
}