//
// Created by qwe on 15.03.24.
//

#ifndef CPP2_S21_CONTAINERS_2_SRC_AVLTREE_AVLTREE_H_
#define CPP2_S21_CONTAINERS_2_SRC_AVLTREE_AVLTREE_H_

#include <iostream>
#include <algorithm>
#include <limits>
#include <utility>

template<typename Key, typename Value>
class AVLTree {
 public:
  struct Node {
    Key key;
    Value value;
    Node *left;
    Node *right;
    Node *parent;
    int height;
    std::pair<const Key, Value>& operator*() { return std::make_pair(this->key, this->value); }
  };



  class Iterator;
  class ConstIterator;

  using reference = Value &;
  using const_reference = const Value &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    friend class AVLTree<Key, Value>;
    Node *iter_node;
    Node *iter_past_node;
    Iterator() : iter_node(nullptr), iter_past_node(nullptr) {};
    Iterator(Node *node, Node *past_node = nullptr) : iter_node(node), iter_past_node(past_node) {};
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
//    reference operator*();
    bool operator==(const iterator &it);
    bool operator!=(const iterator &it);

    std::pair<const Key, Value> operator->() { return *iter_node; }


 //   std::pair<const Key, T>* operator->() { return &(this->node_->value_); }

    Node *MoveForward(Node *node);
    Node *MoveBack(Node *node);
  };


  class ConstIterator {
   public:
    friend class AVLTree<Key, Value>;
    const Node *iter_node;
    const Node *iter_past_node;
    ConstIterator() : iter_node(nullptr), iter_past_node(nullptr) {};
    ConstIterator(const Node *node, const Node *past_node = nullptr) : iter_node(node), iter_past_node(past_node) {};
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    const_iterator operator--(int);
    const_reference operator*();
    bool operator==(const const_iterator &it);
    bool operator!=(const const_iterator &it);

    const Node *MoveForward(const Node *node);
    const Node *MoveBack(const Node *node);
  };

  Node *root;
  AVLTree() : root(nullptr) {}
  ~AVLTree() {
    if (root != nullptr) {
      clear(root);
    }
  }
  AVLTree(const AVLTree &m);
  AVLTree(AVLTree &&m);
  AVLTree &operator=(AVLTree &&other);

  AVLTree(std::initializer_list<std::pair<const Key, Value>> const &items);

  void clear(Node *node);
  int getHeight(Node *node);
  int bFactor(Node *node);
  void setHeight(Node *node);
  void leftRotate(Node *node);
  void rightRotate(Node *node);
  void balance(Node *node);
  std::pair<Iterator, bool> insert(const Key &key, const Value &value);
  Node *find(const Key &key);
  static Node *findMax(Node *node);
  static Node *findMin(Node *node);
  bool remove(const Key &key);
  void erase(Iterator pos);
  bool removeNode(Node *remove);
  void swap(AVLTree &other);
  void merge(AVLTree &other);
  size_t RecursiveSize(Node* node);
  size_type size();
  size_type max_size();
  Node *copytree(Node *node, Node *parent);
  Node *findMinFreeList(Node *node);
  bool empty();

};

//template<typename Key, typename Value>
//const Key& AVLTree<Key, Value>::Iterator::first() {
//  return iter_node->key;
//}
//
//template<typename Key, typename Value>
//Value& AVLTree<Key, Value>::Iterator::second() {
//  return iter_node->value;
//}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::ConstIterator::operator==(const ConstIterator &it) {
  return iter_node == it.iter_node;
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::ConstIterator::operator!=(const ConstIterator &it) {
  return !(*this == it);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::ConstIterator &AVLTree<Key, Value>::ConstIterator::operator--() {
  iter_node = MoveBack(iter_node);
  return *this;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::ConstIterator AVLTree<Key, Value>::ConstIterator::operator--(int) {
  ConstIterator temp = *this;
  iter_node = MoveBack(iter_node);
  return temp;
}

template<typename Key, typename Value>
const typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::ConstIterator::MoveBack(const Node* node) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->left != nullptr) {
    return findMax(node->left);
  }



  const Node* parent = node->parent;
  while (parent != nullptr && node == parent->left) {
    node = parent;
    parent = parent->parent;
  }

  return parent;
}

