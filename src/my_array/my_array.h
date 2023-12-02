#ifndef CPP_MY_CONTAINERS_MY_ARRAY_MY_ARRAY_H_
#define CPP_MY_CONTAINERS_MY_ARRAY_MY_ARRAY_H_
#include <initializer_list>

namespace my {

template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  array() {}
  array(std::initializer_list<value_type> const &items);
  array(const array &a) { std::copy(a.array_, a.array_ + N, array_); }
  array(array &&a) { std::swap(array_, a.array_); }
  ~array() {}

  array &operator=(const array &a);
  array &operator=(array &&a);
  reference at(size_type pos);
  reference operator[](size_t pos) { return array_[pos]; }
  const_reference front() const { return array_[0]; }
  const_reference back() const { return array_[N - 1]; }
  iterator data() { return array_; }
  iterator begin() { return array_; }
  iterator end() { return &array_[N]; }
  bool empty() const { return N == 0; }
  size_t size() const { return N; }
  size_t max_size() const { return N; }
  void swap(array &other) { std::swap(array_, other.array_); }
  void fill(const_reference value);

 private:
  value_type array_[N];
};

template <typename T, size_t N>
my::array<T, N> &my::array<T, N>::operator=(array &&a) {
  std::swap(array_, a.array_);
  return *this;
}

template <typename T, size_t N>
my::array<T, N> &my::array<T, N>::operator=(const array &a) {
  std::copy(a.array_, a.array_ + N, array_);
  return *this;
}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  size_type j = -1;
  if (N < items.size()) {
    throw std::invalid_argument("Too many arguments");
  }
  for (auto i : items) array_[++j] = i;
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::invalid_argument("Out of range");
  }
  return array_[pos];
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    array_[i] = value;
  }
}

}  // namespace my

#endif  // CPP_MY_CONTAINERS_MY_ARRAY_MY_ARRAY_H_