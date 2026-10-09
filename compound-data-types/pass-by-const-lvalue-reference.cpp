// 12.6 - Pass by const lvalue reference
//
// ============================== NOTES ==============================
// 1. const T& can bind to ALL of these:
//      modifiable lvalue (int x), const lvalue (const int z), rvalue (5)
//    So a const reference parameter accepts any kind of argument.
// 2. Same benefit as T& (no copy), plus a guarantee: the function can't
//    modify the argument.
// 3. Why const refs may bind to rvalues: otherwise there would be no way
//    to pass literals to functions that take references.
// 4. If the argument type differs from the reference type, the compiler
//    converts it into a TEMPORARY object and binds the reference to that.
//    With references we wanted to avoid copies, so a conversion can quietly
//    bring a (possibly expensive) copy back. Keep the types matching.
// 5. Every parameter chooses by-value / by-ref / by-const-ref on its own.
//
// BEST PRACTICE:
// - Prefer const T& over T& unless the function must change the argument.
// - Fundamental + enum types: pass by value (cheap to copy).
// - Class types: pass by const reference.
// - Not sure? Use const T&.
//
// OFTEN PASSED BY VALUE (cheap):
//   enums, std::string_view, std::span, iterators, std::reference_wrapper,
//   cheap value-semantics types (std::pair of fundamentals, std::optional,
//   std::expected)
// PASSED BY REFERENCE:
//   args the function must modify; non-copyable types (std::ostream);
//   types where copying has ownership implications (unique_ptr, shared_ptr);
//   types with virtual functions / likely base classes (object slicing, 25.9)
//
// --- COST OF PASS BY VALUE vs PASS BY REFERENCE (advanced) ---
// Cost of a copy depends on: (a) object size, (b) setup cost (opening a
// file, allocating memory...). Binding a reference is always cheap.
// Cost of USING the parameter: a value parameter = 1 access (register/RAM).
// A reference parameter = 1 access to find the referent + 1 more to reach
// the object. Also, pass by value has no aliasing, so the optimizer can be
// more aggressive.
// => cheap objects: value is as cheap to pass and faster to use.
// => expensive objects: the copy cost dominates, so use a reference.
// "Cheap to copy" rule of thumb: sizeof(T) <= 2 * sizeof(void*)
// (2 words or less) AND no setup cost. Assume std library classes have
// setup costs unless known otherwise.
//
// --- string_view vs const std::string& (strings as parameters) ---
// Prefer std::string_view (by value) in most cases. Use const std::string&
// only if: you're on C++14 or older, OR your function calls other functions
// that need a std::string or a null-terminated C-style string.
// ===================================================================

#include <iostream>
#include <string>
#include <string_view>

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

// ---------- 5. is a type cheap to copy? ----------
// Function-like macro so it works with a type OR an object
// (normal functions can't take a type as a parameter).
#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))

struct S
{
    double a;
    double b;
    double c;
};

// ---------- 6. string_view vs const std::string& ----------
void printSV(std::string_view sv) { std::cout << "SV: " << sv << '\n'; }
void printS(const std::string& s) { std::cout << "S:  " << s << '\n'; }

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

    // 5. Cheap to copy?
    std::cout << std::boolalpha;           // print true/false instead of 1/0
    double d {};
    std::cout << "int is small:    " << isSmall(int) << '\n';   // true
    std::cout << "double is small: " << isSmall(d) << '\n';     // true
    std::cout << "S is small:      " << isSmall(S) << '\n';     // false (24 bytes)

    // 6. string_view vs const std::string&
    std::string str { "Hello, world" };
    std::string_view sv { str };

    // string_view parameter: all three are cheap
    printSV(str);              // cheap conversion string -> string_view
    printSV(sv);               // cheap copy of a string_view
    printSV("Hello, world");   // cheap conversion of a string literal

    // const std::string& parameter
    printS(str);               // cheap: reference binds to the string
    printS(static_cast<std::string>(sv));  // bad: expensive temporary string
    printS("Hello, world");    // bad: expensive temporary std::string

    // ---------- 7. Experiments (uncomment ONE at a time) ----------
    // Paste the exact compiler error next to each line, then comment it out again.

    // printS(sv);   // string_view -> const std::string& (no implicit conversion)
    // Error I got:

    // 12.5 comparison: change printRef's parameter to int& and try printRef(z)
    // and printRef(7) again.
    // Error I got:

    // Uncomment tryConstRef above and compile.
    // Error I got:

    return 0;
}