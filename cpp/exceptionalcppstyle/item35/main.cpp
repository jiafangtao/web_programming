#include <iostream>

template<class T, void (T::*F)() >
class callback1 {
public:
    callback1(T & t) : object(t) {}
    void execute() { (object.*F)(); }

private:
    T& object;
};

class Widget {
public:
    void showUp() {
        std::cout << "A widget is showing up" << std::endl;
    }
};

typedef void (Widget::*WidgetMemberFn)();

int main() {
    Widget w;

    // first using normal member fucntion pointers
    WidgetMemberFn func = &Widget::showUp;
    (w.*func)();

    callback1<Widget, &Widget::showUp> c(w);
    c.execute();

    return 0;
}
