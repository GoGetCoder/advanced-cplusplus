#include<iostream>
using namespace std;

class MyException : public exception{
public:
// throw() is saying this method wont throw any exception.
// throw(bad_alloc) - says, this method only throws bad_alloc exception.
    virtual const char* what() const throw()
    {
        return "Something bad happened.";
    }
};

class Test{
public:
    void goesWrong()
    {
        throw MyException();
    }
};

int main()
{
    Test test;
    try
    {
        test.goesWrong();
    }
    catch(MyException& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}