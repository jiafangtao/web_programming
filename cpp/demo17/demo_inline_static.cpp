//
// Created by Bruce Jia on 2022/5/23.
//
#include <iostream>

using namespace std;

namespace cpp17 {

    inline static void f() {
        cout << "calling f" << endl;
    }

}

// command line to build this:
// $ clang demo_inline_static.cpp -lstdc++ -o a.out
int main() {
    cout << "calling main()" << endl;

    cpp17::f();

    //printf("calling main()\r\n");
}


// $ clang main.cpp -lstdc++ -std=c++11
