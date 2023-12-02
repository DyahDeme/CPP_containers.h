#ifndef CPP_MY_CONTAINERS_MULTISET_MULTISET_H_
#define CPP_MY_CONTAINERS_MULTISET_MULTISET_H_

#include "../my_set/my_set.h"

namespace my {
template <typename Key>
class Multiset : public Set<Key> {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<Key>::iterator;
  using const_iterator = typename Tree<Key>::const_iterator;
  using size_type = size_t;

 public:
  Multiset();
  Multiset(std::initializer_list<value_type> const &items);
  Multiset(const Multiset &ms);
  Multiset(Multiset &&ms);
  ~Multiset();
  Multiset<Key> operator=(Multiset<Key> &&other);
  Multiset<Key> operator=(const Multiset<Key> &other);
  inline typename Tree<Key>::iterator Insert(const value_type &type) noexcept;
  inline std::pair<typename Tree<Key>::iterator, typename Tree<Key>::iterator>
  Equal_range(const Key &key) noexcept;
  inline Iterator<Key> Lower_bound(const Key &key) noexcept;
  inline Iterator<Key> Upper_bound(const Key &key) noexcept;
  inline void Merge(Multiset &other) noexcept;
  inline void Swap(Multiset &other) noexcept;

  template <typename... Args>
  inline vector<std::pair<typename Tree<Key>::iterator, bool>> Emplace(
      Args &&...args) noexcept;
};

template <typename Key>
Multiset<Key>::Multiset() {
  Tree<Key>::count = 0;
  Tree<Key>::root = nullptr;
}

template <typename Key>
Multiset<Key>::Multiset(const Multiset &ms) : Set<Key>() {
  for (auto it = ms.Begin(); it != ms.End(); ++it) {
    Insert(*it);
  }
}

template <typename Key>
Multiset<Key>::Multiset(Multiset &&ms)
    : Tree<Key>::count(0), Tree<Key>::root(nullptr) {
  std::swap(Tree<Key>::count, Tree<Key>::other.count);
  std::swap(Tree<Key>::root, Tree<Key>::other.root);
}

template <typename Key>
Multiset<Key>::~Multiset() {
  Set<Key>::Clear();
}

template <typename Key>
Multiset<Key> Multiset<Key>::operator=(Multiset<Key> &&other) {
  std::swap(Tree<Key>::count, Tree<Key>::other.count);
  std::swap(Tree<Key>::root, Tree<Key>::other.root);
  return *this;
}

template <typename Key>
Multiset<Key> Multiset<Key>::operator=(const Multiset<Key> &other) {
  Set<Key>::Clear();
  for (auto it = other.Begin(); it != other.End(); ++it) Insert(*it);
  return *this;
}

template <typename Key>
Multiset<Key>::Multiset(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    Insert(*it);
  }
}

template <typename Key>
inline typename Tree<Key>::iterator Multiset<Key>::Insert(
    const value_type &type) noexcept {
  return Set<Key>::AddElem(type);
}

template <typename Key>
inline std::pair<typename Tree<Key>::iterator, typename Tree<Key>::iterator>
Multiset<Key>::Equal_range(const Key &key) noexcept {
  auto iterator1 = Set<Key>::Find(key);
  auto iterator2 = iterator1;
  while (*iterator2 == *iterator1) {
    ++iterator2;
  }
  return {iterator1, iterator2};
}

template <typename Key>
inline Iterator<Key> Multiset<Key>::Lower_bound(const Key &key) noexcept {
  auto it = Set<Key>::Begin();
  while (it != Set<Key>::End() && *it < key) {
    ++it;
  }
  return it;
}

template <typename Key>
inline Iterator<Key> Multiset<Key>::Upper_bound(const Key &key) noexcept {
  auto it = Set<Key>::Begin();
  while (it != Set<Key>::End() && *it <= key) {
    ++it;
  }
  return it;
}

template <typename Key>
inline void Multiset<Key>::Merge(Multiset &other) noexcept {
  auto it = other.Begin();
  while (it != other.End()) {
    Insert(*it);
    Iterator<Key> temp = it;
    ++it;
    other.Erase(temp);
  }
}

template <typename Key>
inline void Multiset<Key>::Swap(Multiset &other) noexcept {
  Tree<Key>::count = 0;
  other.Tree<Key>::count = 0;
  Multiset<Key> tempSet(*this);
  *this = other;
  other = tempSet;
}

template <typename Key>
template <typename... Args>
inline vector<std::pair<typename Tree<Key>::iterator, bool>>
Multiset<Key>::Emplace(Args &&...args) noexcept {
  vector<std::pair<typename Tree<Key>::iterator, bool>> result;
  (result.push_back(std::make_pair(Insert(args), true)), ...);
  return result;
}

}  // namespace my

#endif  // CPP_MY_CONTAINERS_MULTISET_MULTISET_H_