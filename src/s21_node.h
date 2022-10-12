#ifndef _CONTAINERS_SRC_S21_NODE_
#define _CONTAINERS_SRC_S21_NODE_

template <typename T> class s21_Node {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

   private:
    const_reference elem;

   public:
    s21_Node *back;
    s21_Node *fwd;
    explicit s21_Node(const_reference data) : elem(data), back(nullptr), fwd(nullptr){};
    s21_Node(s21_Node &other)
        : elem(other.elem), back(other.back), fwd(other.fwd){};
    explicit s21_Node() : s21_Node(nullptr){};
    ~s21_Node(){};

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

#endif  // _CONTAINERS_SRC_S21_NODE_