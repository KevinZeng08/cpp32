#include "shape.h"
#include <iostream>

class shared_count {
public:
  shared_count() : count_(1) {}
  void add_count() { ++count_; }
  long reduce_count() { return --count_; }
  long get_count() const { return count_; }

private:
  long count_;
};

template <typename T> class smart_ptr {
public:
  template <typename U> friend class smart_ptr;

  explicit smart_ptr(T *ptr = nullptr) : ptr_(ptr) {
    if (ptr) {
      shared_count_ = new shared_count();
    }
  }

  ~smart_ptr() {
    std::cout << "destructor" << std::endl;
    if (ptr_ && shared_count_->reduce_count() == 0) {
      delete ptr_;
      delete shared_count_;
      std::cout << "delete ptr and shared_count" << std::endl;
    }
  }

  // copy constructor
  smart_ptr(const smart_ptr &other) {
    std::cout << "copy constructor" << std::endl;
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_->add_count();
      shared_count_ = other.shared_count_;
    }
  }
  // for polymorphism: 子类指针向基类指针转换
  template <typename U> smart_ptr(const smart_ptr<U> &other) {
    std::cout << "copy constructor for derived class" << std::endl;
    ptr_ = other.ptr_;
    if (ptr_) {
      other.shared_count_->add_count();
      this->shared_count_ = other.shared_count_;
    }
  }

  // move constructor
  template <typename U> smart_ptr(smart_ptr<U> &&other) {
    std::cout << "move constructor" << std::endl;
    ptr_ = other.ptr_;
    if (ptr_) {
      shared_count_ = other.shared_count_;
      other.ptr_ = nullptr;
    }
  }
  // 强异常安全性, 赋值分为 拷贝 和 交换 两个步骤，异常只可能在拷贝阶段出现
  // 若出现异常，this对象完全不受任何影响
  smart_ptr &operator=(smart_ptr rhs) {
    std::cout << "operator=" << std::endl;
    rhs.swap(*this);
    return *this;
  }

  T &operator*() const { return *ptr_; }
  T *operator->() const { return ptr_; }
  operator bool() const { return ptr_; }

  long use_count() const {
    if (ptr_) {
      return shared_count_->get_count();
    } else {
      return 0;
    }
  }

  void swap(smart_ptr &rhs) {
    using std::swap;
    swap(ptr_, rhs.ptr_);
    swap(shared_count_, rhs.shared_count_);
  }

private:
  T *ptr_;
  shared_count *shared_count_;
};

// 全局swap函数
template <typename T> void swap(smart_ptr<T> &lhs, smart_ptr<T> &rhs) noexcept {
  lhs.swap(rhs);
}

int main() {
  smart_ptr<circle> ptr1(new circle());
  printf("use count of ptr1 is %ld\n", ptr1.use_count());
  smart_ptr<shape> ptr2;
  ptr2 = std::move(ptr1);
  printf("use count of ptr2 is %ld\n", ptr2.use_count());
  smart_ptr<shape> ptr3;
  ptr3 = ptr2;
  printf("use count of ptr3 is %ld\n", ptr3.use_count());
  // printf("use count of ptr1 is %ld\n", ptr1.use_count());
  // smart_ptr<shape> ptr2;
  // printf("use count of ptr2 was %ld\n", ptr2.use_count());
  // ptr2 = ptr1;
  // printf("use count of ptr2 is now %ld\n", ptr2.use_count());
  // if (ptr1) {
  //   puts("ptr1 is not empty");
  // }
  return 0;
}
