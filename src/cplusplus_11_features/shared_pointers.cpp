/*
std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer. Several shared_ptr objects may own the same object. The object is destroyed and its memory deallocated when either of the following happens:
    1. the last remaining shared_ptr owning the object is destroyed;
    2. the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset().
The object is destroyed using delete-expression or a custom deleter that is supplied to shared_ptr during construction.

All std::shared_ptrs pointing to it collaborate to ensure its destruction at the point where it's no longer needed. 
When the last std::shared_ptr pointing to an object stops pointing there (e.g., because the std::shared_ptr is destroyed 
or made to point to a different object), that std::shared_ptr destroys the object it points to.

A std::shared_ptr can tell whether it's the last one pointing to a resource by consulting the resource's reference count, 
a value associated with the resource that keeps track of how many std::shared_ptrs point to it.

The existence of the reference count has performance implications:

    1. std::shared_ptrs are twice the size of a raw pointer, because they internally contain a raw pointer to the resource 
       as well as a raw pointer to the resource's reference count(or control block).
    2. Memory for the reference count must be dynamically allocated. Conceptually, the reference count is associated with 
       the object being pointed to, but pointed-to objects know nothing about this. They thus have no place to store a 
       reference count. (A pleasant implication is that any objectâeven those of built-in typesâmay be managed by 
       std::shared_ptrs.) Item 21 explains that the cost of the dynamic allocation is avoided when the std::shared_ptr is 
       created by std::make_shared, but there are situations where std::make_shared canât be used. Either way, 
       the reference count is stored as dynamically allocated data.
    3. Increments and decrements of the reference count must be atomic, because there can be simultaneous readers and 
       writers in different threads. For example, a std::shared_ptr pointing to a resource in one thread could be 
       executing its destructor (hence decrementing the reference count for the resource it points to), while, in a different
       thread, a std::shared_ptr to the same object could be copied (and therefore incrementing the same reference count).
       Atomic operations are typically slower than non-atomic operations, so even though reference counts are usually only 
       a word in size, you should assume that reading and writing them is comparatively costly.

Like std::unique_ptr (see Item 18), std::shared_ptr uses delete as its default resource-destruction mechanism, but it 
also supports custom deleters. The design of this support differs from that for std::unique_ptr, however. 
For std::unique_ptr, the type of the deleter is part of the type of the smart pointer. For std::shared_ptr, it's not:

// lambda for custom delete
auto loggingDel = [](Widget *pw)        // custom deleter
                  {                     // (as in Item 18)
                    makeLogEntry(pw);
                    delete pw;
                  };

std::unique_ptr<                        // deleter type is
  Widget, decltype(loggingDel)          // part of ptr type
  > upw(new Widget, loggingDel);

std::shared_ptr<Widget>                 // deleter type is not
  spw(new Widget, loggingDel);          // part of ptr type

 I remarked earlier that a std::shared_ptr object contains a pointer to the reference count for the object it points to. 
 That's true, but it's a bit misleading, because the reference count is part of a larger data structure known as the 
 control block. There's a control block for each object managed by std::shared_ptrs. The control block contains, 
 in addition to the reference count, a copy of the custom deleter, if one has been specified. 
 If a custom allocator was specified, the control block contains a copy of that, too.

An object's control block is set up by the function creating the first std::shared_ptr to the object. 
At least that's what's supposed to happen. In general, it's impossible for a function creating a std::shared_ptr to an 
object to know whether some other std::shared_ptr already points to that object, so the following rules for control block 
creation are used:

    1. std::make_shared always creates a control block. It manufactures a new object to point to, so there is certainly 
       no control block for that object at the time std::make_shared is called.
    2. A control block is created when a std::shared_ptr is constructed from a unique-ownership pointer 
       (i.e., a std::unique_ptr or std::auto_ptr). Unique-ownership pointers don't use control blocks, so there should be 
       no control block for the pointed-to object. (As part of its construction, the std::shared_ptr assumes ownership of 
       the pointed-to object, so the unique-ownership pointer is set to null.)
    3. When a std::shared_ptr constructor is called with a raw pointer, it creates a control block. If you wanted to create
       a std::shared_ptr from an object that already had a control block, you'd presumably pass a std::shared_ptr or a 
       std::weak_ptr as a constructor argument, not a raw pointer. std::shared_ptr constructors taking std::shared_ptrs or 
       std::weak_ptrs as constructor arguments don't create new control blocks, because they can rely on the smart pointers
       passed to them to point to any necessary control blocks.

A consequence of these rules is that constructing more than one std::shared_ptr from a single raw pointer gives you a 
complimentary ride on the particle accelerator of undefined behavior, because the pointed-to object will have multiple 
control blocks. Multiple control blocks means multiple reference counts, and multiple reference counts means the object will
 be destroyed multiple times (once for each reference count). That means that code like this is bad, bad, bad:

auto pw = new Widget;                          // pw is raw ptr

std::shared_ptr<Widget> spw1(pw, loggingDel);  // create control
                                               // block for *pw

std::shared_ptr<Widget> spw2(pw, loggingDel);  // create 2nd
                                               // control block
                                               // for *pw!

Now, the constructor for spw1 is called with a raw pointer, so it creates a control block (and thereby a reference count) 
for what's pointed to. In this case, thatâs *pw (i.e., the object pointed to by pw). In and of itself, that's okay, 
but the constructor for spw2 is called with the same raw pointer, so it also creates a control block 
(hence a reference count) for *pw. *pw thus has two reference counts, each of which will eventually become zero, and 
that will ultimately lead to an attempt to destroy *pw twice. The second destruction is responsible for the u
ndefined behavior.

There are at least two lessons regarding std::shared_ptr use here. 
    1. First, try to avoid passing raw pointers to a std::shared_ptr constructor. The usual alternative is to use 
       std::make_shared, but in the example above, we're using custom deleters, and that's not possible with 
       std::make_shared. 
    2. Second, if you must pass a raw pointer to a std::shared_ptr constructor, pass the result of new directly 
       instead of going through a raw pointer variable. If the first part of the code above were rewritten like this,

std::shared_ptr<Widget> spw1(new Widget,    // direct use of new
                             loggingDel);
it'd be a lot less tempting to create a second std::shared_ptr from the same raw pointer. Instead, the author of the 
code creating spw2 would naturally use spw1 as an initialization argument (i.e., would call the std::shared_ptr 
copy constructor), and that would pose no problem whatsoever:

std::shared_ptr<Widget> spw2(spw1);     // spw2 uses same
                                        // control block as spw1


*/
#include <iostream>
#include <memory>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std;

