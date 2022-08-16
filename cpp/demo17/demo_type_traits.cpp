// demonstration of type traits
#include <type_traits>


class A {};

enum E : int {};

char c;
unsigned short us;
int i;
long l;
float f;
double d;

template<typename T>
T check_int(T t)
{
    // With C++11, check the type of T.
    static_assert(std::is_integral<T>::value, "integer type is required");

    // With C++17 you can check it with helper variable templates.
    static_assert(std::is_integral_v<T>, "another helper variable to check integer type");
    return t;
}

template<typename T>
void assert_not_integer(T t)
{
    static_assert(!std::is_integral<T>::value, "should not be an integer");
}

template<typename T>
T check_enum(T t)
{
    static_assert(std::is_enum<T>::value, "enum type is required");
    return t;
}

int main()
{
    check_int(c);
    check_int(i);
    check_int(l);

    check_enum(E());

    assert_not_integer(A());
    assert_not_integer(f);
    assert_not_integer(d);
}
