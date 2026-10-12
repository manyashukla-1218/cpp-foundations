// 12.7 - Introduction to pointers
//
// NOTES:
// - A pointer is an object that holds a memory address.
// - &x  (address-of)   : gives the address of x (returns a pointer, int*)
// - *p  (dereference)  : gives the object at the address (as an lvalue)
// - & and * are opposites.
// - & meanings: int& (reference) | &x (address-of) | x & y (bitwise AND)
// - Always initialize pointers (uninitialized = wild pointer).
// - Pointer type must match the type it points to.
// - ptr = &y  changes WHAT it points at; *ptr = 6 changes the VALUE pointed at.
// - Pointer size depends on architecture (4 bytes on 32-bit, 8 on 64-bit),
//   not on the pointed-to type.
// - Dereferencing a wild or dangling pointer = undefined behavior.

#include <iostream>
#include <typeinfo>

int main()
{
    // ---------- 1. address-of and dereference ----------
    int x { 5 };
    std::cout << "x        = " << x << '\n';
    std::cout << "&x       = " << &x << '\n';        // address (changes per run)
    std::cout << "*(&x)    = " << *(&x) << '\n';     // 5, & and * cancel out

    // ---------- 2. creating a pointer ----------
    int* ptr { &x };                                 // ptr holds x's address
    std::cout << "ptr      = " << ptr << '\n';       // same as &x
    std::cout << "*ptr     = " << *ptr << '\n';      // 5

    // ---------- 3. declaration traps (don't uncomment, just read) ----------
    // int* ptr1, ptr2;     // ptr2 is a plain int, NOT a pointer
    // int* ptr3, * ptr4;   // both are pointers
    // int* wild;           // uninitialized: wild pointer, never dereference it
    int* nullPtr {};        // null pointer (covered in 12.8)
    (void)nullPtr;          // silence "unused variable" warning

    // ---------- 4. types must match ----------
    int i { 5 };
    double d { 7.0 };
    int* iPtr { &i };       // ok
    double* dPtr { &d };    // ok
    // int* bad1 { &d };    // error: int* can't point to a double
    // int* bad2 { 5 };     // error: no literals for pointers
    std::cout << *iPtr << ' ' << *dPtr << '\n';      // 5 7

    // ---------- 5. assignment: two different things ----------
    int a { 5 };
    int b { 6 };
    int* p { &a };
    std::cout << *p << '\n';        // 5
    p = &b;                         // (A) p now points at b
    std::cout << *p << '\n';        // 6
    *p = 60;                        // (B) the object p points at (b) becomes 60
    std::cout << "a = " << a << ", b = " << b << '\n';   // a = 5, b = 60

    // ---------- 6. pointer vs reference ----------
    int v { 5 };
    int& ref { v };
    int* vp { &v };
    std::cout << v << ref << *vp << '\n';   // 555
    ref = 6;
    std::cout << v << ref << *vp << '\n';   // 666
    *vp = 7;
    std::cout << v << ref << *vp << '\n';   // 777

    // ---------- 7. & returns a pointer ----------
    std::cout << typeid(v).name() << '\n';    // "i"  on gcc (int)
    std::cout << typeid(&v).name() << '\n';   // "Pi" on gcc (pointer to int)

    // ---------- 8. size of pointers ----------
    char* chPtr {};
    int* intPtr {};
    long double* ldPtr {};
    std::cout << sizeof(chPtr) << ' ' << sizeof(intPtr) << ' '
              << sizeof(ldPtr) << '\n';       // 8 8 8 on a 64-bit build

    // ---------- 9. dangling pointer (UB, don't uncomment to "test" it) ----------
    // int* dangling { &x };
    // {
    //     int y { 6 };
    //     dangling = &y;
    // }                              // y destroyed, dangling is now invalid
    // std::cout << *dangling;        // undefined behavior

    // ---------- 10. Quiz Q1: what does this print? ----------
    // Question (assume short is 2 bytes, 32-bit machine):
    //   short value{7}; short otherValue{3}; short* qptr{&value};
    //   Print &value, value, qptr, *qptr.
    //   Then *qptr = 9 and print all four again.
    //   Then qptr = &otherValue and print all four again.
    //   Finally print sizeof(qptr) and sizeof(*qptr).
    //
    // ANSWER (lesson's version, with its example addresses):
    //   0012FF60   <- &value
    //   7          <- value
    //   0012FF60   <- qptr (holds value's address, same as &value)
    //   7          <- *qptr (the object qptr points at is value)
    //
    //   0012FF60   <- &value (address never changes)
    //   9          <- value (changed through the pointer: *qptr = 9)
    //   0012FF60   <- qptr (still points at value)
    //   9          <- *qptr
    //
    //   0012FF54   <- &otherValue
    //   3          <- otherValue
    //   0012FF54   <- qptr (now points at otherValue)
    //   3          <- *qptr
    //
    //   4          <- sizeof(qptr): a pointer is 4 bytes on a 32-bit machine
    //   2          <- sizeof(*qptr): that's sizeof(short)
    //
    // Why: *qptr = 9 changes the VALUE at the address (value becomes 9).
    //      qptr = &otherValue changes WHERE the pointer points.
    // On my 64-bit machine the addresses will differ and sizeof(qptr) is 8.
    short value { 7 };
    short otherValue { 3 };
    short* qptr { &value };

    std::cout << &value << '\n';
    std::cout << value << '\n';
    std::cout << qptr << '\n';
    std::cout << *qptr << '\n';
    std::cout << '\n';

    *qptr = 9;

    std::cout << &value << '\n';
    std::cout << value << '\n';
    std::cout << qptr << '\n';
    std::cout << *qptr << '\n';
    std::cout << '\n';

    qptr = &otherValue;

    std::cout << &otherValue << '\n';
    std::cout << otherValue << '\n';
    std::cout << qptr << '\n';
    std::cout << *qptr << '\n';
    std::cout << '\n';

    std::cout << sizeof(qptr) << '\n';     // 8 on 64-bit (4 on 32-bit)
    std::cout << sizeof(*qptr) << '\n';    // 2 (size of a short)

    // ---------- 11. Quiz Q2: what's wrong with this code? ----------
    // Question:
    //   int v1{45};
    //   int* q{&v1};
    //   int v2{78};
    //   *q = &v2;    // assign q to the address of v2 (that was the intent)
    //
    // Answer: *q is an int (it's v1), but &v2 is an int* (an address).
    //         You can't put an address into an int, so it won't compile.
    //         To point q at v2:         q = &v2;
    //         To copy v2's value to v1: *q = v2;
    //
    // To see the real error, uncomment the lines below:
    // int v1 { 45 };
    // int* q { &v1 };
    // int v2 { 78 };
    // *q = &v2;
    // Error I got:

    // ---------- 12. Experiments (uncomment ONE at a time) ----------
    // Paste the exact compiler error next to each line, then comment it out again.
    // int* bad1 { &d };   // Error I got:
    // int* bad2 { 5 };    // Error I got:

    return 0;
}