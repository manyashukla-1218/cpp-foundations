
#include <iostream>
#include <cstddef>

// 12.11 - Pass by Address (Part 2)
// I am practicing optional arguments, pointer parameters,
// nullptr, and references to pointers.

// --------------------------------------------------
// 1. Pass by address with an optional argument
// --------------------------------------------------

void printIDNumber(const int* id = nullptr)
{
    // I check the pointer before using *id.
    if (id)
    {
        std::cout << "Your ID number is " << *id << '\n';
    }
    else
    {
        std::cout << "Your ID number is not known.\n";
    }
}

// --------------------------------------------------
// 2. Function overloading as an alternative
// --------------------------------------------------

void printUserID()
{
    std::cout << "ID is not known.\n";
}

void printUserID(int id)
{
    std::cout << "ID is " << id << '\n';
}

// --------------------------------------------------
// 3. Changing a local copy of a pointer
// --------------------------------------------------

void nullify(int* ptr2)
{
    // ptr2 is a copy of the pointer passed to this function.
    // Changing ptr2 does not change the original pointer.
    ptr2 = nullptr;
}

// --------------------------------------------------
// 4. Changing the original pointer using a reference
// --------------------------------------------------

void nullifyByReference(int*& refptr)
{
    // refptr refers to the original pointer.
    // So this changes the original pointer to nullptr.
    refptr = nullptr;
}

// --------------------------------------------------
// 5. Function overloading: int vs int*
// --------------------------------------------------

void printType(int value)
{
    std::cout << "printType(int): " << value << '\n';
}

void printType(int* ptr)
{
    std::cout << "printType(int*): ";

    if (ptr)
    {
        std::cout << "non-null\n";
    }
    else
    {
        std::cout << "null\n";
    }
}

// --------------------------------------------------
// 6. Practicing std::nullptr_t
// --------------------------------------------------

void printNullType(std::nullptr_t)
{
    std::cout << "printNullType(nullptr_t)\n";
}

void printNullType(int* ptr)
{
    std::cout << "printNullType(int*)\n";
}

// --------------------------------------------------
// Main function: testing each concept
// --------------------------------------------------

int main()
{
    // Example 1: Optional argument
    std::cout << "--- Optional argument ---\n";

    printIDNumber();

    int userID{ 34 };
    printIDNumber(&userID);

    // Output:
    // --- Optional argument ---
    // Your ID number is not known.
    // Your ID number is 34


    // Example 2: Function overloading
    std::cout << "\n--- Function overloading ---\n";

    printUserID();

    printUserID(34);
    printUserID(62);

    // Output:
    // --- Function overloading ---
    // ID is not known.
    // ID is 34
    // ID is 62


    // Example 3: Passing a pointer by value
    std::cout << "\n--- Pointer passed by value ---\n";

    int x{ 5 };
    int* ptr{ &x };

    std::cout << "Before nullify: ";
    std::cout << (ptr ? "non-null\n" : "null\n");

    nullify(ptr);

    std::cout << "After nullify: ";
    std::cout << (ptr ? "non-null\n" : "null\n");

    // Output:
    // --- Pointer passed by value ---
    // Before nullify: non-null
    // After nullify: non-null


    // Example 4: Passing a pointer by reference
    std::cout << "\n--- Pointer passed by reference ---\n";

    nullifyByReference(ptr);

    std::cout << "After nullifyByReference: ";
    std::cout << (ptr ? "non-null\n" : "null\n");

    // Output:
    // --- Pointer passed by reference ---
    // After nullifyByReference: null


    // Example 5: 0 vs nullptr
    std::cout << "\n--- int vs int* ---\n";

    int* anotherPtr{ &x };

    printType(0);           // 0 is an integer literal
    printType(nullptr);     // nullptr matches the pointer overload
    printType(anotherPtr);  // anotherPtr has type int*

    // Output:
    // --- int vs int* ---
    // printType(int): 0
    // printType(int*): null
    // printType(int*): non-null

    // Note:
    // Avoid using printType(NULL) here.
    // NULL can behave differently across implementations.
    // nullptr is the clear choice for a null pointer.


    // Example 6: std::nullptr_t
    std::cout << "\n--- std::nullptr_t ---\n";

    printNullType(nullptr);

    int* emptyPtr{ nullptr };
    printNullType(emptyPtr);

    // Output:
    // --- std::nullptr_t ---
    // printNullType(nullptr_t)
    // printNullType(int*)

    // Even though emptyPtr contains nullptr,
    // its type is still int*.


    // Example 7: Changing the original variable through a pointer
    std::cout << "\n--- Changing a variable through a pointer ---\n";

    int score{ 10 };
    int* scorePtr{ &score };

    std::cout << "Before: " << score << '\n';

    *scorePtr = 50;

    std::cout << "After: " << score << '\n';

    // Output:
    // --- Changing a variable through a pointer ---
    // Before: 10
    // After: 50

    // What I learned:
    // A pointer parameter receives a copy of an address.
    // Dereferencing that address can still modify the original variable.

    return 0;
}
