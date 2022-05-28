#include <iostream>
#include <string>
#include <sstream>
#include "TestMMap.h"

// demo - copy constructor elision
class DumbClass {
public:
    DumbClass() : a('a'), b(0) {};
    DumbClass(const DumbClass & other) : a(other.a), b(other.b) {
        std::cout << "Copy Ctor of DumbClass is called" << std::endl;
    };

    std::string toString() {
        std::stringstream ss;
        ss << "a=" << a << ", b=" << b << std::endl;
        return ss.str();
    }

private:
    char a;
    int b;
};

// verify if copy ctor is omitted by compiler.
void should_invoke_copy_ctor(DumbClass d) {
    std::cout << d.toString() << std::endl;
}

// return value should be copied
DumbClass should_invoke_copy_ctor_on_return(const DumbClass & ref) {
    return ref;
}

void testMap() {
    demo::TestMMap test;
    test.testMap();

    test.testMMap();
}

int main() {

    testMap();

    DumbClass d;
    //should_invoke_copy_ctor(d);
    //should_invoke_copy_ctor_on_return(d);

    should_invoke_copy_ctor_on_return(DumbClass());

    return 0;
}

/*
class CopyOnly {
public:
    CopyOnly() {
    }
    CopyOnly(int) {
    }
    CopyOnly(const CopyOnly&) = default;
    CopyOnly(CopyOnly&&) = delete; // explicitly deleted
};

CopyOnly x = 42; // OK since C++17

CopyOnly y{42};

 */
