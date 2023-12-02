#ifndef CPP_MY_CONTAINERS_MY_TREE_MY_TREE_H_
#define CPP_MY_CONTAINERS_MY_TREE_MY_TREE_H_

#include <iostream>

namespace my {
template <typename Key>
struct TNode {
  Key key;
  struct TNode *parent = nullptr;
  struct TNode *left = nullptr;
  struct TNode *right = nullptr;
};

template <typename Key>
class Iterator {
 public:
  Iterator() : iterator_(nullptr){};
  Iterator(struct TNode<Key> *iterator) : iterator_(iterator){};
  Iterator(const Iterator &other);
  Iterator(Iterator &&other);
  bool operator!=(const Iterator<Key> &other);
  Key &operator*();
  Iterator<Key> &operator++();
  Iterator<Key> operator++(int);
  Iterator<Key> &operator--();
  Iterator<Key> operator--(int);
  Iterator<Key> operator=(const Iterator<Key> &other);

 private:
  struct TNode<Key> *iterator_;
  void NextElem() noexcept;
  void PrevElem() noexcept;
};

template <typename Key>
class ConstIterator {
  using const_reference = const Key &;

 public:
  ConstIterator() : iterator_(nullptr){};
  ConstIterator(const struct TNode<Key> *iterator) : iterator_(iterator){};
  ConstIterator(const ConstIterator &other);
  ConstIterator(ConstIterator &&other);
  bool operator!=(const ConstIterator<Key> &other);
  const_reference operator*();
  ConstIterator<Key> &operator++();
  ConstIterator<Key> operator++(int);
  ConstIterator<Key> &operator--();
  ConstIterator<Key> operator--(int);

 private:
  const struct TNode<Key> *iterator_;
  void NextElem() noexcept;
  void PrevElem() noexcept;
};

template <typename Key>
class Tree {
 public:
  Tree() : count(0), root(nullptr){};
  Tree(const Tree &other);
  Tree(Tree &&other);
  ~Tree();
  Tree &operator=(const Tree &other);
  inline Iterator<Key> Begin() const noexcept;
  inline Iterator<Key> End() const noexcept;
  using iterator = Iterator<Key>;
  using const_iterator = ConstIterator<Key>;

 protected:
  int count;
  struct TNode<Key> *root;
  struct TNode<Key> *FindNode(const Key &x);
  void Remove(Key x);
  Iterator<Key> AddElem(const Key &x) noexcept;
  inline bool Contains(const Key &key) noexcept;
  inline void DeleteTree(struct TNode<Key> *node) noexcept;

