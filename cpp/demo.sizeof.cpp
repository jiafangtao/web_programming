#include <iostream>


int getSize(int data [])
{
    return sizeof(data);
}

int main()
{
    int data [] = { 1, 2, 3, 4, 5 };
    int size1 = sizeof(data);

    int * data2 = data;
    int size2 = sizeof(data2);

    int size3 = getSize(data); // Compiler will generate a warning about getting size of array in function arguments

    std::cout << size1 << ' ' << size2 << ' ' << size3 << std::endl;

}
