#include <iostream>
#include <memory>

struct Point {
    float x;
    float y;
};

using namespace std;

int main() {
    constexpr int i = 0;
    //i++;

    const int j = 0;
    //j++;

    shared_ptr<Point> p(new Point());

    // removed in C++17
    //auto_ptr<Point> p = null;

    // new features in C++20


    return 0;
}
