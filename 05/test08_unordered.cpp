#include <complex>             // std::complex
#include <iostream>            // std::cout/endl
#include <unordered_map>       // std::unordered_map
#include <unordered_set>       // std::unordered_set
#include "output_container.h"  // operator<< for containers

using namespace std;

// 可以计算哈希值的函数对象
template <typename T>
struct complex_hash {
    size_t operator()(const complex<T>& v) const noexcept {
        hash<T> h;
        return h(v.real()) + h(v.imag());
    }
};

int main() {
    unordered_map<complex<double>, double, complex_hash<double>> mp {
         {{2.0 ,2.1}, 3.5 }, { {3.0, 4.5}, 5.0 } };

    cout << mp << endl;
}


// template <typename T>
// struct complex_hash {
//     size_t operator()(const complex<T>& v) const noexcept
//     {
//         hash<T> h;
//         return h(v.real()) + h(v.imag());
//     }
// };

// int main()
// {
//     unordered_set<int> s{1, 1, 2, 3, 5, 8, 13, 21};
//     cout << s << endl;

//     unordered_map<complex<double>, double, complex_hash<double>> umc{
//         {{1.0, 1.0}, 1.4142}, {{3.0, 4.0}, 5.0}};
//     cout << umc << endl;
// }