//template<typename Key, typename Value>
//const Value& AVLTree<Key, Value>::ConstIterator::operator*() {
//  return iter_node->value;
//}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::ConstIterator &AVLTree<Key, Value>::ConstIterator::operator++() {
  iter_node = MoveForward(iter_node);
  return *this;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::ConstIterator AVLTree<Key, Value>::ConstIterator::operator++(int) {
  ConstIterator temp = *this;
  iter_node = MoveForward(iter_node);
  return temp;
}

template<typename Key, typename Value>
const typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::ConstIterator::MoveForward(const Node *node) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->right != nullptr) {
    return findMin(node->right);
  }

  const Node *parent = node->parent;
  while (parent != nullptr && node == parent->right) {
    node = parent;
    parent = parent->parent;
  }

  return parent;
}


template<typename Key, typename Value>
bool AVLTree<Key, Value>::empty(){
  if (root == nullptr){
    return true;
  }
  return false;
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::getHeight(Node *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::clear(Node *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::bFactor(Node *node) {
  return getHeight(node->right) - getHeight(node->left);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::setHeight(Node *node) {
  node->height = std::max(getHeight(node->right), getHeight(node->left)) + 1;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::leftRotate(Node *node) {
  Node *newParentNode = node->right;
  node->right = newParentNode->left;
  if (newParentNode->left != nullptr) {
    newParentNode->left->parent = node;
  }
  newParentNode->parent = node->parent;
  if (node->parent == nullptr) {
    root = newParentNode;
  } else if (node == node->parent->left) {
    node->parent->left = newParentNode;
  } else {
    node->parent->right = newParentNode;
  }
  newParentNode->left = node;
  node->parent = newParentNode;

  setHeight(node);
  setHeight(newParentNode);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::rightRotate(Node *node) {
  Node *newParentNode = node->left;
  node->left = newParentNode->right;
  if (newParentNode->right != nullptr) {
    newParentNode->right->parent = node;
  }
  newParentNode->parent = node->parent;
  if (node->parent == nullptr) {
    root = newParentNode;
  } else if (node == node->parent->right) {
    node->parent->right = newParentNode;
  } else {
    node->parent->left = newParentNode;
  }
  newParentNode->right = node;
  node->parent = newParentNode;

  setHeight(node);
  setHeight(newParentNode);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::balance(Node *node) {
  while (node != nullptr) {
    setHeight(node);
    int balanceFactor = bFactor(node);
    if (balanceFactor == -2) {
      if (bFactor(node->left) > 0) {
        leftRotate(node->left);
      }
      rightRotate(node);
    } else if (balanceFactor == 2) {
      if (bFactor(node->right) < 0) {
        rightRotate(node->right);
      }
      leftRotate(node);
    }
    node = node->parent;
  }
}

template<typename Key, typename Value>
std::pair<typename AVLTree<Key, Value>::Iterator, bool> AVLTree<Key, Value>::insert(const Key &key,
                                                                                    const Value &value) {
  if (root == nullptr) {
    Node *newNode = new Node{key, value, nullptr, nullptr, nullptr, 1};
    root = newNode;
    return std::make_pair(Iterator(newNode), true);
  }

  Node *current = root;
  Node *parent = nullptr;

  while (current) {
    parent = current;
    if (key < current->key) {
      current = current->left;
    } else if (key > current->key) {
      current = current->right;
    } else {
      return std::make_pair(Iterator(current), false);
    }
  }

  Node *newNode = new Node{key, value, nullptr, nullptr, parent, 1};
  if (key < parent->key) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  balance(newNode);

  return std::make_pair(Iterator(newNode), true);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::find(const Key &key) {
  Node *current = root;
  while (current != nullptr) {
    if (key < current->key) {
      current = current->left;
    } else if (key > current->key) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::findMax(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->right == nullptr) {
    return node;
  }
  return findMax(node->right);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::findMin(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left == nullptr) {
    return node;
  }
  return findMin(node->left);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(Iterator pos) {
  removeNode(pos.iter_node);
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::removeNode(Node *remove) {
  if (remove->left == nullptr && remove->right == nullptr) {
    if (remove->parent) {
      if (remove == remove->parent->left) {
        remove->parent->left = nullptr;
      } else {
        remove->parent->right = nullptr;
      }
    } else {
      root = nullptr;
    }

    delete remove;
    return true;
  }

  if (remove->left == nullptr && remove->right != nullptr) {
    if (remove == remove->parent->left) {
      remove->parent->left = remove->right;
    } else {
      remove->parent->right = remove->right;
    }
    delete remove;
    return true;
  } else if (remove->left != nullptr && remove->right == nullptr) {
    if (remove == remove->parent->left) {
      remove->parent->left = remove->left;
    } else {
      remove->parent->right = remove->left;
    }
    delete remove;
    return true;
  }

  if (remove->left != nullptr && remove->right != nullptr) {
    Node *exchange = findMax(remove->left);

    remove->key = exchange->key;
    remove->value = exchange->value;

    if (exchange == exchange->parent->left) {
      exchange->parent->left = exchange->left;
    } else {
      exchange->parent->right = exchange->left;
    }

    if (exchange->left != nullptr) {
      exchange->left->parent = exchange->parent;
    }

    delete exchange;
    balance(remove->left);
  }

  balance(remove->parent);

  return true;
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::remove(const Key &key) {
  Node *remove = find(key);
  if (remove == nullptr) {
    return false;
  }
  return removeNode(remove);;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::Iterator::MoveForward(AVLTree::Node *node) {
  if (node->right != nullptr) {
    return findMin(node->right);
  }

  if (node->parent->left == node) {
    return node->parent;
  }

  Node *current = node;
  while (current->parent != nullptr && node->key > current->parent->key) {
    current = current->parent;
  }

  if (node->key > current->key && current->parent == nullptr) {
    return node;
  }

  current = current->parent;
  return current;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::Iterator::MoveBack(AVLTree::Node *node) {
  if (node->left != nullptr) {
    return findMax(node->left);
  }

  if (node->parent->right == node) {
    return node->parent;
  }

  Node *current = node;
  while (current->parent != nullptr && node->key < current->parent->key) {
    current = current->parent;
  }

  if (node->key < current->key && current->parent == nullptr) {
    return node;
  }

  current = current->parent;
  return current;

}

template<typename Key, typename Value>
void AVLTree<Key, Value>::swap(AVLTree &other) {
  std::swap(root, other.root);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::merge(AVLTree &other) {
  if (other.root == nullptr) {
    return;
  } else if (root == nullptr) {
    Node *newNode = new Node{other.root->key, other.root->value, other.root->left, other.root->right, nullptr, 1};
    root = newNode;
    other.root = nullptr;
    return;
  }

  Node *it_minor = other.findMinFreeList(other.root);
  int flag = 0;

  for (; flag != 2 && flag != 3;) {

    int flagtv = 0;
    Node *it = it_minor;
    Node *current = root;
    Node *parent = nullptr;
    it_minor = it_minor->parent;

    while (current) {
      parent = current;
      if (it->key < current->key) {
        current = current->left;
      } else if (it->key > current->key) {
        current = current->right;
      } else {
        Node *it_parent = it->parent;
        Node *newNode = new Node{it->key, it->value, nullptr, nullptr, nullptr, 1};
        delete it; // разобраться как точно удалять
        it = it_parent;
        flagtv++;
        if (it_minor == nullptr) {

        } else if (it_minor->key > newNode->key) {
          it_minor->left = nullptr;
        } else if (it_minor->key < newNode->key) {
          it_minor->right = nullptr;
        }
        delete newNode;
        break;
      }
    }

    if (it == nullptr) {
      other.root = nullptr;
      flag = 2;
      continue;
    } else if (flagtv > 0) {
      it_minor = findMinFreeList(it_minor);
      continue;
    }

    if (it->key < parent->key) {
      parent->left = it;
      it->parent = parent;

    } else {
      parent->right = it;
      it->parent = parent;
    }

    if (it_minor == nullptr) {
      flag = 2;
      other.root = nullptr;
    } else if (it_minor->key > it->key) {
      it_minor->left = nullptr;
    } else if (it_minor->key < it->key) {
      it_minor->right = nullptr;
    }

    balance(it);

    it_minor = findMinFreeList(it_minor);
    if (flag == 1) {
      other.root = nullptr;
    }
    if (it_minor == other.root) {
      flag++;
    }
  }
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator &AVLTree<Key, Value>::Iterator::operator++() {
  iter_node = MoveForward(iter_node);
  return *this;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::Iterator::operator++(int) {
  iterator temp = *this;
  iter_node = MoveForward(iter_node);
  return temp;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator &AVLTree<Key, Value>::Iterator::operator--() {
  iter_node = MoveBack(iter_node);
  return *this;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::Iterator::operator--(int) {
  iterator temp = *this;
  iter_node = MoveBack(iter_node);
  return temp;
}

//template<typename Key, typename Value>
//typename AVLTree<Key, Value>::reference AVLTree<Key, Value>::Iterator::operator*() {
//  if (iter_node == nullptr) {
//    throw std::runtime_error("Dereferencing end() iterator");
//  }
//  return iter_node->value;
//}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator==(const Iterator &it) {
  return iter_node == it.iter_node && iter_past_node == it.iter_past_node;
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator!=(const Iterator &it) {
  return iter_node != it.iter_node || iter_past_node != it.iter_past_node;
}

template <typename Key, typename Value>
size_t AVLTree<Key, Value>::RecursiveSize(AVLTree::Node *node) {
  if (node == nullptr) return 0;
  size_t left_size = RecursiveSize(node->left);
  size_t right_size = RecursiveSize(node->right);
  return 1 + left_size + right_size;
}

template<typename Key, typename Value>
size_t AVLTree<Key, Value>::size() {
  return RecursiveSize(root);
}

template<typename Key, typename Value>
size_t AVLTree<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(const AVLTree &m) {
  root = copytree(m.root, nullptr);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::copytree(AVLTree::Node *node, AVLTree::Node *parent) {
  if (!node) {
    return nullptr;
  }
  Node *newNode = new Node{node->key, node->value, nullptr, nullptr, parent, node->height};
  newNode->left = copytree(node->left, newNode);
  newNode->right = copytree(node->right, newNode);
  return newNode;
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node *AVLTree<Key, Value>::findMinFreeList(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left != nullptr || node->right != nullptr) {
    if (node->left != nullptr) {
      return findMinFreeList(node->left);
    } else {
      return findMinFreeList(node->right);
    }
  } else {
    return node;
  }
}

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(AVLTree &&m) {
  root = m.root;
  m.root = nullptr;
}

template<typename Key, typename Value>
AVLTree<Key, Value> &AVLTree<Key, Value>::operator=(AVLTree &&m) {
  if (this != &m) {
    if (root) {
      clear(root);
    }
    root = m.root;
    m.root = nullptr;
  }
  return *this;
}

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(std::initializer_list<std::pair<const Key, Value>> const &items) {
  root = nullptr;
  for (const auto &item : items) {
    insert(item.first, item.second);
  }
}

#endif  // CPP2_S21_CONTAINERS_2_SRC_AVLTREE_AVLTREE_H_
