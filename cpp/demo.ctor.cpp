#include <iostream>

class A
{
    private:
        int n1;
        int n2;

    public:
        A() : n2(100), n1(n2+100) {}
        void Print() const
        {
            std::cout << n1 << " " << n2 << std::endl;
        }
};


int main()
{
    A a;
    a.Print();
}