 private:
  inline struct TNode<Key> *MinInBranch(struct TNode<Key> *node) const noexcept;
  inline struct TNode<Key> *MaxInBranch(struct TNode<Key> *node) noexcept;
  inline void CopyTree(const Tree<Key> &other) noexcept;
};

template <typename Key>
void Iterator<Key>::NextElem() noexcept {
  if (iterator_->right != nullptr) {
    iterator_ = iterator_->right;
    while (iterator_->left != nullptr) iterator_ = iterator_->left;
  } else {
    struct TNode<Key> *temp = iterator_;
    while (iterator_->parent != nullptr) {
      if (iterator_->parent->key > iterator_->key) {
        iterator_ = iterator_->parent;
        break;
      } else {
        iterator_ = iterator_->parent;
      }
    }
    if ((iterator_ == temp) ||
        (temp->key >= iterator_->key && iterator_ != temp))
      iterator_ = nullptr;
  }
}

template <typename Key>
void Iterator<Key>::PrevElem() noexcept {
  if (iterator_->left != nullptr) {
    iterator_ = iterator_->left;
    while (iterator_->right != nullptr) iterator_ = iterator_->right;
  } else {
    struct TNode<Key> *temp = iterator_;
    while (iterator_->parent != nullptr) {
      if (iterator_->parent->key < iterator_->key) {
        iterator_ = iterator_->parent;
        break;
      } else {
        iterator_ = iterator_->parent;
      }
    }
    if (temp->key <= iterator_->key && iterator_ != temp) iterator_ = nullptr;
  }
}

template <typename Key>
Iterator<Key> &Iterator<Key>::operator++() {
  NextElem();
  return *this;
}

template <typename Key>
Iterator<Key> Iterator<Key>::operator++(int) {
  Iterator old(iterator_);
  NextElem();
  return old;
}

template <typename Key>
Iterator<Key> &Iterator<Key>::operator--() {
  PrevElem();
  return *this;
}

template <typename Key>
Iterator<Key> Iterator<Key>::operator--(int) {
  Iterator old(iterator_);
  PrevElem();
  return old;
}

template <typename Key>
Iterator<Key>::Iterator(const Iterator<Key> &other) {
  iterator_ = other.iterator_;
}

template <typename Key>
Iterator<Key>::Iterator(Iterator &&other) {
  iterator_ = other.iterator_;
  other.iterator_ = nullptr;
}

template <typename Key>
Key &Iterator<Key>::operator*() {
  return iterator_->key;
}

template <typename Key>
ConstIterator<Key>::ConstIterator(const ConstIterator &other) {
  iterator_ = other.iterator_;
}

template <typename Key>
ConstIterator<Key>::ConstIterator(ConstIterator &&other) {
  iterator_ = other.iterator_;
  other.iterator_ = nullptr;
}

template <typename Key>
bool ConstIterator<Key>::operator!=(const ConstIterator<Key> &other) {
  bool result = true;
  if (iterator_ == other.iterator_) result = false;
  return result;
}

template <typename Key>
Iterator<Key> Iterator<Key>::operator=(const Iterator<Key> &other) {
  iterator_ = other.iterator_;
  return *this;
}

template <typename Key>
typename ConstIterator<Key>::const_reference ConstIterator<Key>::operator*() {
  return iterator_->key;
}

template <typename Key>
ConstIterator<Key> &ConstIterator<Key>::operator++() {
  NextElem();
  return *this;
}

template <typename Key>
ConstIterator<Key> ConstIterator<Key>::operator++(int) {
  ConstIterator old(iterator_);
  NextElem();
  return old;
}

template <typename Key>
ConstIterator<Key> &ConstIterator<Key>::operator--() {
  PrevElem();
  return *this;
}

template <typename Key>
ConstIterator<Key> ConstIterator<Key>::operator--(int) {
  ConstIterator old(iterator_);
  PrevElem();
  return old;
}

template <typename Key>
void ConstIterator<Key>::NextElem() noexcept {
  if (iterator_->right != nullptr) {
    iterator_ = iterator_->right;
    while (iterator_->left != nullptr) iterator_ = iterator_->left;
  } else {
    struct TNode<Key> *temp = iterator_;
    while (iterator_->parent != nullptr) {
      if (iterator_->parent->key > iterator_->key) {
        iterator_ = iterator_->parent;
        break;
      } else {
        iterator_ = iterator_->parent;
      }
    }
    if ((iterator_ == temp) ||
        (temp->key >= iterator_->key && iterator_ != temp))
      iterator_ = nullptr;
  }
}

template <typename Key>
void ConstIterator<Key>::PrevElem() noexcept {
  if (iterator_->left != nullptr) {
    iterator_ = iterator_->left;
    while (iterator_->right != nullptr) iterator_ = iterator_->right;
  } else {
    struct TNode<Key> *temp = iterator_;
    while (iterator_->parent != nullptr) {
      if (iterator_->parent->key < iterator_->key) {
        iterator_ = iterator_->parent;
        break;
      } else {
        iterator_ = iterator_->parent;
      }
    }
    if (temp->key <= iterator_->key && iterator_ != temp) iterator_ = nullptr;
  }
}

template <typename Key>
inline void Tree<Key>::DeleteTree(struct TNode<Key> *node) noexcept {
  if (node != nullptr) {
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
    node = nullptr;
  }
}

template <typename Key>
Tree<Key> &Tree<Key>::operator=(const Tree &other) {
  CopyTree(other);
  return *this;
}

template <typename Key>
Tree<Key>::Tree(const Tree<Key> &other) {
  CopyTree(other);
}

template <typename Key>
inline void Tree<Key>::CopyTree(const Tree<Key> &other) noexcept {
  DeleteTree(root);
  root = nullptr;
  Iterator<Key> it(other.Begin());
  for (; it != other.End(); ++it) AddElem(*it);
}

template <typename Key>
Tree<Key>::Tree(Tree &&other) : count(0), root(nullptr) {
  std::swap(count, other.count);
  std::swap(root, other.root);
}

template <typename Key>
Tree<Key>::~Tree() {
  DeleteTree(root);
  root = nullptr;
}

template <typename Key>
inline struct TNode<Key> *Tree<Key>::MinInBranch(
    struct TNode<Key> *node) const noexcept {
  if (node != nullptr) {
    while (node->left != nullptr) {
      node = node->left;
    }
  }
  return node;
}

template <typename Key>
inline struct TNode<Key> *Tree<Key>::MaxInBranch(
    struct TNode<Key> *node) noexcept {
  if (node != nullptr) {
    while (node->right != nullptr) {
      node = node->right;
    }
  }
  return node;
}

template <typename Key>
bool Iterator<Key>::operator!=(const Iterator<Key> &other) {
  bool result = true;
  if (iterator_ == other.iterator_) result = false;
  return result;
}

template <typename Key>
inline Iterator<Key> Tree<Key>::End() const noexcept {
  return iterator(nullptr);
}

template <typename Key>
inline Iterator<Key> Tree<Key>::Begin() const noexcept {
  return iterator(MinInBranch(root));
  ;
}

template <typename Key>
Iterator<Key> Tree<Key>::AddElem(const Key &x) noexcept {
  struct TNode<Key> *node = root;
  if (root == nullptr) {
    root = new struct TNode<Key>;
    root->key = x;
    node = root;
    root->right = nullptr;
    root->left = nullptr;
  } else {
    struct TNode<Key> *temp;
    while (true) {
      if (node->key > x) {
        if (node->left == nullptr) {
          node->left = new struct TNode<Key>;
          temp = node;
          node = node->left;
          temp->left = node;
          node->parent = temp;
          node->key = x;
          node->left = nullptr;
          node->right = nullptr;
          break;
        } else {
          node = node->left;
        }
      } else {
        if (node->right == nullptr) {
          node->right = new struct TNode<Key>;
          temp = node;
          node = node->right;
          temp->right = node;
          node->parent = temp;
          node->key = x;
          node->left = nullptr;
          node->right = nullptr;
          break;
        } else {
          node = node->right;
        }
      }
    }
  }
  ++count;
  Iterator<Key> tempIterator(node);
  return tempIterator;
}

template <typename Key>
void Tree<Key>::Remove(Key x) {
  if (count == 0) throw std::exception();
  struct TNode<Key> *node = FindNode(x);  // Алгоритм разбивается на 3 случая
  if (node == nullptr) throw std::exception();
  if (node->right == nullptr) {  // 1) когда нет правого  потомка
    if (x == root->key) {  // условие на то, что удаляемое число корень
      if (count != 1) {
        root = node->left;
        root->parent = nullptr;
      } else {
        root = nullptr;
      }
    } else if (node->left !=
               nullptr) {  // проверка есть ли у узла вообще соседи
      node->left->parent = node->parent;
      node->parent->left = node->left;
    } else {
      if (node->parent->right ==
          nullptr) {  // если нет правого потомка, то точно нужно удалить левого
                      // (мы не можем понять без этих 2 условий какого потомка
                      // удалять, если один из них nullptr(просто в else вылетит
                      // сега))
        node->parent->left = nullptr;
      } else if (node->parent->left == nullptr) {  // с точности до наоборот
        node->parent->right = nullptr;
      } else {
        if (node->parent->right->key == x)
          node->parent->right = nullptr;  // если у правого потомка ключ равен
                                          // x, удаляем его, и также с левым
        else
          node->parent->left = nullptr;
      }
    }
  } else if (node->right->left ==
             nullptr) {  // 2) Когда у правого потомка нет левого
    if (x != root->key) {  // условие на то, что удаляемое число корень
      node->right->parent = node->parent;
      node->parent->right = node->right;
    } else {
      root = node->right;
      root->parent = nullptr;
    }
    if (node->left != nullptr) node->left->parent = node->right;
    node->right->left = node->left;
  } else {  // 3)  Когда у правого потомка есть левый (находим самый левый
            // элемент этой ветки и меняем его с нашим числом)
    struct TNode<Key> *temp = node;
    node = node->right;
    node = MinInBranch(node);
    if (node->right)
      node->parent->left = node->right;
    else
      node->parent->left = nullptr;
    node->left = temp->left;
    node->right = temp->right;
    if (temp->left != nullptr) temp->left->parent = node;
    temp->right->parent = node;
    if (temp != root) {
      if (temp->parent->right != nullptr && temp->parent->right->key == x)
        temp->parent->right = node;
      else if (temp->parent->left != nullptr && temp->parent->left->key == x)
        temp->parent->left = node;
      node->parent = temp->parent;
    } else {
      root = node;
    }
    node = temp;
  }
  delete node;
  node = nullptr;
  count--;
}

template <typename Key>
struct TNode<Key> *Tree<Key>::FindNode(const Key &x) {
  struct TNode<Key> *node = root;
  while (node != nullptr) {
    if (node->key > x) {
      node = node->left;
    } else if (node->key < x) {
      node = node->right;
    } else {
      break;
    }
  }
  return node;
}

template <typename Key>
inline bool Tree<Key>::Contains(const Key &key) noexcept {
  return FindNode(key) != nullptr;
}
}  // namespace my
#endif  // CPP_MY_CONTAINERS_MY_TREE_MY__TREE_H_
