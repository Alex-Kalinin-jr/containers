#ifndef S21_NODE_H_
#define S21_NODE_H_

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
class list_Node {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

   private:
    const_reference elem;

   public:
    list_Node *back;
    list_Node *fwd;
    explicit list_Node(const_reference data)
        : elem(data), back(nullptr), fwd(nullptr){};
    list_Node(list_Node &other)
        : elem(other.elem), back(other.back), fwd(other.fwd){};
    ~list_Node(){};

    bool operator==(list_Node<value_type> other) { return this = &other; }

    list_Node &operator=(const list_Node &other) {
        elem = other.elem;
        back = other.back;
        fwd = other.fwd;
        return *this;
    }

    list_Node &operator=(list_Node &&other) {
        elem = other.elem;
        back = other.back;
        fwd = other.fwd;
        return *this;
    }

    const_reference get_elem() { return elem; }
};

}  // namespace s21
#endif  // S21_NODE_H_