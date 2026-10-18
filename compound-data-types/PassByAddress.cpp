// 12.10 - Pass by address
//
// NOTES:
// - Pass by address: the caller passes the ADDRESS of an object (via a pointer).
//   The address is copied into a pointer parameter, and the function
//   dereferences it to reach the real object.
// - No copy of the object is made, only the pointer (4 or 8 bytes) is copied.
// - If the parameter is a pointer to non-const, the function can modify the
//   original. If it must not modify it, use a pointer to const.
// - const int*       -> significant: tells the caller the value is read-only.
//   int* const       -> not significant for the caller, avoid it for parameters.
// - A pointer can be null, so check it before dereferencing:
//     (a) if (ptr) { ... }       fine for small functions
//     (b) if (!ptr) return;      early return, avoids nesting
//     (c) assert(ptr)            for "this should never happen"
// - Only lvalues have addresses, so &5 is an error.
// - Prefer pass by (const) reference. Pass by address only when needed.
//   "Pass by reference when you can, pass by address when you must."

#include <iostream>
#include <string>
#include <cassert>

// ---------- 1. the three ways side by side ----------
void printByValue(std::string val)              // copy of the string (expensive)
{
    std::cout << "by value:     " << val << '\n';
}

void printByReference(const std::string& ref)   // alias, no copy
{
    std::cout << "by reference: " << ref << '\n';
}

void printByAddress(const std::string* ptr)     // pointer to const, no copy
{
    std::cout << "by address:   " << *ptr << '\n';
}

// ---------- 2. the pointer parameter itself is a copy ----------
void showPtr(const int* p)
{
    std::cout << "param holds:      " << p << '\n';    // same as np holds
    std::cout << "param's own addr: " << &p << '\n';   // different from np's
}

// ---------- 3. modifying the argument through a pointer ----------
void changeValue(int* ptr)          // non-const pointer: can modify
{
    *ptr = 6;
}

// void readOnly(const int* ptr)
// {
//     *ptr = 6;                    // error: can't change a const value
// }

// ---------- 4. null checking: three styles ----------
void printSafe(int* ptr)            // (a) if inside
{
    if (ptr)
    {
        std::cout << "printSafe:   " << *ptr << '\n';
    }
}

void printEarly(int* ptr)           // (b) early return
{
    if (!ptr)
        return;

    // from here on we can assume ptr is valid
    std::cout << "printEarly:  " << *ptr << '\n';
}

void printAssert(const int* ptr)    // (c) assert + safe fallback
{
    assert(ptr);                    // stops the program in debug mode if null

    if (!ptr)                       // in release mode we still don't crash
        return;

    std::cout << "printAssert: " << *ptr << '\n';
}

// ---------- 5. reference vs address with a literal ----------
void printIntVal(int val)        { std::cout << "int by value: " << val << '\n'; }
void printIntRef(const int& ref) { std::cout << "int by ref:   " << ref << '\n'; }
void printIntAddr(const int* p)  { std::cout << "int by addr:  " << *p << '\n'; }

int main()
{
    // 1. three ways
    std::string str { "Hello, world!" };
    printByValue(str);
    printByReference(str);
    printByAddress(&str);           // & gives the address of str

    std::string* sp { &str };       // already have a pointer? pass it directly
    printByAddress(sp);

    // 2. the pointer is passed by value (copied)
    int n { 5 };
    int* np { &n };
    std::cout << "np holds:         " << np << '\n';
    std::cout << "np's own addr:    " << &np << '\n';
    showPtr(np);

    // 3. modify through the pointer
    int x { 5 };
    std::cout << "x = " << x << '\n';    // 5
    changeValue(&x);
    std::cout << "x = " << x << '\n';    // 6

    // 4. null checks
    printSafe(&x);
    printSafe(nullptr);             // prints nothing, doesn't crash
    printEarly(&x);
    printEarly(nullptr);            // prints nothing, doesn't crash
    printAssert(&x);
    // printAssert(nullptr);        // debug build: program aborts on the assert

    // 5. literals: reference works, address doesn't
    printIntVal(5);
    printIntRef(5);
    // printIntAddr(&5);            // error: can't take address of an rvalue
    printIntAddr(&x);               // fine, x is an lvalue

    // ---------- 6. Experiments (uncomment ONE at a time) ----------
    // Paste the exact compiler error (or what happened) next to each one.

    // printIntAddr(&5);
    // Error I got:

    // Uncomment readOnly() above, then compile.
    // Error I got:

    // printAssert(nullptr);        // compiles, then aborts when run
    // What I saw:

    // int* crash {};
    // std::cout << *crash;         // null dereference, no check
    // What I saw:

    return 0;
}