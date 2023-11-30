#include <cstddef>
#include <stdexcept>

class matrix {
public:
  matrix(size_t nrows, size_t ncols) : nrows_(nrows), ncols_(ncols) {
    data_ = new float[nrows * ncols];
  }

  friend matrix operator*(const matrix &lhs, const matrix &rhs);

  ~matrix() { delete[] data_; }

private:
  float *data_;
  size_t nrows_;
  size_t ncols_;
};

matrix operator*(const matrix &lhs, const matrix &rhs) {
  // 抛出异常
  if (lhs.ncols_ != rhs.nrows_) {
    throw std::runtime_error("matrix size mismatch!");
  }
  matrix result(lhs.nrows_, rhs.ncols_);
  // 矩阵乘法计算
  return result;
}