#ifndef CPP_MY_CONTAINERS_MY_VECTOR_MY_VECTOR_H_
#define CPP_MY_CONTAINERS_MY_VECTOR_MY_VECTOR_H_
#include <initializer_list>

namespace my {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();

  vector &operator=(vector &&v);
  reference at(size_type pos);
  const_reference front() const { return arr_[0]; };
  const_reference back() const { return arr_[size_ - 1]; };
  void push_back(const_reference v);
  void pop_back();
  void reserve(size_t size);
  void shrink_to_fit();
  void clear();
  void erase(iterator pos);
  void swap(vector &other);

  reference operator[](size_t pos);

  iterator begin() { return arr_; };
  iterator end() { return &arr_[size_]; };
  iterator data() const { return arr_; };
  iterator insert(iterator pos, const_reference value);

  size_type capacity() const { return capacity_; };
  size_type size() const { return size_; };
  size_type max_size() const { return SIZE_MAX / sizeof(value_type); };
  bool empty() const { return size() == 0U; };

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  size_t size_;
  size_t capacity_;
  T *arr_;

  void alloc_space(size_type n);
  void reserve_more_capacity(size_type n);
  bool full() const { return size() >= capacity(); }
};

template <typename T>
vector<T>::vector() : size_(0), capacity_(0) {
  alloc_space(0);
}

template <typename T>
vector<T>::vector(size_type n) {
  if (n == 0) throw std::invalid_argument("Size cannot be 0");
  alloc_space(n);
  size_ = 0;
  capacity_ = n;
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()), capacity_((items.size())) {
  alloc_space(items.size());
  size_type j = -1;
  for (auto i : items) arr_[++j] = i;
}

template <typename T>
vector<T>::vector(const vector &v) {
  alloc_space(v.capacity_);
  for (size_t i = 0; i < v.size(); i++) {
    arr_[i] = v.arr_[i];
  }
  size_ = v.size_;
  capacity_ = v.capacity_;
}

template <typename T>
vector<T>::vector(vector &&v) {
  std::swap(arr_, v.arr_);
  std::swap(size_, v.size_);
  std::swap(capacity_, v.capacity_);
}

template <typename T>
vector<T>::~vector() {
  size_ = 0;
  capacity_ = 0;
  delete (arr_);
}

template <typename T>
my::vector<T> &my::vector<T>::operator=(vector &&v) {
  std::swap(arr_, v.arr_);
  std::swap(size_, v.size_);
  std::swap(capacity_, v.capacity_);
  return *this;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(arr_, other.arr_);
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_t pos) {
  if (pos >= size_) throw std::invalid_argument("Out of range");
  return arr_[pos];
}

template <typename T>
void vector<T>::push_back(const_reference v) {
  if (full()) {
    reserve_more_capacity(size_ + 10);
  }
  arr_[size_] = v;
  ++size_;
}

template <typename T>
void vector<T>::pop_back() {
  if (empty()) {
    throw std::invalid_argument("Vector is empty");
  }
  --size_;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type i) {
  if (i >= size_) {
    throw std::invalid_argument("Index out of range");
  }
  return arr_[i];
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size < size_) {
    throw std::invalid_argument("Size is to low");
  }
  reserve_more_capacity(size);
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    T *temp = new T[size_];
    for (size_t i = 0; i < size_; i++) {
      temp[i] = arr_[i];
    }
    delete[] arr_;
    arr_ = temp;
    capacity_ = size_;
  }
}

template <typename T>
void vector<T>::clear() {
  for (size_t i = 0; i < size_; ++i) {
    arr_[i] = T{};
  }
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_t index = pos - arr_;
  if (index > size_) throw std::invalid_argument("Out of range");
  for (size_t i = index + 1; i < size_; ++i) arr_[i - 1] = arr_[i];
  --size_;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  T *temp = new T[capacity_ + 1];
  int counter = 0;
  int index = 0;
  for (size_t i = 0; i < size_; ++i) {
    if (&arr_[i] == pos) {
      temp[counter] = value;
      index = counter;
      counter++;
    }
    temp[counter] = arr_[i];
    ++counter;
  }
  capacity_ = capacity_ + 1;
  size_ = size_ + 1;
  delete[] arr_;
  arr_ = temp;
  return &arr_[index];
}

template <typename T>
template <typename... Args>
typename my::vector<T>::iterator my::vector<T>::emplace(const_iterator pos,
                                                          Args &&...args) {
  iterator adress = (iterator)pos;
  for (const auto temp : {args...}) {
    adress = insert(adress, temp);
  }
  return adress;
}

template <typename T>
template <typename... Args>
void my::vector<T>::emplace_back(Args &&...args) {
  for (const auto temp : {args...}) push_back(temp);
}

template <typename T>
void vector<T>::alloc_space(size_type n) {
  arr_ = new T[n];
}

template <typename T>
void vector<T>::reserve_more_capacity(size_type n) {
  if (n <= size_) {
    throw std::invalid_argument("Out of range");
  } else if (n <= capacity_) {
    n = capacity_;
  } else if (n > max_size()) {
    throw std::invalid_argument("Out of range(n > max size)");
  }
  T *temp = new T[n];
  for (size_t i = 0; i < size_; i++) {
    temp[i] = arr_[i];
  }
  delete[] arr_;
  arr_ = temp;
  capacity_ = n;
}

}  // namespace my

#endif  // CPP_MY_CONTAINERS_MY_VECTOR_MY_VECTOR_H_