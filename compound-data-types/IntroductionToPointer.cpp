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

    // ---------- 10. Quiz Q2: what's wrong here? ----------
    // int v1 { 45 };
    // int* q { &v1 };
    // int v2 { 78 };
    // *q = &v2;      // Error I got:
    // My explanation:

    // ---------- 11. Experiments (uncomment ONE at a time) ----------
    // Paste the exact compiler error next to each line, then comment it out again.
    // int* bad1 { &d };   // Error I got:
    // int* bad2 { 5 };    // Error I got:

    return 0;
}