class Test :  public enable_shared_from_this<Test>{

private:

    int i{};
    vector<shared_ptr<Test>> spList;

public:

    Test(int val) : i(val){}

    void add_this(){
        spList.emplace_back(shared_from_this());     
    }

    void display(){
        cout << "---List of sps---" << endl;
        for(shared_ptr<Test> sp: spList){
            cout << sp.get() << ", " << sp.use_count() << ", " << endl;
        }
    }
};
 
int main()
{
    auto cutom_deleter_1 = [](int* ptr)
    {
        cout << "custom_deleter_1" << endl;
        delete ptr;
    };
    shared_ptr<int> spInt1 = shared_ptr<int>(new int(3), cutom_deleter_1);

    // spInt1 is pointing to an int object and this object has a control block assoicated with it    
    cout << "spInt1: " << spInt1.get() << ", " << spInt1.use_count() << ": " << *spInt1 << endl;

    {
        shared_ptr<int> spInt2 = shared_ptr<int>(spInt1);

        // spInt1 & spInt2 are pointing to same int obj, use_count = 2 & control fblock is not duplicated
        // get() shows both sp's are pointing to same int obj
        cout << endl << "spInt1: " << spInt1.get() << ", " << spInt1.use_count() << ": " << *spInt1 << endl;
        cout << "spInt2: " << spInt2.get() << ", " << spInt2.use_count() << ": " << *spInt2 << endl;

        {
            // can also create shared_ptr using make_shared
            shared_ptr<int> spInt3 = std::make_shared<int>(5);            
            cout << endl << "spInt3: " << spInt3.get() << ", " << spInt3.use_count() << ": " << *spInt3 << endl;
        }
    }

    // use_count reduces to 1, spInt2 is destroyed
    cout << endl << "spInt1: " << spInt1.get() << ", " << spInt1.use_count() << ": " << *spInt1 << endl;
    /*
    {
        auto cutom_deleter_2 = [](int* p)
        {
            cout << endl << "custom_deleter2" << endl;
            try
            {
                delete p;
            }
            catch(const std::exception& e)
            {
                cout << "Caught exception !!!!" << endl; 
                cout << e.what() << '\n';
            }
        };

        int* ptrInt = new int(8);
        shared_ptr<int> spInt4(ptrInt, cutom_deleter_2); // creates a control block for int obj 8
        cout << endl << "spInt4: " << spInt4.get() << ", " << spInt4.use_count() << ": " << *spInt4 << endl;
        {
            // now, if you want to create another shared_ptr pointing to same int obj
            shared_ptr<int> spInt5(ptrInt); // this creates a duplicate control block, ref count is not increamented
            cout << "spInt5: " << spInt5.get() << ", " << spInt5.use_count() << ": " << *spInt5 << endl;
        } // control block and obj is freed once her
    } // for the second time again delete is initiated on the same object, run_time exception hit here.
    */

    // the correct way to do the above is
    {
        int* ptrInt = new int(8);
        shared_ptr<int> spInt4(ptrInt); // creates a control block for int obj 8
        cout << endl << "spInt4: " << spInt4.get() << ", " << spInt4.use_count() << ": " << *spInt4 << endl;
        {
            // now, if you want to create another shared_ptr pointing to same int obj
            shared_ptr<int> spInt5(spInt4); // no duplication of control block, ref count is increamented
            cout << "spInt5: " << spInt5.get() << ", " << spInt5.use_count() << ": " << *spInt5 << endl;
        } // control block and obj is freed once her
        cout << endl << "spInt4: " << spInt4.get() << ", " << spInt4.use_count() << ": " << *spInt4 << endl;
    } // for the second time again delete.

    Test test{12};
    test.add_this();
    test.display();

    cout << endl << endl  << "Done with main!!" << endl;

    return 0;
}