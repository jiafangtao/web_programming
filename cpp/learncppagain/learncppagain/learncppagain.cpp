#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void f_copysign();

int main()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    vector<int> v2;
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(6);


    v1.insert(v1.end(), v2.cbegin(), v2.cend());
    std::for_each(v1.cbegin(), v1.cend(), [](int i) { cout << i << endl; });
    
    std::cout << "Hello World!\n";

    std::cout << "calling f_copysign" << std::endl;
    f_copysign();
}

void f_copysign() {
    float pos_pi = 3.1415926535f;
    float neg_pi = -3.1415926535f;
    float pos_sign = 2.0000f;
    float neg_sign = -2.002f;

    float result;
    
    result = std::copysignf(pos_pi, pos_sign);
    std::cout << "result: " << result << std::endl;

    result = std::copysignf(pos_pi, neg_sign);
    std::cout << "result: " << result << std::endl;

    result = std::copysignf(neg_pi, pos_sign);
    std::cout << "result: " << result << std::endl;

    result = std::copysignf(neg_pi, neg_sign);
    std::cout << "result: " << result << std::endl;

}

