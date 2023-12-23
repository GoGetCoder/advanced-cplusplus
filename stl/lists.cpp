#include <iostream>
#include <list>
using namespace std;

// lists are like vectors, they hold a list of things.
// one important difference is, in a vector elements can only be inserted at the end,
// where as in lists, we can insert elements at the end, beginning or in the middle.

int main()
{
    list<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    for(list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
    {
        cout << *it << endl;
    }
    cout << endl;

    // add '0' to the beginning
    numbers.push_front(0);
    for(list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
    {
        cout << *it << endl;
    }
    
    cout << endl;
    // add '100' after the first element
    list<int>::iterator it = numbers.begin();
    it++;
    numbers.insert(it, 100);
    for(list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
    {
        cout << *it << endl;
    }

    cout << endl;
    // erase '2' from list
    list<int>::iterator erase = numbers.begin();
    while(*erase != 2)
    {
        erase++;
    }    
    numbers.erase(erase);
    for(list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
    {
        cout << *it << endl;
    }
    return 0;
}