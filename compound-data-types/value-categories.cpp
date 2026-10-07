// 12.2 - Value categories (lvalues and rvalues)

#include <iostream>
#include <string>

int getint() { return 5; }

int main()
{
    // ---------- 1. Lvalue vs Rvalue ----------
    // Lvalue = identifiable object (has a name/address, lives beyond the expression)
    // Rvalue = temporary value (used immediately, then gone)
    int x { 5 };        // x = lvalue, 5 = rvalue
    int y { x + 1 };    // x + 1 = rvalue (temporary result)
    int z { getint() }; // getint() = rvalue (returned by value)

    // const lvalue = non-modifiable lvalue
    const double d { 1.2 }; // d = non-modifiable lvalue, 1.2 = rvalue

    // ---------- 2. Assignment rule ----------
    // Left side: modifiable lvalue | Right side: rvalue
    x = 10;     // valid
    // 5 = x;   // error: 5 is an rvalue, you can't store anything in it

    // ---------- 3. Lvalue-to-rvalue conversion ----------
    // An lvalue can be used wherever an rvalue is expected (its value gets read)
    x = y;      // y (lvalue) -> its value (rvalue) -> assigned to x
    x = x + 1;  // left x = lvalue, right x = converted to an rvalue
    // The reverse is not allowed: an rvalue never becomes an lvalue

    // ---------- 4. Prefix vs Postfix ----------
    int a { 5 };
    ++a;        // ++a = lvalue (returns a itself)
    a++;        // a++ = rvalue (returns a temporary copy of the old value)

    // ---------- 5. Exception ----------
    // A C-style string literal like "Hello" is an lvalue
    // Other literals (5, 1.2, 'c') are rvalues

    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';
    std::cout << "z = " << z << '\n';
    std::cout << "d = " << d << '\n';
    std::cout << "a = " << a << '\n'; // 7 (both ++a and a++ incremented it)

    return 0;
}