#include <iostream>

class A
{

};

void printAddress(const A & a)
{
    printf("printAddress: %p\n", (void*)&a);

    auto addr = std::addressof(a);
    std::cout << "addr: " << addr << std::endl;
}

int main()
{
    const A a;
    printf("address: %p\n", (void*)&a);
    auto addr = std::addressof(a);
    std::cout << "addr: " << addr << std::endl;

    printAddress(a);
}

