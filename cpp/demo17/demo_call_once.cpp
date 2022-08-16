// build it with: c++ -std=c++17 demo_call_once.cpp

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>


using namespace std::chrono_literals; // requires c++14 or above

int counter = 0;


void increaseCounter()
{
    std::cout << "counter is increased to " << ++counter << std::endl;
}

void decreaseCounter()
{
    std::cout << "counter is decreased to " << --counter << std::endl;
}

void showCounter()
{
    std::cout << "couter is " << counter << std::endl;
}

std::once_flag flag;


void demo1()
{
    // in same thread, when flag is shared, the function is called only once.
    std::call_once(flag, increaseCounter);
    std::call_once(flag, increaseCounter);
    std::call_once(flag, increaseCounter);
}

void demo_one_flag_for_multi_callees()
{
    // flag is shared for multi calls of call_once
    // but only one returning call can be invoked.
    std::call_once(flag, decreaseCounter);
    std::call_once(flag, increaseCounter);
    std::call_once(flag, showCounter);
}


std::once_flag flag1, flag2, flag3;

/**
 * Only block 1 will invoke calls to the callee. 
 */
void demo3()
{    
    // block 1
    {
        std::call_once(flag1, increaseCounter);
        std::call_once(flag2, increaseCounter);
        std::call_once(flag3, increaseCounter);        
    }

    // block 2
    {
        std::call_once(flag1, increaseCounter);
        std::call_once(flag2, increaseCounter);
        std::call_once(flag3, increaseCounter);        
    }
}

std::once_flag flag_for_exc;

void demo_exceptions_simple()
{
    std::call_once(flag_for_exc, [](){ throw "failed to say hello"; });
}

template<int N>
struct FailForTimes
{
    int n;

    FailForTimes() : n(N) {}

    void operator()()
    {
        if (n > 0)
        {
            throw n--;
        }
    }

    int get() const
    {
        return n;
    }
};


void demo_exceptions_complex()
{
    FailForTimes<3> ff3t;
    while(true)
    {
        try
        {
            std::call_once(flag_for_exc, ff3t);
            std::cout << "Result: " << ff3t.get() << std::endl;

            // When we reach here, we've at least invoked the callee once.
            // This is a good solutioon for "hard" initialization ...
            break;
        }
        catch(int n)
        {
            std::cerr << "Caught exception of int - " << n << std::endl;
        }
    }
}


std::once_flag flag_for_multi_threads;

void demo_threads()
{
    for (int idx=0; idx<10; idx++) {
        std::thread t(
            [=](int i) {
                std::this_thread::sleep_for(3000ms);
                std::call_once(flag_for_multi_threads, [=]() {
                    std::cout << "thread " << idx;
                    std::cout << "(" << std::this_thread::get_id() << ")";                    
                });
        },
        idx);

        //t.detach();
    }
}

std::once_flag flag_for_call_with_args;

template<typename Arg>
void variadic_print(Arg arg) {
    std::cout << arg;
}

template<typename T, typename ...Args>
void variadic_print(T first_arg, Args...args) {
    std::cout << first_arg << " ";
    variadic_print(args...);
}

template<typename ... Args>
void demo_call_with_args(Args&& ... args)
{
    std::call_once(flag_for_call_with_args, [](auto&& ... args) {
        std::cout << "calling with arguments: ";
        variadic_print(args...);
        std::cout << std::endl;
    }, args...);
}


int main()
{
    //demo_one_flag_for_multi_callees();

    //demo_exceptions_simple();

    //demo_exceptions_complex();

    //demo_threads();

    demo_call_with_args("love", "C++", "or hate it", 2022);

    std::this_thread::sleep_for(3000ms);
}
