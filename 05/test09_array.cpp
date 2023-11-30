#include <array>               // std::array
#include <iostream>            // std::cout/endl
#include <map>                 // std::map
#include "output_container.h"  // operator<< for containers

typedef std::array<char, 8> mykey_t;
typedef std::array<int, 4> intkey_t;

int main()
{
    std::map<mykey_t, int> mp;
    mykey_t mykey{"hello"};
    mp[mykey] = 5;  // OK
    std::cout << mp << std::endl;

    std::map<intkey_t, int> mp2;
    intkey_t intkey{{1,2,3,4}};
    mp2[intkey] = 10;
    std::cout << mp2 << std::endl;
}
