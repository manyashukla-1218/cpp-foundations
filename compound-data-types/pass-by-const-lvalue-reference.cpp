// 12.6 - Pass by const lvalue reference
//
// NOTES:
// - const T& is a reference that can bind to ALL of these:
//     modifiable lvalue (int x), const lvalue (const int z), rvalue (5)
// - Same benefit as T&: no copy is made.
// - Extra safety: the function can't modify the argument.
// - 12.5 problem: int& refused const variables and literals.
//   12.6 solution: const int& accepts them.
// - If the argument type differs from the reference type, a temporary is
//   created behind the scenes (hidden conversion, possibly a copy).
//
// RULE OF THUMB:
// - int, double, char, bool, enums -> pass by value (cheap to copy)
// - std::string and other class types -> pass by const reference
// - Only use plain T& when the function MUST change the argument
// - Not sure? Use const T&

#include <iostream>
#include <string>

// ---------- 1. const reference accepts everything ----------
void printRef(const int& y)
{
    std::cout << "printRef: " << y << '\n';
    // ++y;   // error: y is const, can't modify through it
}

// ---------- 2. value vs reference vs const reference ----------
void tryValue(int y) { ++y; }     // changes only the copy
void tryRef(int& y)  { ++y; }     // changes the real argument
// void tryConstRef(const int& y) { ++y; }   // error: won't compile

// ---------- 3. different type -> temporary object ----------
void printDoubleVal(double d)        { std::cout << "by value: " << d << '\n'; }
void printDoubleRef(const double& d) { std::cout << "by const ref: " << d << '\n'; }

// ---------- 4. mixing all three in one function ----------
void mixed(int a, int& b, const std::string& c)
{
    ++b;   // allowed: b is a non-const reference
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << '\n';
}

// ---------- 5. big objects: const reference avoids the copy ----------
void printString(const std::string& s)
{
    std::cout << s << '\n';
}

int main()
{
    // 1. All three kinds of arguments work
    int x { 5 };
    const int z { 10 };
    printRef(x);   // modifiable lvalue (also worked with int&)
    printRef(z);   // const lvalue (was an error with int&)
    printRef(7);   // rvalue literal (was an error with int&)

    // 2. Who modifies the original?
    int n { 5 };
    std::cout << "start: n = " << n << '\n';           // 5
    tryValue(n);
    std::cout << "after tryValue: " << n << '\n';      // 5 (copy changed)
    tryRef(n);
    std::cout << "after tryRef: " << n << '\n';        // 6 (original changed)

    // 3. Type mismatch: 5 is an int, but the parameter wants a double
    printDoubleVal(5);   // 5 -> temporary 5.0 -> copied into d
    printDoubleRef(5);   // 5 -> temporary 5.0 -> reference binds to it

    // 4. Mixing
    int score { 1 };
    const std::string msg { "Hello" };
    mixed(100, score, msg);
    std::cout << "score after mixed(): " << score << '\n';   // 2

    // 5. Strings
    std::string name { "Hello, world!" };
    printString(name);            // no copy, reference binds to name
    printString("Hello, world!"); // works, but builds a temporary std::string

    // ---------- 6. Experiments (uncomment ONE at a time) ----------
    // Paste the exact compiler error next to each line, then comment it out again.

    // printRef(7);  // go back to 12.5: change printRef to take int& and try
    // Error I got:

    // tryConstRef(n);  // uncomment tryConstRef above first, then compile
    // Error I got:

    return 0;
}