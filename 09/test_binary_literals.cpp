#include <bitset>    // std::bitset
#include <iostream>  // std::cout/endl

using namespace std;

int main()
{
    // 二进制字面量
    unsigned mask = 0b111000000;
    cout << bitset<9>(mask) << endl;
}
