#include <iostream>
#include <exception>
using namespace std;

// Always catch child-class exceptions before parent-class exceptions
// Eg. bad_alloc() exception is sub-class of exception. Hence, below code.
void goesWrong()
{
    bool error1 = false;
    bool error2 = true;

    if(error1)
    {
        throw bad_alloc();
    }
    if(error2)
    {
        throw exception();
    }    
}

int main()
{
    try
    {
        goesWrong();
    }
    catch(bad_alloc& e)
    {
        cout << "Catching bad_alloc exceptions." << endl;
        cout << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << "Catching parent exceptions." << endl;
        cout << e.what() << endl;
    }
    return 0;
}