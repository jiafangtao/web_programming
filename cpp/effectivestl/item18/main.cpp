
#include <iostream>
#include <vector>

int main() {

    std::vector<bool> answers;
    answers.push_back(true);
    answers.push_back(true);
    answers.push_back(false);

    // This line won't compile. It will cause error like "error: no viable conversion from '__bit_iterator<std::__1::vector<bool, std::__1::allocator<bool> >, false>' to 'bool *'"
    //bool * b = &answers[0];
    //std::cout << "the answer is " << *b << std::endl;

    // But if you don't care too much about it's container or not,
    // you can still use an iterator libe below.
    auto it = &answers[0];
    std::cout << "the answer is " << *it << std::endl;

    for (auto && p : answers)
    {
        std::cout << "the answer is " << p << std::endl;
    }

    return 0;
}
