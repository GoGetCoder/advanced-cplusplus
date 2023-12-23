#include <iostream>
using namespace std;

class Test{
private:
    int one{1};
    int two{2};
public:
    void run(){
        int three{3};
        int four{4};

        auto pLambda = [three, four, this](){
            cout << one << endl;
            cout << two << endl;
            cout << three << endl;
            cout << four << endl;
            // this is captured by reference
            one = 1000;
        };
        pLambda();
        cout << one << endl;
    }
};

int main(){
    Test test;
    test.run();
    return 0;
}