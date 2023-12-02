#ifndef CPP_MY_CONTAINERS_MY_QUEUE_MY_QUEUE_H_
#define CPP_MY_CONTAINERS_MY_QUEUE_MY_QUEUE_H_
#include <initializer_list>

namespace my {

template <typename T>
struct D_Node {
  using value_type = T;
  value_type data;
  struct D_Node *next = nullptr;
};

template <typename T>
class queue {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = D_Node<T>;

 public:
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &&q);
  const_reference front() const;
  const_reference back() const;
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(queue &other);
  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  void clear();
  size_t sizeOfQueue_;
  Node *front_node_;
  Node *back_node_;
};

template <typename T>
queue<T>::queue()
    : sizeOfQueue_(0), front_node_(nullptr), back_node_(nullptr) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : sizeOfQueue_(0), front_node_(nullptr), back_node_(nullptr) {
  if (items.size() > 0) {
    Node **iter = &front_node_;
    auto fr = items.begin();
    auto end = items.end() - 1;
    while (fr != end) {
      *iter = new Node{*fr, nullptr};
      ++fr;
      iter = &(*iter)->next;
      ++sizeOfQueue_;
    }
    *iter = new Node{*fr, nullptr};
    back_node_ = *iter;
    ++sizeOfQueue_;
  }
}

template <typename T>
queue<T>::queue(const queue &q)
    : sizeOfQueue_(q.sizeOfQueue_), front_node_(nullptr), back_node_(nullptr) {
  if (!q.empty()) {
    Node **dst_ptr = &front_node_;
    Node *src_ptr = q.front_node_;
    while (src_ptr != q.back_node_) {
      *dst_ptr = new Node{src_ptr->data, nullptr};
      dst_ptr = &(*dst_ptr)->next;
      src_ptr = src_ptr->next;
    }
    back_node_ = *dst_ptr = new Node{src_ptr->data, nullptr};
  }
}

template <typename T>
queue<T>::queue(queue &&q)
    : sizeOfQueue_(q.sizeOfQueue_),
      front_node_(q.front_node_),
      back_node_(q.back_node_) {
  q.sizeOfQueue_ = 0;
  q.back_node_ = nullptr;
  q.front_node_ = nullptr;
}

template <typename T>
queue<T>::~queue() {
  clear();
}

template <typename T>
my::queue<T> &my::queue<T>::operator=(queue &&l) {
  std::swap(sizeOfQueue_, l.sizeOfQueue_);
  std::swap(front_node_, l.front_node_);
  std::swap(back_node_, l.back_node_);
  return *this;
}

template <typename T>
void queue<T>::push(const_reference value) {
  ++sizeOfQueue_;
  if (empty()) {
    back_node_ = front_node_ = new Node{value, nullptr};
  } else {
    back_node_ = back_node_->next = new Node{value, nullptr};
  }
}

template <typename T>
void queue<T>::pop() {
  if (!empty()) {
    --sizeOfQueue_;
    Node *temp = front_node_->next;
    delete front_node_;
    front_node_ = temp;
    if (!front_node_) back_node_ = nullptr;
  }
}

template <typename T>
bool queue<T>::empty() const {
  if (front_node_ == nullptr) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
const T &queue<T>::front() const {
  return front_node_->data;
}

template <typename T>
const T &queue<T>::back() const {
  return back_node_->data;
}

template <typename T>
size_t queue<T>::size() const {
  return sizeOfQueue_;
}

template <typename T>
void queue<T>::swap(queue &other) {
  std::swap(sizeOfQueue_, other.sizeOfQueue_);
  std::swap(front_node_, other.front_node_);
  std::swap(back_node_, other.back_node_);
}

template <typename T>
void queue<T>::clear() {
  while (front_node_ != nullptr) {
    Node *ptr = front_node_->next;
    delete (front_node_);
    front_node_ = ptr;
  }
  sizeOfQueue_ = 0;
}

template <typename T>
template <typename... Args>
void my::queue<T>::emplace_back(Args &&...args) {
  (push(args), ...);
}

}  // namespace my

#endif  // CPP_MY_CONTAINERS_MY_QUEUE_MY_QUEUE_H_