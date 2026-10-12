// 12.8 - Null pointers
//
// My notes:
// - A null pointer is a pointer holding "nothing" instead of an address.
// - Make one with {} or nullptr. Never leave a pointer uninitialized.
// - Dereferencing a null (or dangling / wild) pointer = undefined behavior,
//   usually a crash. It's the #1 reason C++ programs crash.
// - if (ptr) works because a pointer converts to bool: null -> false.
// - That check can only tell null from non-null. It cannot detect a dangling
//   pointer, so: a pointer must hold a valid address OR be nullptr.
// - When an object dies, pointers to it do NOT become null automatically.
//   I have to set them to nullptr myself.
// - Prefer references over pointers unless I really need null or reseating.

#include <iostream>
#include <cstddef>   // for NULL (old-style, only here to recognise it)

// A function that takes a pointer must be ready for it to be null
void showValue(int* p)
{
    if (p)
        std::cout << "value = " << *p << '\n';
    else
        std::cout << "got a null pointer, nothing to print\n";
}

int main()
{
    std::cout << std::boolalpha;

    // ---------- 1. a null pointer can be pointed at something later ----------
    int* ptr {};          // null pointer
    int x { 5 };
    ptr = &x;             // now it points at x
    std::cout << *ptr << '\n';                 // 5

    // ---------- 2. nullptr keyword ----------
    int* a { nullptr };   // initialize with nullptr
    int value { 5 };
    int* b { &value };
    b = nullptr;          // b is empty again, value is untouched
    showValue(nullptr);   // pass null to a function
    showValue(&value);    // pass a real address
    (void)a;              // silence "unused variable" warning

    // ---------- 3. checking for null: two ways ----------
    int* nullPtr {};

    if (ptr == nullptr)                        // explicit
        std::cout << "ptr is null\n";
    else
        std::cout << "ptr is non-null\n";      // this prints

    std::cout << "nullPtr is " << (nullPtr == nullptr ? "null\n" : "non-null\n");

    // short way: pointer converts to bool (null -> false)
    if (ptr)
        std::cout << "ptr is non-null\n";      // this prints
    std::cout << "nullPtr is " << (nullPtr ? "non-null\n" : "null\n");

    // ---------- 4. avoiding a dangling pointer ----------
    int* dp {};
    {
        int y { 10 };
        dp = &y;
        std::cout << *dp << '\n';              // 10
    }                                          // y is destroyed here
    dp = nullptr;                              // reset it, don't leave it dangling

    if (dp)
        std::cout << *dp << '\n';
    else
        std::cout << "dp is null, so we skip dereferencing\n";

    // ---------- 5. old-style null literals (don't write these, just know them) ----------
    float* old1 { 0 };        // literal 0 in a pointer context means null
    double* old2 { NULL };    // macro from C
    std::cout << "old1 is null: " << (old1 == nullptr) << '\n';   // true
    std::cout << "old2 is null: " << (old2 == nullptr) << '\n';   // true

    // ---------- 6. Experiments (uncomment ONE at a time) ----------
    // This one compiles fine but crashes when run. Note what happens
    // (crash? no output? error code?) next to "What I saw".

    // int* crash {};
    // std::cout << *crash << '\n';
    // What I saw:

    // This one also compiles. Why is it dangerous? (hint: the if passes)
    // int* d2 {};
    // { int z { 1 }; d2 = &z; }
    // if (d2) std::cout << *d2 << '\n';
    // What I saw:

    // ---------- 7. Quiz (I tried first, then checked) ----------
    // Q1a. Can we tell if a pointer is null? How?
    //      A: Yes, ptr == nullptr, or if (ptr).
    // Q1b. Can we tell if a non-null pointer is valid or dangling?
    //      A: No. That's why invalid pointers should be set to nullptr.
    //
    // Q2. Predictable, undefined, or possibly undefined?
    // 2a. Assigning an object's address to a non-const pointer -> predictable
    // 2b. Assigning nullptr to a pointer                       -> predictable
    // 2c. Dereferencing a pointer to a valid object            -> predictable
    // 2d. Dereferencing a dangling pointer                     -> undefined
    // 2e. Dereferencing a null pointer                         -> undefined
    // 2f. Dereferencing a non-null pointer                     -> possibly undefined
    //     (fine if it's valid, undefined if it's dangling)
    //
    // Q3. Why set pointers that aren't pointing at a valid object to nullptr?
    //     A: So a simple null check is enough to know the pointer is safe to use.

    return 0;
}