#include <iostream>

class A
{
    private:
        int n;
    public:
        A(int v=0) : n(v) {}
        void set(int newValue) { n = newValue; }

        void dump() const
        {
            std::cout << "n=" << n << std::endl;
        }
};


int main()
{
    A a;
    a.set(100);
    a.dump();

    const A a2 = a;
    const_cast<A &>(a2).set(200);
    a2.dump();

}

