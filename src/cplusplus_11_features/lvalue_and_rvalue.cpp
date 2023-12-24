#include<iostream>>
using namespace std;

// lvalue: lhs of = & anything whose address is accessible. Eg Variable in memory.
// rvalue: rhs of = & anything whose address is inaccessible. Eg Literals (7, "cplusplus", 'g').
// Function return values, temp objects are rvalues. Cannot access its address.

class Test{   
};

Test getTest(){
    return Test();
}

void lvalue_rvalue_basics(){
    int one = 1; // rvalue is assigned to an lvalue.

    // but, when we're accessing addresses, always use lvalue.
    // we can never get the address of an rvalue (literals, function return types, temp variables/objects).

    int* pOne1 = &one; // legal, can get the address of 'one', its an lvalue.
    int* pOne2 = &7; // illegal, literal '7' is an rvalue, cannot access its address.

    // same thing applies to objects
    Test test = getTest();
    Test* pTest1 = &test; // legal, can get the address of 'test' object, its an lvalue
    Test* pTest2 = &(getTest()); // illegal, function return value is always an rvalue, cannot access its address
                                      // on comiple, we get "error: taking the address of a temporary object of type 'Test' "
}

// these are normal kind of references.
// we can only bind an lvalue to a non-const lvalue_reference
// if an lvalue_reference is a const, we can bind an rvalue to it
void lvalue_references(){

    int one = 1;
    int& refOne1 = one; // perfect, normal reference we've seen. lvalue bound to lvalue_reference.
    int& refOne2 = 1; // illegal, 1 is not an lvalue. Cannot bind it to a  non-const lvalue_reference.
    const int& refOne3 = 1; // legal, refOne3 is now a const, so we can bind an rvalue to it
}

// c++ 11 onwards we have rvalue_references
// these are references we can bind to an rvalue
void rvalue_references(){

    int one = 1;
    int& refOne1 = one; // perfect, normal reference we've seen. lvalue bound to lvalue_reference.
    int&& refOne2 = 1; // legal, can bind an rvalue to rvalue_reference

    // the same works for function return values and temp objects/variables
    // rvalue_references are used mostly in move_constructors

}

int main(){

    lvalue_rvalue_basics();
    lvalue_references();
    rvalue_references();
    return 0;
}