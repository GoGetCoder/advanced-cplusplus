#include <iostream>
#include <vector>
using  namespace std;

void vectorBasics()
{
    vector<string> strings(5); // predefined size of 5
    strings.push_back("one");
    strings.push_back("two");
    strings.push_back("three");

    cout << strings.size() << endl; // size is 8. There were already 5 elements, we pused 3 more.    

    // iterating through a vector
    //index-based
    cout << "\nindex-based" << endl;
    cout << "---------------" << endl;
    for(int i=0; i<strings.size(); i++)
    {
        cout << strings[i] << endl;  // print 5 empty elements first, then one, two, three.
    }
    //iterator-based
    cout << "\niterator-based" << endl;
    cout << "-----------------" << endl;
    for(vector<string>::iterator it = strings.begin(); it != strings.end(); it++)
    {
        cout << *it << endl;  // print 5 empty elements first, then one, two, three.
    }
}

void vectorsAndMemory()
{
    vector<double> numbers(20);

    cout << "Size: " << numbers.size() << endl;
    int capacity = numbers.capacity(); // capacity is the size of the internal array managed by vector
    cout << "Capacity: " << capacity << endl;

    for(int i=0; i<10000; i++)
    {
        if(capacity != numbers.capacity())
        {
            capacity = numbers.capacity();
            cout << "Capacity: " << capacity << endl;
        }
        numbers.push_back(i);
    }

    cout << "Size(Before clear): " << numbers.size() << endl;
    cout << "Capacity(Before clear): " << capacity << endl;
    
    numbers.clear();

    cout << "Size(After clear): " << numbers.size() << endl; // size is 0 but not capacity
    cout << "Capacity(After clear): " << capacity << endl;
}

void twoDimVectors()
{
    vector< vector<int> > table_of_12(10, vector<int>(3, 0));
    for(int row=0; row < table_of_12.size(); row++)
    {
        table_of_12[row][0] = 12;
        table_of_12[row][1] = (row + 1);
        table_of_12[row][2] = 12 * table_of_12[row][1];
    }

    for(int row=0; row < table_of_12.size(); row++)
    {
        cout << table_of_12[row][0] << " x " << table_of_12[row][1] << " = "
             << table_of_12[row][2] << endl;        
    }
}

int main()
{
    //vectorBasics();
    //vectorsAndMemory();
    twoDimVectors();
    return 0;
}