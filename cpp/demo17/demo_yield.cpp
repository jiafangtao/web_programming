// demonstration of std::this_thread::yield
// by Bruce Jia <bruce.jia@live.com>

#include <chrono>
#include <iostream>
#include <thread>

class HighResStopwatch
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    HighResStopwatch() noexcept: start(std::chrono::high_resolution_clock::now()) {
    }

    ~HighResStopwatch() noexcept {
        
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
              << " microseconds\n";
    }

    HighResStopwatch(HighResStopwatch &) = delete;
    void operator = (HighResStopwatch &) = delete;
};

int main()
{
    long maxCount = 1000000L;
    int j = 1;

    for (long i=1; i<=maxCount; i++) {
        if (i % 10000 == 0) {
            std::cout << "yield " << j++ << std::endl;
            HighResStopwatch watch;
            std::this_thread::yield();
        }
    }    
}
