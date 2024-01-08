#include<iostream>
#include<vector>
#include<initializer_list>
using namespace std;

class C{
    public:
        string text;
        int id;
};

struct S{
    string text;
    int id;
}r1 = {"Rello", 50}, r2 = {"R2llo", 55};

class Test1{
    public:
        Test1(initializer_list<string> texts){
            for(auto value: texts){
                cout << value << endl;
            }
        }

        void print(initializer_list<string> texts){
            for(auto value: texts){
                cout << value << endl;
            }
        }
};

class Test2{
    int id{3};
    string name{"Mike"};
public:

    Test2() = default;
    Test2(const Test2& other) = default;
    Test2& operator=(const Test2& other) = default;
    // Test2(const Test2& other) = delete; // make the obj non-copyable
    // Test2& operator=(const Test2& other) = delete; // make the obj non-copyable   

    Test2(int pId) : id(pId){

    }

    void print(){
        cout << id << ": " << name << endl;
    }
};

int main(){

    // c++98
    cout << "-------------c++98---------------" << endl;
    int values[] = {1, 2, 3};
    cout << values[0] << endl;

    C c1 = {"Hello", 100};
    cout << c1.text << endl;
    cout << c1.id << endl;

    S s1 = {"Hi", 10};
    cout << s1.text << endl;
    cout << s1.id << endl;

    cout << r1.text << endl;
    cout << r1.id << endl;
    cout << "---------------------------------" << endl;

    //c++11
    cout << "-------------c++11---------------" << endl;
    int val{10}; // I
    cout << "I.     " << val << endl;

    int numbers[]{1, 2, 3}; // II
    cout << "II.    " << numbers[2] << endl;

    int *pNumber1{&val}; // III
    cout << "III.   " << *pNumber1 << endl;

    int* pInts = new int[3]{3, 6, 9}; // IV
    cout << "IV.    " << pInts[1] << endl;
    delete[] pInts;

    int value1{}; // default init'd to 0 // V
    cout << "V.     " << value1 << endl;

    int* pNumber2{}; // default init'd to null(0x0) // VI
                     // equivalent to int* pNumbers2 = nullptr;
    cout << "VI.    " << pNumber2 << endl;

    int numbers2[5]{}; // VII
    cout << "VII.   " << numbers2[4] << endl;
    cout << "---------------------------------" << endl;

    // c++11 initializr lists
    cout << "-------------c++11 initializer list---------------" << endl;
    vector<string> strings{"one", "two", "three"}; // VIII
    cout << "VIII.  " << strings[1] << endl;

    Test1 test1{"apple", "orange", "banana"};
    test1.print({"carrot", "beans", "potato"});
    cout << "--------------------------------------------------" << endl;

    cout << "-------------c++11 object initialization---------------" << endl;
    Test2 test2;
    test2.print();

    Test2 test3(8);
    test3.print();
    cout << "-------------------------------------------------------" << endl;

    return 0;
}