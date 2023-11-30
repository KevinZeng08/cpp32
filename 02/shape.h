#include <iostream>

class shape {
public:
    virtual ~shape() {}
};

class circle : public shape {
public:
    ~circle() {
        std::cout << "~circle()" << std::endl;
    }
};