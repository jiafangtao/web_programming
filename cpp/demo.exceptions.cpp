#include <iostream>
#include <string>

class MyException
{
    private:
        std::string message;

    public:
        MyException() 
        {
            message = "my exception for demo";
            std::cout << "ctor of my exception" << std::endl; 
        }
        
        MyException(const MyException & rhs) : message(rhs.message) 
        { 
            std::cout << "copy ctor of my exception" << std::endl; 
        }

        std::string what() { return message; }
};

void foo () {
    try
    {
        int i = 0;
        int j = ++i;

        if (i <= j)
        {
            throw MyException();
        }
    }
    catch (MyException & e) {
        std::cerr << "Got exception " << e.what() << std::endl;
    }
}


void bar () {
    try
    {
        int i = 0;
        int j = ++i;

        if (i <= j)
        {
            throw MyException();
        }
    }
    catch (MyException e) { // catch the exception by value. this will cause copy ctor.
        std::cerr << "Got exception " << e.what() << std::endl;
    }
}



int main() {
    foo();

    std::cout << "================================" << std::endl;
    bar();
}

