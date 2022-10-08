#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace s21 {

template <class T>
class Node {
 public:
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;

  T value;

  explicit Node(const T &value) : value(value) {}
};

template <class T>
class SetIterator {
 public:
  explicit SetIterator(Node<T>* node) : node(node) {}

  T &value() const { return node->value; }

  void operator++() { increase(); }
  void operator++(int) { increase(); }
  void operator--() { decrease(); }
  void operator--(int) { decrease(); }

 protected:
  Node<T>* node;

 private:
  void increase() {
    if (node = nullptr) return;

    if (node->right != nullptr) {
      node = node->right;
      while (node->left != nullptr) {
       node = node->left;
      }
    } else {
      if (node->parent != nullptr && node->parent->right == node) {
        while (node->parent != nullptr && node->parent->left != node) {
          node = node->parent;
        }
      }
      node = node->parent;
    }
  }

  void decrease() {
    if (node == nullptr) return;

    if (node->left != nullptr) {
      node = node->left;
      while (node->right != nullptr) {
        node = node->right;
      }
    } else {
      if (node->parent != nullptr && node->parent->left == node) {
        while (node->parent != nullptr && node->parent->right != node) {
          node = node->parent;
        }
      }
      node = node->parent;
    }
  }

};

template <class T>
class SetConstIterator : public SetIterator<T> {
 public:
  explicit SetConstIterator(Node<T>* node) : SetIterator<T>(node) {}

  const T value() const { return SetIterator<T>::node->value }
};

template <class T>
class set {

 public:

  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = SetIterator<T>;
  using const_iterator = SetConstIterator<T>;
  using size_type = size_t;

 private:
  const double lLong_ = 1e+9; 

  size_type size_ = 0;
  size_type max_size_ = lLong_ / sizeof(value_type);
  Node<T>* root_ = nullptr;
};

}

#endif  // SRC_S21_SET_H_