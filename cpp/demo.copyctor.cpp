#include <iostream>

class A
{
    private:
        int value;
    public:
        A(int n) { value = n; }

        // bellow line caused compilation error
        A(A other) { value = other.value; }

        void Print() { std::cout << value << std::endl; }
};



int main()
{
    A a = 10;
    A b = a;
    b.Print();
}

