// 12.3 - Lvalue references
//
// NOTES:
// - A reference is an alias (another name) for an existing object.
// - int& means "lvalue reference to an int". Here & does NOT mean "address of".
// - A reference is essentially identical to the object it refers to.
// - Rules: must be initialized, can't be reseated, non-const refs only bind
//   to modifiable lvalues, and the types must match.

#include <iostream>

void quiz()
{
    // Quiz from the lesson. Predicted output: 11, 22, 44
    int x { 1 };
    int& ref { x };
    std::cout << x << ref << '\n';   // 11

    int y { 2 };
    ref = y;                         // same as x = y, so x becomes 2
    y = 3;                           // only y changes, ref is still tied to x
    std::cout << x << ref << '\n';   // 22

    x = 4;
    std::cout << x << ref << '\n';   // 44
}

int main()
{
    // ---------- 1. Creating a reference ----------
    int x { 5 };
    int& ref { x };                  // ref is an alias for x
    std::cout << x << ' ' << ref << '\n';   // 5 5

    // ---------- 2. Modifying through a reference ----------
    ref = 7;                         // changes x itself
    std::cout << x << ' ' << ref << '\n';   // 7 7

    // ---------- 3. References can't be reseated ----------
    int y { 6 };
    ref = y;                         // NOT "ref now refers to y", this is x = y
    y = 100;                         // does not affect ref or x
    std::cout << x << ' ' << ref << ' ' << y << '\n';   // 6 6 100

    // ---------- 4. Scope: reference and referent live independently ----------
    {
        int& ref2 { x };
        std::cout << ref2 << '\n';   // 6
    }                                // ref2 dies here, x is unaffected
    std::cout << x << '\n';          // 6

    // ---------- 5. Dangling reference (just a note for now) ----------
    // If the referenced object dies before the reference, the reference
    // dangles and using it is undefined behavior. Real example in 12.12.

    // ---------- 6. References are not objects ----------
    // The compiler may optimize them away. No reference to a reference exists.
     // ---------- 7. Experiments (uncomment ONE at a time) ----------
    // Paste the exact compiler error next to each line, then comment it out again.

    // int& r1;            // references must be initialized
    // Error I got:

    // const int c { 5 };
    // int& r2 { c };      // c is a non-modifiable lvalue
    // Error I got:

    // int& r3 { 5 };      // 5 is an rvalue
    // Error I got:

    // double d { 6.0 };
    // int& r4 { d };      // type mismatch
    // Error I got:

    // double& r5 { x };   // converted value is an rvalue
    // Error I got:

    quiz();

    return 0;
}