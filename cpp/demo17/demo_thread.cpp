// demo_thread.cpp

#include <iostream>
#include <thread>
#include <vector>


template<class Func>
std::vector<std::thread> start_threads(std::vector<Func> & fns)
{
    std::vector<std::thread> threads;
    for (Func fn : fns)
    {
        std::thread t(fn);
        threads.emplace_back(std::move(t));
        //threads.push_back(std::move(t));
    }

    std::cout << "All threads are started" << std::endl;
    //return std::move(threads);
    return threads; // move-ctor will be called.
}

void printChar(char c, int times)
{
    std::cout << std::endl << "[ printing in thread " << std::this_thread::get_id() << " ] ";
    while(times-- > 0)
    {
        printf("%c", c);
    };

    std::cout << std::endl;
}

int main()
{
    auto tid1 = std::this_thread::get_id();
    std::cout << "tid1 : " << tid1 << std::endl;

    auto tid2 = std::this_thread::get_id();
    std::cout << "tid2 : " << tid2 << std::endl;

    std::vector<std::function<void ()>> fns;
    
    fns.push_back(std::bind(printChar, 'a', 10));
    fns.push_back(std::bind(printChar, 'b', 20));
    fns.push_back(std::bind(printChar, 'c', 30));
    fns.push_back(std::bind(printChar, 'd', 40));
    
    
    std::vector<std::thread> threads = start_threads(fns);
    std::cout << "Join all threads in main thread " << std::this_thread::get_id() << std::endl;
    for (auto & t : threads)
    {
        if (t.joinable()) {
            std::cout << "__j__";
            t.join();
        } else {
            std::cout << "  x  ";
            t.detach();
        }
    }
    
    std::cout << std::endl << "We are all set in main thread " << std::this_thread::get_id() << std::endl;
}
