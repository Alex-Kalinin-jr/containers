#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <climits>
#include <cstddef>
#include <initializer_list>
#include <utility>

#include "s21_node.h"
#include "s21_iterator.h"

namespace s21 {

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

    void operator=(set&& s) {
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
    }

    virtual std::pair<iterator, bool> insert(const value_type& value) {
        if (size_ >= max_size_) {
            return std::make_pair(iterator(nullptr), false);
        }
        Node<Key>* node = new Node<Key>(value);
        std::pair<iterator, bool> result = std::make_pair(iterator(node), true);
        ++size_;

        if (root_ == nullptr) {
            end_ = new Node<Key>;
            node->right = end_;
            node->right->parent = node;
            root_ = node;
        } else {
            Node<Key>* tmp = root_;
            while (tmp != end_ || tmp != nullptr) {
                if (value < tmp->value) {
                    if (tmp->left == nullptr) {
                        tmp->left = node;
                        node->parent = tmp;
                        break;
                    } else {
                        tmp = tmp->left;
                    }
                } else if (value > tmp->value) {
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
        Node<Key> * buff = result.first.get_node();
        while (buff != root_) {
            balance(buff);
            buff = buff->parent;
        }
        balance(root_);
        return result;
    }

    void erase(iterator pos) {
        if (pos == end()) {
            throw std::out_of_range("invalid pointer");
        }
        Node<Key>* node = pos.get_node();
        Node<Key>* buff = (node != root_) ? node->parent : nullptr;
        if ((node != nullptr && node != end_) ||
            (node->left == nullptr && node->right == nullptr)) {  // что делает вот это?
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
            if (buff != nullptr) {
                while (buff != root_) {
                    balance(buff);
                    buff = buff->parent;
                }
            }
            balance(root_);
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

    void merge(set& other) {
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

    int height(Node<Key> * chunck) {
        if (chunck == nullptr || chunck == end_) return 0;
        int h_left = height(chunck->left);
        int h_right = height(chunck->right);
        if (h_left > h_right) {
            return h_left + 1;
        } else {
            return h_right + 1;
        }
    }

    void balance(Node<Key> * chunck) {
        chunck->balance = height(chunck->right) - height(chunck->left);
    }

   protected:
    Node<Key>* end_ = nullptr;

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

}  // namespace s21

#endif  // SRC_S21_SET_H_
