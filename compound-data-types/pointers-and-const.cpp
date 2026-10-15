// 12.9 - Pointers and const
//
// NOTES:
// - A normal pointer lets me change BOTH what it points at (the address)
//   and the value at that address.
// - A normal pointer (int*) can't point at a const variable. If it could,
//   I could change the const value through it.
// - const int* ptr   = pointer to const. The VALUE is frozen (through ptr),
//                      but ptr can point somewhere else.
// - int* const ptr   = const pointer. The ADDRESS is frozen, must be
//                      initialized, but the value can be changed.
// - const int* const = both frozen. I can only read through it.
// - A pointer to const can point at const OR non-const variables.
//   It only freezes the value when accessed THROUGH the pointer.
//   (the variable itself can still be changed by its own name)
//
// HOW TO READ A DECLARATION: right to left
//   const int* ptr  -> ptr is a pointer to a const int
//   int* const ptr  -> ptr is a const pointer to an int
//   const on the LEFT of *  belongs to the VALUE
//   const on the RIGHT of * belongs to the POINTER

#include <iostream>

int main()
{
    // ---------- 1. normal pointer: change address AND value ----------
    int x { 5 };
    int* ptr { &x };
    int y { 6 };
    ptr = &y;                  // point at a different object
    *ptr = 7;                  // change the value at that address (y)
    std::cout << "x = " << x << ", y = " << y << '\n';   // x = 5, y = 7

    // ---------- 2. pointer to const: value frozen, address free ----------
    const int cx { 5 };
    const int* pc { &cx };     // ok: pointer to const int
    // *pc = 6;                // error: can't change value through pc
    const int cy { 6 };
    pc = &cy;                  // ok: pointer itself is not const
    std::cout << *pc << '\n';  // 6

    // ---------- 3. pointer to const can point at a NON-const variable ----------
    int n { 5 };
    const int* pn { &n };
    // *pn = 6;                // error: not allowed through pn
    n = 6;                     // ok: n itself is still non-const
    std::cout << *pn << '\n';  // 6 (pn sees the change)

    // ---------- 4. const pointer: address frozen, value free ----------
    int a { 5 };
    int b { 6 };
    int* const cp { &a };      // must be initialized
    // cp = &b;                // error: address can't change
    *cp = 50;                  // ok: value is non-const
    std::cout << "a = " << a << ", b = " << b << '\n';   // a = 50, b = 6

    // ---------- 5. const pointer to const: both frozen ----------
    int value { 5 };
    const int* const cpc { &value };
    // *cpc = 6;               // error
    // cpc = &a;               // error
    std::cout << *cpc << '\n'; // 5 (can only read)

    // ---------- 6. all four side by side ----------
    int v { 5 };
    int w { 8 };
    int* ptr0 { &v };              // value ok, address ok
    const int* ptr1 { &v };        // value NO,  address ok
    int* const ptr2 { &v };        // value ok,  address NO
    const int* const ptr3 { &v };  // value NO,  address NO

    *ptr0 = 10;    // changes v to 10
    ptr0 = &w;     // ptr0 now points at w
    ptr1 = &w;     // ptr1 now points at w
    // *ptr1 = 1;  // error
    *ptr2 = 20;    // changes v to 20 (ptr2 still points at v)
    // ptr2 = &w;  // error
    // *ptr3 = 1;  // error
    // ptr3 = &w;  // error

    std::cout << v << ' ' << w << ' '
              << *ptr0 << ' ' << *ptr1 << ' ' << *ptr2 << ' ' << *ptr3 << '\n';
    // v=20, w=8, *ptr0=8, *ptr1=8, *ptr2=20, *ptr3=20

    // ---------- 7. Experiments (uncomment ONE at a time) ----------
    // Paste the exact compiler error next to each, then comment it out again.
    // Where a line needs a helper variable, uncomment that line too.

    // int* bad1 { &cx };       // normal pointer to a const variable
    // Error I got:

    // *pc = 100;               // change value through pointer to const
    // Error I got:

    // cp = &b;                 // change address of a const pointer
    // Error I got:

    // int* const noInit;       // const pointer without initialization
    // Error I got:

    // *cpc = 1;                // change value through const pointer to const
    // Error I got:

    return 0;
}