#ifndef CPP_MY_CONTAINERS_MY_SET_MY_SET_H_
#define CPP_MY_CONTAINERS_MY_SET_MY_SET_H_

#include "../my_list/my_list.h"
#include "../my_tree/my_tree.h"
#include "../my_vector/my_vector.h"

namespace my {
template <typename Key>
class Set : public Tree<Key> {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<Key>::iterator;
  using const_iterator = typename Tree<Key>::const_iterator;
  using size_type = size_t;

 public:
  Set();
  Set(std::initializer_list<value_type> const &items);
  Set(const Set &s);
  Set(Set &&s);
  ~Set();
  inline std::pair<typename Tree<Key>::iterator, bool> Insert(
      const Key &value) noexcept;
  inline bool Empty() noexcept;
  inline size_t Size() noexcept;
  inline size_t Max_size() noexcept;
  inline Iterator<Key> Find(const Key &key) noexcept;
  inline void Erase(Iterator<Key> pos) noexcept;
  void Merge(Set &other) noexcept;
  inline void Swap(Set &other) noexcept;
  Set operator=(Set &&s);
  Set operator=(const Set &otsher);
  inline bool Contains(const Key &key) noexcept;
  inline void Clear() noexcept;

  template <typename... Args>
  inline vector<std::pair<typename Tree<Key>::iterator, bool>> Emplace(
      Args &&...args) noexcept;

 protected:
  inline Iterator<Key> AddElem(const Key &x) noexcept;

 private:
  inline void AddElementsForOtherSet(const Set &s) noexcept;
};

template <typename Key>
Set<Key>::Set() {
  Tree<Key>::count = 0;
  Tree<Key>::root = nullptr;
}

template <typename Key>
Set<Key>::Set(const Set &s) : Tree<Key>() {
  AddElementsForOtherSet(s);
}

template <typename Key>
Set<Key>::Set(Set &&s) : Tree<Key>::count(0), Tree<Key>::root(nullptr) {
  std::swap(Tree<Key>::count, Tree<Key>::other.count);
  std::swap(Tree<Key>::root, Tree<Key>::other.root);
}

template <typename Key>
Set<Key>::Set(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if (!Contains(*it)) Insert(*it);
  }
}

template <typename Key>
Set<Key>::~Set() {
  Clear();
}

template <typename Key>
Set<Key> Set<Key>::operator=(Set<Key> &&other) {
  std::swap(Tree<Key>::count, Tree<Key>::other.count);
  std::swap(Tree<Key>::root, Tree<Key>::other.root);
  return *this;
}

template <typename Key>
Set<Key> Set<Key>::operator=(const Set<Key> &other) {
  Clear();
  AddElementsForOtherSet(other);
  return *this;
}

template <typename Key>
inline void Set<Key>::AddElementsForOtherSet(const Set<Key> &s) noexcept {
  for (auto it = s.Begin(); it != s.End(); ++it) {
    Insert(*it);
  }
}

template <typename Key>
inline std::pair<typename Tree<Key>::iterator, bool> Set<Key>::Insert(
    const Key &value) noexcept {
  std::pair<typename Tree<Key>::iterator, bool> result;
  if (Tree<Key>::Contains(value))
    result = {Tree<Key>::End(), false};
  else
    result = {Tree<Key>::AddElem(value), true};
  return result;
}

template <typename Key>
inline bool Set<Key>::Empty() noexcept {
  return (Tree<Key>::count == 0) ? true : false;
}

template <typename Key>
inline size_t Set<Key>::Size() noexcept {
  return Tree<Key>::count;
}

template <typename Key>
inline size_t Set<Key>::Max_size() noexcept {
  return SIZE_MAX / sizeof(value_type);
}

template <typename Key>
inline Iterator<Key> Set<Key>::Find(const Key &key) noexcept {
  Iterator<Key> iter(Tree<Key>::FindNode(key));
  return iter;
}

template <typename Key>
inline void Set<Key>::Erase(Iterator<Key> pos) noexcept {
  Tree<Key>::Remove(*pos);
}

template <typename Key>
void Set<Key>::Merge(Set<Key> &other) noexcept {
  auto it = other.Begin();
  while (it != other.End()) {
    if (!Tree<Key>::Contains(*it)) {
      Insert(*it);
      Iterator<Key> temp = it;
      ++it;
      other.Erase(temp);
    } else {
      ++it;
    }
  }
}

template <typename Key>
inline void Set<Key>::Swap(Set<Key> &other) noexcept {
  Tree<Key>::count = 0;
  other.Tree<Key>::count = 0;
  Set<Key> tempSet(*this);
  *this = other;
  other = tempSet;
}

template <typename Key>
inline void Set<Key>::Clear() noexcept {
  Tree<Key>::DeleteTree(Tree<Key>::root);
  Tree<Key>::root = nullptr;
}

template <typename Key>
inline bool Set<Key>::Contains(const Key &key) noexcept {
  return Tree<Key>::Contains(key);
}

template <typename Key>
inline Iterator<Key> Set<Key>::AddElem(const Key &key) noexcept {
  return Tree<Key>::AddElem(key);
}

template <typename Key>
template <typename... Args>
inline vector<std::pair<typename Tree<Key>::iterator, bool>> Set<Key>::Emplace(
    Args &&...args) noexcept {
  vector<std::pair<typename Tree<Key>::iterator, bool>> result;
  (result.push_back(Insert(args)), ...);
  return result;
}

}  // namespace my
#endif  // CPP_MY_CONTAINERS_MY_SET_MY_SET_H_
