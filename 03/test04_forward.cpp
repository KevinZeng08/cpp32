#include <utility>  // std::forward
#include <stdio.h>  // puts

class shape {
public:
    virtual ~shape() {}
};

class circle : public shape {
public:
    circle() {}
    ~circle() {}
};

void foo(const shape&)
{
    puts("foo(const shape&)");
}

void foo(shape&&)
{
    puts("foo(shape&&)");
}

// 当T是模板参数时, T&& 是万能引用，保持值类别 (左值 右值) 并进行转发
template <typename T>
void bar(T&& s)
{
    foo(std::forward<T>(s));
}

int main()
{
    circle temp;
    bar(temp);
    bar(circle()); // 保持值类别为右值
}
