class A {
public:
    virtual void foo();
    virtual void bar();
    void foobar();
};

class B : public A {
    void foo() override;
    void bar() override final;
    // void foobar() override; // Error
};

class C final : public B {
    void foo() override;
    // void bar() override; // Error: final函数不可以override
};

// class D : public C { // Error: final类不可以被继承
// };