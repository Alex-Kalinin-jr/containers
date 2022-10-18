#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <stdexcept>
#include <initializer_list>
#include <utility>

namespace s21 {


template <class Key, class T>
class Node {
public:
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;

  T value;
  const Key key;

  explicit Node(Key key, const T &value) : value(value), key(key) {}
};

template <class Key, class T>
class MapIterator {
public:

  explicit MapIterator(Node<Key,T>* node) : node(node) {}

  T& value() { return node->value; }
  const Key key() const { return node->key; }

  void operator++() { increase(); }
  void operator++(int) { increase(); }
  void operator--() { decrease(); }
  void operator--(int) { decrease(); }
  bool operator==(const MapIterator& other) { return node == other.node; }
  bool operator!=(const MapIterator& other) { return node != other.node; }


protected:
  Node<Key,T>* node;

private:

  void increase() {
    if (node == nullptr) return;

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

template <class Key, class T>
class MapConstIterator : public MapIterator<Key, T> {
public:
  explicit MapConstIterator(Node<Key, T>* node) : MapIterator<Key, T>(node) {}

  const Key key() const { return MapIterator<Key, T>::node->key; }
  const T value() const { return MapIterator<Key, T>::node->key; }

  bool operator==(const MapConstIterator& other) { return MapIterator<Key, T>::node == other.node; }
  bool operator!=(const MapConstIterator& other) { return MapIterator<Key, T>::node != other.node; }
};


template <class Key, class T>
class map {
public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator<Key, T>;
  using const_iterator = MapConstIterator<Key, T>;
  using size_type = size_t;

  map() {}

  map(std::initializer_list<value_type> const &items) {
    for (auto it : items) {
      insert(it);
    }
  }

  map(const map &m) : size_(m.size_) {
    CopyTree(m.root_);
  }

  map(map &&m) : size_(m.size_), root_(m.root_) {
    m.size_ = 0;
    m.root_ = nullptr;
  }

  ~map() { DeleteTree(root_); }

  operator=(map &&m) {
    if (this != &m) {
      size_ = m.size_;
      CopyTree(m.root_);
    }
  }

  T& at(const Key& key) {
    Node<Key,T>* node = root_;
    while (key != node->key) {
      if (key < node->key) {
        if (node->key != nullptr ) {
          node = node->left;
        } else {
          throw std::out_of_range("index not found!");
        }
      } else {
        if (node->key != nullptr) {
          node = node->right;
        } else {
          throw std::out_of_range("index not found!");
        }
      }
    }
    return node->value;
  }

  T& operator[](const Key& key) {
    if (!contains(key)) {
      std::pair<iterator, bool> tmp = insert(key, T);
      iterator it = tmp.first;
      return it.value();
    } else {
      return at(key);
    }
  }

  iterator begin() {
    Node<Key, T>* node = root_;
    while (node != nullptr && node->left != nullptr) {
      node = node->left;
    }
    return iterator(node);
  }

  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() { return begin(); }
  const_iterator cend() { return end(); }

  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() { return max_size_; }


  void clear() {
    DeleteTree(root_);
    root_ = nullptr;
    size_ = 0;
  }
  std::pair<iterator, bool> insert(const value_type& value) {
    return insert(value.first, value.second);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    if (size_ >= max_size_) {
      return std::make_pair(iterator(nullptr), false);
    }
    Node<Key, T>* node = new Node<Key, T>(key, obj);
    std::pair<iterator, bool> result = std::make_pair(iterator(node), true);
    ++size_;

    if(root_ == nullptr) {
      root_ = node;
    } else {
      Node<Key, T>* tmp = root_;
      while(tmp != nullptr) {
        if (key < tmp->key) {
          if (tmp->left == nullptr) {
            tmp->left = node;
            node->parent = tmp;
            break;
          } else {
            tmp = tmp->left;
          }
        } else if (key > tmp->key) {
          if (tmp->right == nullptr) {
            tmp->right = node;
            node->parent = tmp;
            break;
          } else {
            tmp = tmp->right;
          }
        } else {
          result = std::make_pair(iterator(nullptr), false);
          --size_;
          delete node;
          break;
        }
      }
    }
    return result;
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    if (size_ >= max_size_) {
      return std::make_pair(iterator(nullptr), false);
    }
    Node<Key, T>* node = new Node<Key, T>(key, obj);
    std::pair<iterator, bool> result = std::make_pair(iterator(node), true);
    ++size_;

    if(root_ == nullptr) {
      root_ = node;
    } else {
      Node<Key, T>* tmp = root_;
      while(tmp != nullptr) {
        if (key < tmp->key) {
          if (tmp->left == nullptr) {
            tmp->left = node;
            node->parent = tmp;
            break;
          } else {
            tmp = tmp->left;
          }
        } else if (key > tmp->key) {
          if (tmp->right == nullptr) {
            tmp->right = node;
            node->parent = tmp;
            break;
          } else {
            tmp = tmp->right;
          }
        } else {
          tmp->value = node->value;
          result = std::make_pair(iterator(tmp), true);
          --size_;
          delete node;
          break;
        }
      }
    }
    return result;
  }

  void erase(iterator pos) {
    Node<Key, T>* node = root_;
    while (node != nullptr && node->key != pos.key()) {
      if (pos.key() < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }

    if (node != nullptr) {
      if (node->left == nullptr && node->right == nullptr) {
        if (node->parent != nullptr) {
          if (node->parent->left == node) {
            node->parent->left = nullptr;
          }
          if (node->parent->right == node) {
            node->parent->right = nullptr;
          }
        } else {
          root_ = nullptr;
        }
      } else if (node->left == nullptr) {
        if (node->parent != nullptr) {
          if (node->parent->left == node) {
            node->parent->left = node->right;
          }
          if (node->parent->right == node) {
            node->parent->right = node->right;
          }
          node->right->parent = node->parent;
        } else {
          node->right->parent = nullptr;
          root_ = node->right;
        }
      } else if (node->right == nullptr) {
        if (node->parent != nullptr) {
          if (node->parent->left == node) {
            node->parent->left = node->left;
          }
          if (node->parent->right == node) {
            node->parent->right = node->left;
          }
          node->left->parent = node->parent;
        } else {
          node->left->parent = nullptr;
          root_ = node->left;
        }
      } else {
        Node<Key, T>* tmp = node->right;
        while (tmp->left != nullptr) {
          tmp = tmp->left;
        }
        tmp->left = node->left;
        tmp->left->parent = tmp;
        if (node->parent != nullptr) {
          if (node->parent->left == node) {
            node->parent->left = node->right;
          }
          if (node->parent->right == node) {
            node->parent->right = node->right;
            node->right->parent = node->parent;
          }
        } else {
          node->right->parent = nullptr;
          root_ = node->right;
        }
      }
      --size_;
      delete node;
    }
  }

bool contains(const Key& key) {
  Node<Key, T>* node = root_;
    while (node != nullptr && node->key != key) {
      if (key < node->key) {
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return node != nullptr;
}

void swap(map& other) {
    if (this != &other) {
      root_ = other.root_;
      size_ = other.size_;
      other.size_ = 0;
      other.root_ = nullptr;
    }
  }

void merge(map& other) {
  for (iterator it = other.begin(); it != other.end();) {
    if (!contains(it.key())) {
      insert(it.key(), it.value());
      other.erase(it);
      it = other.begin();
    } else {
      ++it;
    }
  }
}



private:
  const double lLong_ = 1e+9;

  size_type size_ = 0;
  size_type max_size_ = lLong_ / sizeof(value_type);
  Node<Key, T>* root_ = nullptr;

  void CopyTree(Node<Key, T>* node) {
    if (node == nullptr) return;

    insert(node->key, node->value);

    if (node->left != nullptr) {
      CopyTree(node->left);
    }
    if (node->right != nullptr) {
      CopyTree(node->right);
    }
  }

  void DeleteTree(Node<Key, T>* node) {
    if (node == nullptr) return;

    if (node->left != nullptr) {
      DeleteTree(node->left);
    }
    if (node->right != nullptr) {
      DeleteTree(node->right);
    }
    delete node;
  }
};


};


#endif // SRC_S21_MAP_H_