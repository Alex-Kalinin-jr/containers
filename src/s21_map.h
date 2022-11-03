#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <utility>
#include <climits>
#include <vector>


namespace s21 {


template <class Key, class T>
class Node {
public:
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int balance = 0;

  T value;
  const Key key;

  explicit Node(Key key, const T &value) : value(value), key(key) {}
  Node() : key(0) {}
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
  T &operator*() const {
        if (node != nullptr && node->parent != nullptr &&
            node->parent->right == node && node->parent->key > node->key) {
            return node->parent->value;
        }
        if (node != nullptr) {
            return node->value;
        } else {
            throw std::out_of_range("out of range");
        }
    }
  int show_balance() const { return node->balance; }
  Node<Key, T> *get_node() const { return node; }

protected:
  Node<Key,T>* node;

void increase() {
        if (node == nullptr) return;

        if (node->parent == nullptr && node->right->key < node->key) {
            node = node->right;
            return;
        }

        // Проверка на end, чтобы итератор не уходил в nullptr
        if (node->parent != nullptr && node->parent->right == node &&
            node->parent->key > node->key)
            return;
        if (node->parent != nullptr && node->key == node->parent->key) {
            node = node->parent;
            return;
        }
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
        bool end = false;

        if (node->parent != nullptr && node->parent->right == node &&
            node->parent->key > node->key) {
            node = node->parent;
            end = true;
        }

        if (node->left != nullptr && (!end)) {
            node = node->left;
            if (node->parent->key == node->key) {
                return;
            }
            while (node->right != nullptr) {
                node = node->right;
            }
        } else if (!end) {
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
  const T value() const { return MapIterator<Key, T>::node->value; }

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

   public:
    map() {}

    map(std::initializer_list<value_type> const& items) {
        for (auto it : items) {
            insert(it);
        }
    }

    map(const map& m) { CopyTree(m.root_); }

    map(map&& m) {
        size_ = m.size_;
        root_ = m.root_;
        end_ = m.end_;
        m.size_ = 0;
        m.root_ = nullptr;
        m.end_ = nullptr;
    }

    ~map() { DeleteTree(root_); }

    void operator=(map&& m) {
        if (this != &m) {
            size_ = m.size_;
            CopyTree(m.root_);
        }
    }

    T& at(const Key& key) {
    Node<Key,T>* node = root_;
    while (key != node->key) {
      if (key < node->key) {
        if (node->left != nullptr) {
          node = node->left;
        } else {
          throw std::out_of_range("index not found!");
        }
      } else {
        if (node->right != nullptr && node->right != end_) {
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
      std::pair<iterator, bool> tmp = insert(key, T());
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

    iterator end() { return iterator(end_); }
    const_iterator cbegin() { return begin(); }
    const_iterator cend() { return end(); }

    bool empty() { return size_ == 0; }
    size_type size() { return size_; }
    size_type max_size() { return max_size_; }

    void clear() {
        DeleteTree(root_);
        size_ = 0;
        root_ = nullptr;
        end_ = nullptr;
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

        if (root_ == nullptr) {
            end_ = new Node<Key, T>;
            node->right = end_;
            node->right->parent = node;
            root_ = node;
        } else {
            Node<Key, T>* tmp = root_;
            while (tmp != end_ || tmp != nullptr) {
                if (key < tmp->key) {
                    if (tmp->left == nullptr) {
                        tmp->left = node;
                        node->parent = tmp;
                        break;
                    } else {
                        tmp = tmp->left;
                    }
                } else if (key > tmp->key) {
                    if (tmp->right == end_) {
                        tmp->right = node;
                        node->parent = tmp;
                        end_->parent = node;
                        node->right = end_;
                        break;
                    } else if (tmp->right == nullptr) {
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
        Node<Key, T>* buff = result.first.get_node();
        balancing(buff);
        return result;
    }

    std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
        if (size_ >= max_size_) {
            return std::make_pair(iterator(nullptr), false);
        }
        Node<Key, T>* node = new Node<Key, T>(key, obj);
        std::pair<iterator, bool> result = std::make_pair(iterator(node), true);
        ++size_;

        if (root_ == nullptr) {
            end_ = new Node<Key, T>;
            node->right = end_;
            node->right->parent = node;
            root_ = node;
        } else {
            Node<Key, T>* tmp = root_;
            while (tmp != end_ || tmp != nullptr) {
                if (key < tmp->key) {
                    if (tmp->left == nullptr) {
                        tmp->left = node;
                        node->parent = tmp;
                        break;
                    } else {
                        tmp = tmp->left;
                    }
                } else if (key > tmp->key) {
                    if (tmp->right == end_) {
                        tmp->right = node;
                        node->parent = tmp;
                        end_->parent = node;
                        node->right = end_;
                        break;
                    } else if (tmp->right == nullptr) {
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
        Node<Key, T>* buff = result.first.get_node();
        balancing(buff);
        return result;
    }

    void erase(iterator pos) {
        if (pos == end()) {
            throw std::out_of_range("invalid pointer");
        }
        Node<Key, T>* node = pos.get_node();
        if ((node != nullptr && node != end_) ||
            (node->left == nullptr && node->right == nullptr)) {
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
                    delete end_;
                    end_ = nullptr;
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
            } else if (node->right == nullptr || node->right == end_) {
                if (node->parent != nullptr) {
                    if (node->parent->left == node) {
                        node->parent->left = node->left;
                    }
                    if (node->parent->right == node) {
                        node->parent->right = node->left;
                    }
                    node->left->parent = node->parent;
                    node->left->right = end_;
                    node->left->right->parent = node->left;
                    node->parent = nullptr;
                } else {
                    node->left->parent = nullptr;
                    if (node->left->right != nullptr) {
                        Node<Key,T>* tmp = node->left->right;
                        while(tmp->right != nullptr) {
                            tmp = tmp->right;
                        }
                        tmp->right = node->right;
                        node->right->parent = tmp;
                        root_ = node->left; 
                    } else {
                        node->left->right = node->right;
                        node->left->right->parent = node->left;
                        root_ = node->left;
                    }
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
                        node->right->parent = node->parent;
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
            set_balance_for_all();
        }
    }

    void swap(map& other) {
        if (this != &other) {
            Node<Key, T>* buff = other.root_;
            size_type buff_size = other.size_;
            Node<Key, T>* buff_end = other.end_;
            other.size_ = size_;
            other.root_ = root_;
            other.end_ = end_;
            root_ = buff;
            end_ = buff_end;
            size_ = buff_size;
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
    template <class... Args>
    std::vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    std::vector<std::pair<iterator, bool>> result{};
    std::initializer_list<std::pair<Key, T>> arguments = {{args...}};
    for (auto item : arguments) {
      result.push_back(insert(value_type(item)));
    }
    return result;
    }

   protected:
    Node<Key, T>* end_ = nullptr;
    Node<Key, T>* root_ = nullptr;
    size_type size_ = 0;
    size_type max_size_ = LLONG_MAX / sizeof(value_type);

    void CopyTree(Node<Key, T>* node) {
        if (node == nullptr || node == end_) return;
        bool end = false;
        if (node->parent != nullptr && node->parent->right == node &&
            node->key < node->parent->key) {
            end = true;
        }
        if (!end) {
            insert(node->key, node->value);
            if (node->left != nullptr) {
                CopyTree(node->left);
            }
            if (node->right != nullptr && node->right != end_) {
                CopyTree(node->right);
            }
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

    void r_rotate(Node<Key, T>* chunck) {
        if (chunck == root_) root_ = chunck->left;
        if (chunck != root_) {
            if (chunck->parent->left == chunck)
                chunck->parent->left = chunck->left;
            if (chunck->parent->right == chunck)
                chunck->parent->right = chunck->left;
        }
        chunck->left->parent = (chunck == root_) ? nullptr : chunck->parent;
        chunck->parent = chunck->left;
        if (chunck->left->right != nullptr)
            chunck->left->right->parent = chunck;
        Node<Key, T>* buff = chunck->left->right;
        chunck->left->right = chunck;
        chunck->left = buff;
    }

    void l_rotate(Node<Key, T>* chunck) {
        if (chunck == root_) root_ = chunck->right;
        if (chunck != root_) {
            if (chunck->parent->left == chunck)
                chunck->parent->left = chunck->right;
            if (chunck->parent->right == chunck)
                chunck->parent->right = chunck->right;
        }
        chunck->right->parent = (chunck == root_) ? nullptr : chunck->parent;
        chunck->parent = chunck->right;
        if (chunck->right->left != nullptr) {
            chunck->right->left->parent = chunck;
        }
        Node<Key,T>* buff = chunck->right->left;
        chunck->right->left = chunck;
        chunck->right = buff;
    }

    void set_balance(Node<Key, T>* chunck) {
        chunck->balance = height(chunck->right) - height(chunck->left);
    }

    void set_balance_for_all() {
        iterator itr1 = begin();
        while (itr1.get_node() != end_) {
            set_balance(itr1.get_node());
            ++itr1;
        }
    }

    int height(Node<Key, T>* chunck) {
        if (chunck == nullptr || chunck == end_) return 0;
        int h_left = height(chunck->left);
        int h_right = height(chunck->right);
        if (h_left > h_right) {
            return h_left + 1;
        } else {
            return h_right + 1;
        }
    }

    Node<Key, T>* get_root() { return root_; }

    void balancing(Node<Key, T>* buff) {
        set_balance_for_all();
        while (buff != root_) {
            Node<Key, T>* new_buff = buff->parent;
            if (buff->balance > 1) {
                new_buff = buff->right;
                if (buff->right->balance < 0) r_rotate(buff->right);
                l_rotate(buff);
            } else if (buff->balance < -1) {
                new_buff = buff->left;
                if (buff->left->balance > 0) l_rotate(buff->left);
                r_rotate(buff);
            }
            buff = new_buff;
            set_balance_for_all();
        }
    }
};


}


#endif // SRC_S21_MAP_H_