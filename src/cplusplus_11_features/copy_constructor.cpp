#include <iostream>

using namespace std;

class Copy{

private:
    int a;    

public:
    Copy(int z) : a(z){

    }
    Copy(Copy& obj){
        a = obj.a;
    }
    void print(){
        cout << "Value of 'a' is: " << a << endl;
    }
};

int main(){

    Copy p(10);
    p.print();

    Copy q = p;
    q.print();

    return 0;
}