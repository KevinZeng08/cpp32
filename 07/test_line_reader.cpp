#include <iostream>
#include <iterator>
#include <sstream>
using namespace std;

// 定义输入迭代器
class istream_line_reader {
  // 1.迭代器定义为嵌套类
public:
  class iterator {
  public:
    typedef ptrdiff_t difference_type;
    typedef string value_type;
    typedef const value_type *pointer;
    typedef const value_type &reference;
    typedef input_iterator_tag iterator_category;

    // 2.++负责读取，*负责返回读取的内容
    iterator() noexcept : stream_(nullptr) {}
    explicit iterator(istream &is) : stream_(&is) { ++*this; }

    reference operator*() const noexcept { return line_; }

    pointer operator->() const noexcept { return &line_; }

    iterator &operator++() {
      getline(*stream_, line_);
      if (!*stream_) {
        stream_ = nullptr; // 读取到尾部，清空
      }
      return *this;
    }

    iterator operator++(int) {
      iterator temp(*this);
      ++*this;
      return temp;
    }

    bool operator==(iterator &rhs) const noexcept {
      return stream_ == rhs.stream_;
    }

    bool operator!=(iterator &rhs) const noexcept { return !operator==(rhs); }

  private:
    istream *stream_;
    string line_;
  };
  istream_line_reader() noexcept : stream_(nullptr) {}
  explicit istream_line_reader(istream &is) noexcept : stream_(&is) {}

  //构造函数只是把输入流的指针赋给stream_成员变量，begin函数负责构造一个真正有意义的迭代器
  iterator begin() { return iterator(*stream_); }

  iterator end() const noexcept { return iterator(); }

private:
  istream *stream_;
};

int main() {
  // 创建一个含有多行文本的字符串
  std::string testData = "Line 1\nLine 2\nLine 3";

  // 使用测试数据创建一个istringstream对象
  std::istringstream iss(testData);
  for (const string &line : istream_line_reader(iss)) {
    cout << line << endl;
  }
  // 等价于
  /*
  {
    auto&& r = istream_line_reader(is);
    auto it = r.begin();
    auto end = r.end();
    for (; it != end; ++it) {
        const string& line = *it;
        cout << line << endl;
    }
  }
  */
}