#include<iostream>
#include<memory>
using namespace std;

// memory is deallocated automatically

class Test{
public:
    Test(){
        cout << "created" << endl;
    }

    void greet(){
        cout << "Hello" << endl;
    }

    ~Test(){
        cout << "destroyed" << endl;    
    }
};

int main(){
    {
    unique_ptr<Test> pTest1(new Test);
    pTest1->greet();

    unique_ptr<Test[]> pTest2(new Test[2]);
    pTest2[1].greet();
    } // destroyed automatically

    cout << "finished" << endl;
    
    return 0;
}