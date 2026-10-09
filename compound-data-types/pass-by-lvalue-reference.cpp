// 12.5 - Pass by lvalue reference
//
// NOTES:
// - Pass by value copies the argument into the parameter. Cheap for int,
//   expensive for class types like std::string.
// - Pass by reference (T&) binds the parameter to the argument itself:
//   no copy, and the function can modify the original.
// - A non-const reference parameter only accepts modifiable lvalues
//   (not const variables, not literals). Fix comes in 12.6 (const T&).
//
// RULE OF THUMB:
// - Big object, just reading it   -> avoid the copy (reference)
// - Need to modify the original   -> non-const reference
// - Small type (int, double)      -> pass by value is fine

#include <iostream>
#include <string>

// ---------- 1. Copy vs no copy ----------
void printByValue(std::string y)    // y is a COPY of the argument (expensive)
{
    std::cout << y << '\n';
}

void printByRef(std::string& y)     // y is an alias of the argument (no copy)
{
    std::cout << y << '\n';
}

// ---------- 2. Proof: compare addresses ----------
void printAddresses(int val, int& ref)
{
    std::cout << "address of value parameter:     " << &val << '\n'; // different
    std::cout << "address of reference parameter: " << &ref << '\n'; // same as x
}

// ---------- 3. Modifying the argument ----------
void addOneByValue(int y) { ++y; }   // changes only the copy
void addOneByRef(int& y)  { ++y; }   // changes the real argument

// Used only for the experiments below
void printInt(int& y) { std::cout << y << '\n'; }

int main()
{
    // 1. Copy vs no copy
    std::string s { "Hello, world!" };
    printByValue(s);
    printByRef(s);

    // 2. Addresses
    int x { 5 };
    std::cout << "address of x:                   " << &x << '\n';
    printAddresses(x, x);

    // 3. Modifying the argument
    std::cout << "x = " << x << '\n';          // 5
    addOneByValue(x);
    std::cout << "after by value: " << x << '\n'; // 5 (unchanged)
    addOneByRef(x);
    std::cout << "after by ref:   " << x << '\n'; // 6 (changed)

    // ---------- 4. Experiments (uncomment ONE at a time) ----------
    // Paste the exact compiler error next to each, then comment it out again.

    // const int z { 5 };
    // printInt(z);    // const variable -> non-const reference
    // Error I got:

    // printInt(5);    // literal (rvalue) -> non-const reference
    // Error I got:

    return 0;
}