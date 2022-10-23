#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <climits>
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

    explicit Node(const T& value) : value(value) {}
};

template <class T>
class SetIterator {
   public:
    explicit SetIterator(Node<T>* node) : node(node) {}

    T& value() const { return node->value; }

    void operator++() { increase(); }
    void operator++(int) { increase(); }
    void operator--() { decrease(); }
    void operator--(int) { decrease(); }
    bool operator==(const SetIterator& other) { return node == other.node; }
    bool operator!=(const SetIterator& other) { return node != other.node; }
    T& operator*() const {
        if (node != nullptr) {
            return node->value;
        } else {
            throw std::out_of_range("aaaa");
        }
    }

    Node<T>* get_node() const { return node; }

   protected:
    Node<T>* node;

    void increase() {
        if (node == nullptr) return;

        if (node->parent != nullptr && node->value == node->parent->value) {
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

        if (node->left != nullptr) {
            node = node->left;
            if (node->parent->value == node->value) {
                return;
            }

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

    const T value() const { return SetIterator<T>::node->value; }

    bool operator==(const SetConstIterator& other) {
        return SetIterator<T>::node == other.node;
    }
    bool operator!=(const SetConstIterator& other) {
        return SetIterator<T>::node != other.node;
    }
};

template <class Key>
class set {
   public:
    using key_type = Key;
    using value_type = Key;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = SetIterator<Key>;
    using const_iterator = SetConstIterator<Key>;
    using size_type = size_t;
    using Sset = set<key_type>;

    set() {}

    set(std::initializer_list<value_type> const& items) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            insert(*it);
        }
    }

    set(const set& s) : size_(s.size_) { CopyTree(s.root_); }

    set(set&& s) : size_(s.size_), root_(s.root_) {
        s.size_ = 0;
        s.root_ = nullptr;
    }

    ~set() { DeleteTree(root_); }

    virtual void operator=(set&& s) {
        if (this != &s) {
            size_ = s.size_;
            CopyTree(s.root_);
        }
    }

    iterator begin() {
        Node<Key>* node = root_;
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
        size_ = 0;
        root_ = nullptr;
    }

    virtual std::pair<iterator, bool> insert(const value_type& value) {
        if (size_ >= max_size_) {
            return std::make_pair(iterator(nullptr), false);
        }
        Node<Key>* node = new Node<Key>(value);
        std::pair<iterator, bool> result = std::make_pair(iterator(node), true);
        ++size_;

        if (root_ == nullptr) {
            root_ = node;
        } else {
            Node<Key>* tmp = root_;
            while (tmp != nullptr) {
                if (value < tmp->value) {
                    if (tmp->left == nullptr) {
                        tmp->left = node;
                        node->parent = tmp;
                        break;
                    } else {
                        tmp = tmp->left;
                    }
                } else if (value > tmp->value) {
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

    virtual void erase(iterator pos) {
        Node<Key>* node = pos.get_node();

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
                Node<Key>* tmp = node->right;
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

    void swap(set& other) {
        if (this != &other) {
            Node<Key>* buff = other.root_;
            size_type buff_size = other.size_;
            other.size_ = size_;
            other.root_ = root_;
            root_ = buff;
            size_ = buff_size;
        }
    }

    virtual void merge(set& other) {
        for (iterator it = other.begin(); it != other.end();) {
            if (!contains(it.value())) {
                insert(it.value());
                other.erase(it);
                it = other.begin();
            } else {
                ++it;
            }
        }
    }

    bool contains(const Key& key) {
        Node<Key>* node = root_;
        while (node != nullptr && node->value != key) {
            if (key < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node != nullptr;
    }

    iterator find(const Key& key) {
        Node<Key>* node = root_;
        while (node != nullptr && node->value != key) {
            if (key < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return iterator(node);
    }

   protected:
    size_type size_ = 0;
    size_type max_size_ = LLONG_MAX / sizeof(value_type);
    Node<Key>* root_ = nullptr;

    void CopyTree(Node<Key>* node) {
        if (node == nullptr) return;

        insert(node->value);

        if (node->left != nullptr) {
            CopyTree(node->left);
        }
        if (node->right != nullptr) {
            CopyTree(node->right);
        }
    }

    void DeleteTree(Node<Key>* node) {
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

template <typename Key>
class s21_Multiset : public set<Key> {
    using node = Node<Key>;
    using Sset = set<Key>;
    using key_type = Key;
    using value_type = Key;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = SetIterator<Key>;
    using const_iterator = SetConstIterator<Key>;
    using size_type = size_t;

   public:
    s21_Multiset() : Sset::set(){};

    s21_Multiset(const s21_Multiset<Key>& ms) : Sset::set(ms){};

    s21_Multiset(std::initializer_list<key_type> const& items) : Sset::set() {
        for (auto it = items.begin(); it != items.end(); ++it) {
            insert(*it);
        }
    };

    s21_Multiset(s21_Multiset<Key>&& ms) : Sset::set(ms){};

    ~s21_Multiset(){};

    // void operator=(s21_Multiset &&s) {
    //     if (this != &s) {
    //         Sset::size_ = s.Sset::size_;
    //         Sset::CopyTree(s.Sset::root_);
    //     }
    // }

    std::pair<iterator, bool> insert(const value_type& value) {
        if (Sset::size_ >= Sset::max_size_) {
            return std::make_pair(iterator(nullptr), false);
        }
        Node<Key>* node = new Node<Key>(value);
        insert_node(node);
        std::pair<iterator, bool> result = std::make_pair(iterator(node), true);
        return result;
    }

    void merge(s21_Multiset& other) {
        iterator it = other.begin();
        for (size_type i = 0; i < other.size_; ++i) {
            insert_node(it.get_node());
            ++it;
        }
        other.root_ = nullptr;
        other.size_ = 0;
    }

    size_type count(const Key& val) {
        size_type i = Sset::size_;
        size_type result = 0;
        iterator itr1 = Sset::begin();
        while (--i != 0) {
            if (val == *itr1) {
                ++result;
            }
            ++itr1;
        }
        return result;
    }

    iterator find(const Key& key) {
        size_type i = Sset::size_;
        iterator itr1 = Sset::begin();
        while (itr1.get_node() != nullptr || i != 0) {
            if (key == *itr1) {
                return itr1;
            }
            ++itr1;
            --i;
        }
        return itr1;
    }

    bool contains(const Key& key) {
        size_type i = Sset::size_;
        iterator itr1 = Sset::begin();
        while (itr1.get_node() != nullptr || i != 0) {
            if (key == *itr1) {
                return true;
            }
            ++itr1;
            --i;
        }
        return false;
    }

    std::pair<iterator, iterator> equal_range(const Key& key) {
        iterator itr1 = Sset::begin();
        while (itr1.get_node() != nullptr || *itr1 != key) {
            ++itr1;
        }
        iterator itr2 = itr1;
        if (itr1.get_node() != nullptr) {
            while (itr2.get_node()->parent != nullptr &&
                   (itr2.get_node()->parent)->value == key) {
                ++itr2;
            }
        }
        std::pair<iterator, iterator> result = std::make_pair(itr1, itr2);
        return result;
    }

   private:
    void insert_node(Node<Key>* node) {
        if (node == nullptr) {
            return;
        }
        ++(Sset::size_);

        if (Sset::root_ == nullptr) {
            Sset::root_ = node;
        } else {
            Node<Key>* tmp = Sset::root_;
            while (tmp != nullptr) {
                if (node->value < tmp->value) {
                    if (tmp->left == nullptr) {
                        tmp->left = node;
                        node->parent = tmp;
                        break;
                    } else {
                        tmp = tmp->left;
                    }
                } else if (node->value > tmp->value) {
                    if (tmp->right == nullptr) {
                        tmp->right = node;
                        node->parent = tmp;
                        break;
                    } else {
                        tmp = tmp->right;
                    }
                } else {
                    if (tmp->left != nullptr) {
                        tmp->left->parent = node;
                        node->left = tmp->left;
                    }
                    tmp->left = node;
                    node->parent = tmp;
                    break;
                }
            }
        }
    }
};
}  // namespace s21

#endif  // SRC_S21_SET_H_