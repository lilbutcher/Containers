//
// Created by Hotah Mireille on 4/12/24.
//

#ifndef CPP2_S21_CONTAINERS_2_SRC_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_2_SRC_SET_S21_SET_H_

#include "../AVLTree/AVLTree.h"
namespace s21 {

template<typename Key>
class set : public AVLTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = typename AVLTree<Key, Key>::Iterator;
  using const_iterator = typename AVLTree<Key, Key>::ConstIterator;
  using size_type = size_t;

  set() : AVLTree<Key, Key>() {};
  set(std::initializer_list<value_type> const &items);
  set(const set &other) : AVLTree<Key, Key>(other) {};
  set(set &&other) noexcept : AVLTree<Key, Key>(std::move(other)){};
  set &operator=(set &&other);
  set &operator=(const set &other);
  ~set() = default;

  iterator begin();
  iterator end();


  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void swap(set& other);
  void merge(set& other);

  bool contains(const Key& key);
};



template<typename Key>
bool set<Key>::contains(const Key& key) {
  return AVLTree<Key, Key>::find(key) != nullptr;
}

template <typename Key>
set<Key>::set(const std::initializer_list<value_type> &items) {
  for (const auto& item : items) {
    insert(item);
  }
}

template<typename Key>
void set<Key>::merge(set<Key>& other) {
  AVLTree<Key, Key>::merge(other);
}

template<typename Key>
void set<Key>::swap(set<Key>& other) {
  AVLTree<Key, Key>::swap(other);
}

template<typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(const typename set<Key>::value_type& value) {
  Key key = value;
  std::pair<typename AVLTree<Key, Key>::Iterator, bool> result = AVLTree<Key, Key>::insert(key, value);
  return std::make_pair(typename set<Key>::iterator(result.first), result.second);
}


template<typename Key>
void set<Key>::clear() {
  if (this->root != nullptr) {
    AVLTree<Key, Key>::clear(this->root); // Удаляем аргумент из вызова clear
    this->root = nullptr;
  }
}

template<typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return set<Key>::iterator(AVLTree<Key, Key>::findMin(AVLTree<Key, Key>::root));
}

template<typename Key>
typename set<Key>::iterator set<Key>::end() {
  return set<Key>::iterator(AVLTree<Key, Key>::findMax(AVLTree<Key, Key>::root));
}


template<typename Key>
set<Key> &set<Key>::operator=(set &&other)  {
  if ( this != &other){
    AVLTree<Key, Key>::operator=(std::move(other));
  }
  return *this;
}

template<typename Key>
set<Key> &set<Key>::operator=(const set &other) {
  if ( this != &other){
    AVLTree<Key, Key>::operator=(std::move(other));
  }
  return *this;
}


} // namespace s21

#endif //CPP2_S21_CONTAINERS_2_SRC_SET_S21_SET_H_
