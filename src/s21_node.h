#ifndef _CONTAINERS_SRC_S21_NODE_
#define _CONTAINERS_SRC_S21_NODE_

namespace s21 {

template <class T>
class Node {
   public:
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    int balance = 0;

    T value;

    explicit Node(const T &value) : value(value) {}
    Node() {}
};

template <class Key, class T>
class map_Node {
   public:
    map_Node *parent = nullptr;
    map_Node *left = nullptr;
    map_Node *right = nullptr;

    T value;
    const Key key;

    explicit map_Node(Key key, const T &value) : value(value), key(key) {}
};

template <typename T>
class s21_Node {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

   private:
    const_reference elem;

   public:
    s21_Node *back;
    s21_Node *fwd;
    explicit s21_Node(const_reference data)
        : elem(data), back(nullptr), fwd(nullptr){};
    s21_Node(s21_Node &other)
        : elem(other.elem), back(other.back), fwd(other.fwd){};
    ~s21_Node(){};

    bool operator==(s21_Node<value_type> other) { return this = &other; }

    s21_Node &operator=(const s21_Node &other) {
        elem = other.elem;
        back = other.back;
        fwd = other.fwd;
        return *this;
    }

    s21_Node &operator=(s21_Node &&other) {
        elem = other.elem;
        back = other.back;
        fwd = other.fwd;
        return *this;
    }

    const_reference get_elem() { return elem; }
};

}  // namespace s21
#endif  // _CONTAINERS_SRC_S21_NODE_