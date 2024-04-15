//
// Created by Hotah Mireille on 4/7/24.
//

#ifndef CPP2_S21_CONTAINERS_2_S21_MAP_H
#define CPP2_S21_CONTAINERS_2_S21_MAP_H

#include "../AVLTree/AVLTree.h"

namespace s21 {

template<typename Key, typename T>
class map : public AVLTree<Key, T> {
 public:

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename AVLTree<Key, T>::Iterator;
  using const_iterator = typename AVLTree<Key, T>::ConstIterator;
  using size_type = size_t;


  map() : AVLTree<Key, T>() {};
  map(std::initializer_list<std::pair<const Key, T>> const &items);
  map(map &&other) : AVLTree<Key, T>(std::move(other)) {};
  map &operator=(map &&other);
  map &operator=(const map &other);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  void merge(map &other);
  void swap(map &other);




  bool contains(const Key& key);
  T &at(const Key &key);
  T &operator[](const Key &key);
  std::pair<iterator, bool> insert(const value_type &value);
//  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
};


template<typename Key, typename T>
bool map<Key, T>::contains(const Key &key){
  return find(key) != nullptr;
}

template<typename Key, typename T>
void map<Key, T>::swap(map<Key, T> &other) {
  AVLTree<Key, T>::swap(other);
}

template<typename Key, typename T>
map<Key, T>::map(const std::initializer_list<value_type> &items) {
//  root = nullptr;
  for (const auto &item : items) {
    insert(item);
  }
}

template<typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&other) {
  if (this != &other) {
    AVLTree<Key, T>::operator=(std::move(other));
  }
  return *this;
}

template<typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  if (this != &other) {
    AVLTree<Key, T>::operator=(std::move(other));
  }
  return *this;
}

template<typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return map<Key, T>::iterator(AVLTree<Key, T>::findMin(AVLTree<Key, T>::root));
}

template<typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::cbegin() const {
  return map<Key, T>::const_iterator(AVLTree<Key, T>::findMin(AVLTree<Key, T>::root));
}

template<typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return map<Key, T>::iterator(AVLTree<Key, T>::findMax(AVLTree<Key, T>::root));
}

template<typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::cend() const {
  return map<Key, T>::const_iterator(AVLTree<Key, T>::findMax(AVLTree<Key, T>::root));
}


template<typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  iterator it = AVLTree<Key, T>::find(key);
  if (it == nullptr) {
//    throw std::out_of_range("Key not found in map");
    static T fake_value{};
    return fake_value;
  }
  return it.iter_node->value;
}

template<typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  iterator it = AVLTree<Key, T>::find(key);
  if (it != end()) {
    return it.iter_node->value;

  } else {
    std::pair<iterator, bool> result = insert(std::make_pair(key, T()));
    return result.first.iter_node->value;
  }
}

template<typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(const value_type &value) {
  return AVLTree<Key, T>::insert(value.first, value.second);
}

template<typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  iterator it = find(key);

  if (it != end()) {
    it->return_value() = obj;
    return std::make_pair(it, false);
  } else {
    return insert(std::make_pair(key, obj));
  }
}

template<typename Key, typename T>
void map<Key, T>::merge(map &other) {
  AVLTree<Key, T>::merge(other);
}

} // namespace s21




#endif //CPP2_S21_CONTAINERS_2_S21_MAP_H
