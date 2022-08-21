// reference-qualified

#include <iostream>
#include <vector>


class Widget
{
using DataType = std::vector<int>;

private:
    DataType _data;

public:
    DataType & doSomething() &
    {
        std::cout << "calling first" << std::endl;
        return this->_data;
    }

    DataType && doSomething() &&
    {
        std::cout << "calling second with rvalue-ref" << std::endl;
        return std::move(this->_data);
    }

    int constq() const
    {
        return 1;
    }

    int constq()
    {
        return 0;
    }
};

Widget createWidget()
{
    return Widget();
}

int main()
{
    Widget w;
    w.doSomething();

    std::cout << "w.constq(): " << w.constq() << std::endl;

    const Widget & cr = w;
    std::cout << "cr.constq(): " << cr.constq() << std::endl;


    createWidget().doSomething();

    // temp object is taken as non-const
    std::cout << "temp object.constq(): " << createWidget().constq() << std::endl;
}
