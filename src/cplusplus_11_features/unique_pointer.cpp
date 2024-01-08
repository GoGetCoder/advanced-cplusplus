/*
std::unique_ptr is a smart pointer that owns and manages another object through a pointer and 
disposes of that object when the unique_ptr goes out of scope.
The object is disposed of, using the associated deleter when either of the following happens:
    1. the managing unique_ptr object is destroyed.
    2. the managing unique_ptr object is assigned another pointer via operator= or reset().
*/
#include <iostream>
#include <memory>
#include <fstream>
#include <locale>
#include <cstdio>
#include <cassert>
#include <stdexcept>

using namespace std;

// helper class for runtime polymorphism
struct B
{
    virtual ~B() = default;

    virtual void bar() { cout << "B::bar" << endl; }
};

struct D : B
{
    D() { cout << "D::D" << endl; }
    ~D() { cout << "D::~D" << endl; }

    void bar() override { cout << "D::bar" << endl; }
};

class Parent
{
public:
    Parent(int a){
        cout << "In Parent: " << a << endl;
    }

    virtual void print() = 0;
};

class Child : public Parent
{
public:
    Child(int a) : Parent(a)
    {
        cout << "In Child: " << a << endl;
    }

    void print() override
    {
        cout << "In print(CHILD)" << endl;
    }    
};

// a function consuming a unique_ptr can take it by value or by rvalue reference
unique_ptr<D> pass_through(unique_ptr<D> p)
{
    p->bar();
    return p;
}

// helper function for custom deleter demo
void close_file(FILE* fp)
{
    fclose(fp);
    cout << "destroying file via custom deleter close_file" << endl;
}

// unique_ptr-based linked list demo
struct List
{
    struct Node
    {
        int data;
        unique_ptr<Node> next;
    };

    unique_ptr<Node> head;

    ~List()
    {
        while(head)
        {
            auto next = std::move(head->next);
            head = std::move(next);
        }
    }

    void push(int data)
    {
        head = unique_ptr<Node>(new Node{data, std::move(head)});
    }
};

int main()
{
    cout << "1) Unique ownership semantics demo" << endl;
    {
        // create a uniquely owned resource
        unique_ptr<D> p = std::make_unique<D>();

        // transfer the ownership to pass_through
        // which in turn transfers the ownership back through the return value
        unique_ptr<D> q = pass_through(std::move(p));

        // p is now nullptr
        assert(!p);
    }

    cout << endl << "2) Runtime polymorphism demo" << endl;
    {
        // create a derived resource and point it via base type
        unique_ptr<B> p = std::make_unique<D>();

        p->bar();
    }

    cout << endl << "3) Custom deleter demo" << endl;
    ofstream("demo.txt") << 'x';
    {
        using unique_file_t = unique_ptr<FILE, decltype(&close_file)>;
        unique_file_t fp(std::fopen("demo.txt", "r"), &close_file);
        if(fp)
            cout << char(std::fgetc(fp.get())) << endl;
    }

    cout << endl << "4) Custom lambda-expression deleter and exception safety demo" << endl;
    try
    {
        unique_ptr<D, void(*)(D*)> p(new D, [](D* ptr)
        {
            cout << "destroying from lambda custom deleter" << endl;
            delete ptr;
        });        
    }
    catch(const std::exception& e)
    {
        std::cout << "Caught exception" << '\n';
    }
    

    cout << endl << "5) Trying some more polymorphism demo" << endl;
    unique_ptr<Parent> parent_ptr = std::make_unique<Child>(2);
    parent_ptr->print();

    return 0;
}