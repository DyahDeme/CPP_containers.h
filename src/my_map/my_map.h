#ifndef CPP_MY_CONTAINERS_MY_MAP_MY_MAP_H_
#define CPP_MY_CONTAINERS_MY_MAP_MY_MAP_H_

#include "../my_list/my_list.h"
#include "../my_tree/my_tree.h"
#include "../my_vector/my_vector.h"

namespace my {
template <typename Key, typename T>
class Map : public Tree<std::pair<Key, T>> {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<std::pair<Key, T>>::iterator;
  using const_iterator = typename Tree<Key>::const_iterator;
  using size_type = size_t;

 public:
  Map();
  Map(const Map &m);
  Map(Map &&m);
  Map(std::initializer_list<value_type> const &items);
  ~Map();
  Map operator=(Map &&m);
  Map operator=(const Map &m);
  inline T &At(const Key &key);
  T &operator[](const Key &key);
  inline bool Empty() noexcept;
  inline size_t Size() noexcept;
  inline size_t Max_size() noexcept;
  inline void Clear() noexcept;
  inline std::pair<typename Tree<std::pair<Key, T>>::iterator, bool> Insert(
      const value_type &value) noexcept;
  inline std::pair<typename Tree<std::pair<Key, T>>::iterator, bool> Insert(
      const Key &key, const T &obj) noexcept;
  std::pair<typename Tree<std::pair<Key, T>>::iterator, bool> Insert_or_assign(
      const Key &key, const T &obj) noexcept;
  inline void Erase(typename Tree<std::pair<Key, T>>::iterator pos) noexcept;
  inline void Swap(Map &other) noexcept;
  void Merge(Map &other) noexcept;
  inline bool Contains(const Key &key) noexcept;

  template <typename... Args>
  inline vector<std::pair<typename Tree<std::pair<Key, T>>::iterator, bool>>
  Emplace(Args &&...args) noexcept;

 private:
  inline void AddElementsFromOtherMap(const Map &s) noexcept;
};

template <typename Key, typename T>
Map<Key, T>::Map() {
  Tree<std::pair<Key, T>>::count = 0;
  Tree<std::pair<Key, T>>::root = nullptr;
}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if (!Map::Contains((*it).first))
      Tree<std::pair<Key, T>>::AddElem(
          std::make_pair((*it).first, (*it).second));
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map &m) : Tree<std::pair<Key, T>>() {
  AddElementsFromOtherMap(m);
}

template <typename Key, typename T>
Map<Key, T>::Map(Map &&m)
    : Tree<std::pair<Key, T>>::count(0),
      Tree<std::pair<Key, T>>::root(nullptr) {
  std::swap(Tree<std::pair<Key, T>>::count, Tree<std::pair<Key, T>>::m.count);
  std::swap(Tree<std::pair<Key, T>>::root, Tree<std::pair<Key, T>>::m.root);
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  Clear();
}

template <typename Key, typename T>
Map<Key, T> Map<Key, T>::operator=(Map &&other) {
  std::swap(Tree<std::pair<Key, T>>::count,
            Tree<std::pair<Key, T>>::other.count);
  std::swap(Tree<std::pair<Key, T>>::root, Tree<std::pair<Key, T>>::other.root);
  return *this;
}

template <typename Key, typename T>
Map<Key, T> Map<Key, T>::operator=(const Map &other) {
  Clear();
  AddElementsFromOtherMap(other);
  return *this;
}

template <typename Key, typename T>
inline std::pair<typename Tree<std::pair<Key, T>>::iterator, bool>
Map<Key, T>::Insert(const Key &key, const T &obj) noexcept {
  std::pair<typename Tree<std::pair<Key, T>>::iterator, bool> result;
  if (!Map::Contains(key))
    result = {Tree<std::pair<Key, T>>::AddElem(std::make_pair(key, obj)), true};
  else
    result = {Tree<std::pair<Key, T>>::End(), false};
  return result;
}

