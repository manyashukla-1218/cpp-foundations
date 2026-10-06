#include <iostream>

void doSomething(int x, double y)
{
}

int main()
{
    int numerator {1};
    int denominator {2};

    std::cout << "Fraction: "
              << numerator << '/' << denominator << '\n';

    doSomething(numerator, 2.5);

    return 0;
}