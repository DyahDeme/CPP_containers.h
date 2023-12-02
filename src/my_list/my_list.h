#ifndef CPP_MY_CONTAINERS_MY_LIST_MY_LIST_H_
#define CPP_MY_CONTAINERS_MY_LIST_MY_LIST_H_
#include <initializer_list>

namespace my {

template <typename T>
struct D_Node {
  using value_type = T;
  value_type data;
  struct D_Node *prev = nullptr;
  struct D_Node *next = nullptr;
};

template <typename T>
class ListIterator {
  using value_type = T;
  using reference = T &;

 public:
  ListIterator();
  ListIterator(D_Node<T> *iterator_);
  reference operator*();
  ListIterator &operator++();
  ListIterator operator++(int);
  ListIterator &operator--();
  ListIterator operator--(int);
  bool operator!=(const ListIterator &rhs) const;
  bool operator==(const ListIterator &rhs) const;
  struct D_Node<T> *iterator_ = nullptr;
};

template <typename T>
class ListConstIterator {
  using value_type = T;
  using const_reference = const T &;

 public:
  ListConstIterator(const ListIterator<T> &pos);
  const_reference operator*();
  ListConstIterator &operator++();
  ListConstIterator operator++(int);
  ListConstIterator &operator--();
  ListConstIterator operator--(int);
  bool operator!=(const ListConstIterator &rhs) const;
  bool operator==(const ListConstIterator &rhs) const;
  const struct D_Node<T> *iterator_ = nullptr;
};

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = D_Node<T>;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);
  bool empty() const;
  const_reference front() const;
  const_reference back() const;
  iterator begin();
  iterator end();
  size_type size() const;
  size_type max_size() const;
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  iterator emplace(const_iterator pos);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  size_t sizeOfList_;
  Node *fake_node_;
  Node *front_node_;
  Node *back_node_;
};

template <typename T>
ListIterator<T>::ListIterator() : iterator_(nullptr){};

template <typename T>
ListIterator<T>::ListIterator(D_Node<T> *iterator_) : iterator_(iterator_){};