template <typename Key, typename T>
inline std::pair<typename Tree<std::pair<Key, T>>::iterator, bool>
Map<Key, T>::Insert(const value_type &value) noexcept {
  std::pair<typename Tree<std::pair<Key, T>>::iterator, bool> result;
  if (!Map::Contains(value.first))
    result = {Tree<std::pair<Key, T>>::AddElem(value), true};
  else
    result = {Tree<std::pair<Key, T>>::End(), false};
  return result;
}

template <typename Key, typename T>
std::pair<typename Tree<std::pair<Key, T>>::iterator, bool>
Map<Key, T>::Insert_or_assign(const Key &key, const T &obj) noexcept {
  std::pair<typename Tree<std::pair<Key, T>>::iterator, bool> result;
  if (Contains(key)) {
    At(key) = obj;
    for (auto it = this->Begin(); it != this->End(); ++it)
      if ((*it).first == key) {
        result.first = it;
        break;
      }
    result.second = false;
  } else {
    result = Insert(key, obj);
  }
  return result;
}

template <typename Key, typename T>
inline T &Map<Key, T>::At(const Key &key) {
  if (!Contains(key)) throw std::exception();
  auto it = this->Begin();
  for (; it != this->End(); ++it) {
    if ((*it).first == key) break;
  }
  return (*it).second;
}

template <typename Key, typename T>
T &Map<Key, T>::operator[](const Key &key) {
  if (!Contains(key)) Insert(key, 0);
  return At(key);
}

template <typename Key, typename T>
inline bool Map<Key, T>::Empty() noexcept {
  return (Tree<std::pair<Key, T>>::count == 0) ? true : false;
}

template <typename Key, typename T>
size_t Map<Key, T>::Max_size() noexcept {
  return SIZE_MAX / sizeof(value_type);
}

template <typename Key, typename T>
size_t Map<Key, T>::Size() noexcept {
  return Tree<std::pair<Key, T>>::count;
}

template <typename Key, typename T>
inline void Map<Key, T>::Clear() noexcept {
  Tree<std::pair<Key, T>>::DeleteTree(Tree<std::pair<Key, T>>::root);
  Tree<std::pair<Key, T>>::root = nullptr;
}

template <typename Key, typename T>
inline void Map<Key, T>::Erase(
    typename Tree<std::pair<Key, T>>::iterator pos) noexcept {
  Tree<std::pair<Key, T>>::Remove(*pos);
}

template <typename Key, typename T>
inline bool Map<Key, T>::Contains(const Key &key) noexcept {
  bool result = false;
  for (auto it = this->Begin(); it != this->End(); ++it) {
    if ((*it).first == key) {
      result = true;
      break;
    }
  }
  return result;
}

template <typename Key, typename T>
inline void Map<Key, T>::Swap(Map &other) noexcept {
  Tree<std::pair<Key, T>>::count = 0;
  other.Tree<std::pair<Key, T>>::count = 0;
  Map<Key, T> tempMap(*this);
  *this = other;
  other = tempMap;
}

template <typename Key, typename T>
void Map<Key, T>::Merge(Map &other) noexcept {
  auto it = other.Begin();
  while (it != other.End()) {
    if (!Contains((*it).first)) {
      Insert((*it).first, (*it).second);
      Iterator<std::pair<Key, T>> temp = it;
      ++it;
      other.Erase(temp);
    } else {
      ++it;
    }
  }
}

template <typename Key, typename T>
inline void Map<Key, T>::AddElementsFromOtherMap(const Map &s) noexcept {
  for (auto it = s.Begin(); it != s.End(); ++it)
    Insert((*it).first, (*it).second);
}

template <typename Key, typename T>
template <typename... Args>
inline vector<std::pair<typename Tree<std::pair<Key, T>>::iterator, bool>>
Map<Key, T>::Emplace(Args &&...args) noexcept {
  vector<std::pair<typename Tree<std::pair<Key, T>>::iterator, bool>> result;
  (result.push_back(Insert(args)), ...);
  return result;
}

}  // namespace my

#endif  // CPP_MY_CONTAINERS_MY_MAP_MY_MAP_H_