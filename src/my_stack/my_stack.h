#ifndef CPP_MY_CONTAINERS_MY_STACK_MY_STACK_H_
#define CPP_MY_CONTAINERS_MY_STACK_MY_STACK_H_
#include <initializer_list>

namespace my {

template <typename T>
class stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack &operator=(const stack &s);
  const_reference top();
  bool empty();
  size_type size();
  void push(const_reference value);
  void pop();
  void swap(stack &other);
  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  int amount;
  T *steck;
};

template <typename T>
stack<T>::stack() {
  amount = 0;
  steck = new T[0];
}

template <typename T>
stack<T>::~stack() {
  delete[] steck;
}

template <typename T>
stack<T>::stack(const stack &s) {
  amount = s.amount;
  steck = new T[amount];
  for (int i = 0; i < amount; i++) {
    steck[i] = s.steck[i];
  }
}

template <typename T>
stack<T>::stack(stack &&s) {
  amount = 0;
  steck = new T[0];
  std::swap(*this, s);
}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items) {
  size_t j = 0;
  amount = 0;
  steck = new T[0];
  for (auto i : items) {
    push(i);
    ++j;
  }
  amount = j;
}

template <typename T>
my::stack<T> &stack<T>::operator=(const stack &s) {
  amount = s.amount;
  for (int i = 0; i < amount; i++) {
    steck[i] = s.steck[i];
  }
  return *this;
}

template <typename T>
void stack<T>::push(const_reference value) {
  T *tmp = new T[amount];
  std::swap(tmp, steck);
  delete[] steck;
  steck = nullptr;
  steck = new T[amount + 1];
  for (int i = 0; i <= amount; i++) {
    steck[i] = tmp[i];
  }
  steck[amount] = value;
  delete[] tmp;
  tmp = nullptr;
  amount++;
}

template <typename T>
void stack<T>::pop() {
  T *tmp = new T[amount - 1];
  for (int i = 0; i < amount - 1; i++) {
    tmp[i] = steck[i];
  }
  delete[] steck;
  steck = new T[amount - 1];
  amount--;
  for (int i = 0; i < amount; i++) {
    steck[i] = tmp[i];
  }
  delete[] tmp;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  return steck[amount - 1];
}

template <typename T>
bool stack<T>::empty() {
  if (amount == 0) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
void stack<T>::swap(stack &other) {
  std::swap(amount, other.amount);
  std::swap(steck, other.steck);
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
  return amount;
}

template <typename T>
template <typename... Args>
void my::stack<T>::emplace_front(Args &&...args) {
  (push(args), ...);
}

}  // namespace my
#endif  // CPP_MY_CONTAINERS_MY_STACK_MY_STACK_H_