// AWOV - abstract without virtual functions
#include <iostream>


class AWOV
{
public:
    virtual ~AWOV() = 0;    
};

// the definition is required even it's a pure virtual dtor.
AWOV::~AWOV() {}

class D1 : public AWOV
{
public:
    virtual ~D1()
    {
        std::cout << "D1 dtor is called" << std::endl;
    }
};

int main() 
{
    D1 d1;
    D1 * pd1 = new D1();
    delete pd1;

    return 0;
}