template <typename T>
T &ListIterator<T>::operator*() {
  if (!iterator_->next) {
    throw(std::out_of_range("You can't dereference end iterator"));
  }
  return iterator_->data;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator++() {
  if (iterator_->next) iterator_ = iterator_->next;
  return (*this);
}

template <typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
  ListIterator old{iterator_};
  if (iterator_->next) iterator_ = iterator_->next;
  return old;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator--() {
  if (iterator_->prev) iterator_ = iterator_->prev;
  return (*this);
}

template <typename T>
ListIterator<T> ListIterator<T>::operator--(int) {
  ListIterator old{iterator_};
  if (iterator_->prev) iterator_ = iterator_->prev;
  return old;
}

template <typename T>
bool ListIterator<T>::operator!=(const ListIterator<T> &rhs) const {
  return (iterator_ != rhs.iterator_);
}

template <typename T>
bool ListIterator<T>::operator==(const ListIterator<T> &rhs) const {
  return (iterator_ == rhs.iterator_);
}

template <typename T>
ListConstIterator<T>::ListConstIterator(const ListIterator<T> &pos) {
  iterator_ = pos.iterator_;
};

template <typename T>
const T &ListConstIterator<T>::operator*() {
  return iterator_->data;
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator++() {
  if (iterator_->next) iterator_ = iterator_->next;
  return (*this);
}

template <typename T>
inline ListConstIterator<T> ListConstIterator<T>::operator++(int) {
  ListConstIterator<T> old{*this};
  if (iterator_->next) iterator_ = iterator_->next;
  return old;
}

template <typename T>
ListConstIterator<T> &ListConstIterator<T>::operator--() {
  if (iterator_->prev) iterator_ = iterator_->prev;
  return (*this);
}

template <typename T>
inline ListConstIterator<T> ListConstIterator<T>::operator--(int) {
  ListConstIterator old{*this};
  if (iterator_->prev) iterator_ = iterator_->prev;
  return old;
}

template <typename T>
bool ListConstIterator<T>::operator!=(const ListConstIterator<T> &rhs) const {
  return (iterator_ != rhs.iterator_);
}

template <typename T>
bool ListConstIterator<T>::operator==(const ListConstIterator<T> &rhs) const {
  return (iterator_ == rhs.iterator_);
}

template <typename T>
list<T>::list()
    : sizeOfList_(0),
      fake_node_(new Node{}),
      front_node_(fake_node_),
      back_node_(fake_node_) {}

template <typename T>
list<T>::list(size_type n)
    : sizeOfList_(0),
      fake_node_(new Node{}),
      front_node_(fake_node_),
      back_node_(fake_node_) {
  if (n > 0) {
    Node **iter = &front_node_;
    Node *temp = nullptr;
    for (size_t i = 0; i < n - 1; ++i) {
      temp = *iter = new Node{T(), temp, nullptr};
      iter = &(*iter)->next;
    }
    *iter = new Node{T(), temp, fake_node_};
    back_node_ = *iter;
    fake_node_->prev = back_node_;
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : sizeOfList_(items.size()),
      fake_node_(new Node{}),
      front_node_(fake_node_),
      back_node_(fake_node_) {
  if (items.size() > 0) {
    Node **iter = &front_node_;
    Node *temp = nullptr;
    auto fr = items.begin();
    auto end = items.end() - 1;
    while (fr != end) {
      temp = *iter = new Node{*fr, temp, nullptr};
      ++fr;
      iter = &(*iter)->next;
    }
    *iter = new Node{*fr, temp, fake_node_};
    back_node_ = *iter;
    fake_node_->prev = back_node_;
  }
}

template <typename T>
list<T>::list(const list &l)
    : sizeOfList_(l.sizeOfList_),
      fake_node_(new Node{}),
      front_node_(fake_node_),
      back_node_(fake_node_) {
  Node **dst_ptr = &front_node_;
  Node *src_ptr = l.front_node_;
  Node *temp = nullptr;
  while (src_ptr != l.back_node_) {
    temp = *dst_ptr = new Node{src_ptr->data, temp, nullptr};
    dst_ptr = &(*dst_ptr)->next;
    src_ptr = src_ptr->next;
  }

  back_node_ = *dst_ptr = new Node{src_ptr->data, temp, fake_node_};
  fake_node_->prev = back_node_;
}

template <typename T>
list<T>::list(list &&l)
    : sizeOfList_(l.sizeOfList_),
      fake_node_(l.fake_node_),
      front_node_(l.front_node_),
      back_node_(l.back_node_) {
  l.sizeOfList_ = 0;
  l.fake_node_ = new Node{};
  l.back_node_ = l.fake_node_;
  l.front_node_ = l.fake_node_;
}

template <typename T>
list<T>::~list() {
  clear();
  if (fake_node_) delete fake_node_;
}

template <typename T>
my::list<T> &my::list<T>::operator=(list &&l) {
  std::swap(sizeOfList_, l.sizeOfList_);
  std::swap(fake_node_, l.fake_node_);
  std::swap(front_node_, l.front_node_);
  std::swap(back_node_, l.back_node_);
  return *this;
}

template <typename T>
void list<T>::clear() {
  while (front_node_ != fake_node_) {
    Node *ptr = front_node_->next;
    delete (front_node_);
    front_node_ = ptr;
  }
  sizeOfList_ = 0;
}

template <typename T>
inline bool my::list<T>::empty() const {
  return front_node_ == fake_node_;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  fake_node_->prev = new Node{value, nullptr, fake_node_};
  Node *temp = back_node_;
  back_node_ = fake_node_->prev;
  if (empty()) {
    front_node_ = back_node_;
  } else {
    temp->next = back_node_;
    back_node_->prev = temp;
  }
  ++sizeOfList_;
}

template <typename T>
void list<T>::pop_back() {
  if (!empty()) {
    if (back_node_->prev) {
      back_node_->prev->next = fake_node_;
      delete (back_node_);
      back_node_ = back_node_->prev;
      fake_node_->prev = back_node_;
      --sizeOfList_;
    } else {
      clear();
    }
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  ++sizeOfList_;
  if (empty()) {
    front_node_ = back_node_ = fake_node_->prev =
        new Node{value, nullptr, fake_node_};
  } else {
    front_node_->prev = new Node{value, nullptr, front_node_};
    front_node_ = front_node_->prev;
  }
}

template <typename T>
void list<T>::pop_front() {
  if (!empty())
    if (front_node_->next) {
      delete (front_node_);
      front_node_ = front_node_->next;
      if (empty()) fake_node_->prev = nullptr;
      --sizeOfList_;
    }
}

template <typename T>
typename my::list<T>::iterator my::list<T>::insert(iterator pos,
                                                     const_reference value) {
  Node *temp = pos.iterator_->prev;
  pos.iterator_->prev = new Node{value, pos.iterator_->prev, pos.iterator_};
  if (temp) temp->next = pos.iterator_->prev;
  if (pos.iterator_ == fake_node_) back_node_ = pos.iterator_->prev;
  if (pos.iterator_ == front_node_) front_node_ = pos.iterator_->prev;
  pos.iterator_ = pos.iterator_->prev;
  ++sizeOfList_;
  return pos;
}

template <typename T>
void my::list<T>::splice(const_iterator pos, list &other) {
  iterator it1 = front_node_;
  iterator it2(const_cast<Node *>(pos.iterator_));
  while (it1 != it2) {
    it1++;
  }
  for (iterator iter1 = other.front_node_; iter1 != other.fake_node_; iter1++) {
    insert(it1, *iter1);
  }
}

template <typename T>
void my::list<T>::erase(iterator pos) {
  if (pos.iterator_ != front_node_) {
    pos.iterator_->next->prev = pos.iterator_->prev;
    pos.iterator_->prev->next = pos.iterator_->next;
    delete (pos.iterator_);
    --sizeOfList_;
  } else {
    if (pos.iterator_ != fake_node_) {
      delete (pos.iterator_);
      front_node_ = front_node_->next;
      --sizeOfList_;
    }
  }
}

template <typename T>
void list<T>::merge(list &other) {
  iterator iter1 = front_node_;
  iterator iter2 = other.front_node_;
  while ((iter2 != other.fake_node_) && (iter1 != fake_node_)) {
    if (*iter1 <= *iter2) {
      iter1++;
    } else {
      insert(iter1, *iter2);
      iter2++;
    }
  }
  while (iter2 != other.fake_node_) {
    insert(iter1, *iter2);
    iter2++;
  }
  fake_node_->prev = back_node_;
  other.clear();
}

template <typename T>
void list<T>::sort() {
  for (iterator iter1 = front_node_; iter1 != fake_node_; iter1++)
    for (iterator iter2 = front_node_; iter2 != back_node_; iter2++)
      if (*iter2 > iter2.iterator_->next->data)
        std::swap(iter2.iterator_->data, iter2.iterator_->next->data);
}

template <typename T>
void list<T>::unique() {
  for (iterator iter = front_node_; iter != fake_node_; iter++)
    if (*iter == iter.iterator_->next->data) erase(iter);
}

template <typename T>
void list<T>::reverse() {
  for (iterator iter1 = back_node_; iter1 != front_node_; iter1--)
    for (iterator iter2 = front_node_; iter2 != iter1; iter2++)
      std::swap(iter2.iterator_->data, iter2.iterator_->next->data);
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(sizeOfList_, other.sizeOfList_);
  std::swap(fake_node_, other.fake_node_);
  std::swap(front_node_, other.front_node_);
  std::swap(back_node_, other.back_node_);
}

template <typename T>
const T &my::list<T>::front() const {
  return front_node_->data;
}

template <typename T>
const T &my::list<T>::back() const {
  return back_node_->data;
}

template <typename T>
size_t list<T>::size() const {
  return sizeOfList_;
}

template <typename T>
size_t list<T>::max_size() const {
  return SIZE_MAX / sizeof(Node) / 2;
}

template <typename T>
typename my::list<T>::iterator my::list<T>::begin() {
  return iterator(front_node_);
}

template <typename T>
typename my::list<T>::iterator my::list<T>::end() {
  return iterator(fake_node_);
}

template <typename T>
template <typename... Args>
typename my::list<T>::iterator my::list<T>::emplace(const_iterator pos,
                                                      Args &&...args) {
  (insert(iterator(const_cast<Node *>(pos.iterator_)), args), ...);
  return iterator(front_node_);
}

template <typename T>
typename my::list<T>::iterator my::list<T>::emplace(const_iterator pos) {
  return iterator(const_cast<Node *>(pos.iterator_));
}

template <typename T>
template <typename... Args>
void my::list<T>::emplace_back(Args &&...args) {
  (push_back(args), ...);
}

template <typename T>
template <typename... Args>
void my::list<T>::emplace_front(Args &&...args) {
  iterator iter(front_node_);
  (insert(iter, args), ...);
}

}  // namespace my
#endif  // CPP_MY_CONTAINERS_MY_LIST_MY_LIST_H_