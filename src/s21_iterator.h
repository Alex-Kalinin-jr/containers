#ifndef SRC_S21_SET_ITER_H_
#define SRC_S21_SET_ITER_H_

#include <climits>
#include <cstddef>
#include <initializer_list>
#include <utility>

namespace s21 {

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

   protected:
    Node<T>* node;

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

template <class T>
class MultisetIterator  : public SetIterator<T> {
    using iterator = SetIterator<T>;
    public:
    explicit MultisetIterator(Node<T>* node) : SetIterator<T>(node) {};
private:
    void increase() {
        if (node == nullptr) return;
        if (node->value == node->left->value) {
            node = node->left;
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
            if (node->parent->value == node->value) { return; }
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

}
#endif //SRC_S21_SET_ITER_H_