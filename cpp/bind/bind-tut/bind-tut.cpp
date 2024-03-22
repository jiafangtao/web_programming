#include "bind-tut.h"
#include "pybind11/pybind11.h"


using namespace std;

/*
int main()
{
    cout << "Hello CMake." << endl;
    return 0;
}*/


int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function that adds two numbers");
}
