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

    bool operator==(s21_Node<value_type> other) {return this = &other;}

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


template <typename T> class node_iterator {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using node = s21_Node<value_type>;
    using node_ptr = s21_Node<value_type> *;
public:
    node_iterator() : elem_(nullptr) {};
    explicit node_iterator(node &elem) : elem_(&elem) {};
    explicit node_iterator(node &&elem) {*elem_ = elem;};
    explicit node_iterator(node_ptr elem) : elem_(elem) {};
    ~node_iterator() {};
    void operator++() {elem_ = elem_->fwd;}
    void operator--() {elem_ = elem_->back;}
    bool operator==(const node_iterator other) {return elem_ == other.elem;}
    bool operator!=(const node_iterator other) {return elem_ != other.elem;}
    node_iterator &operator=(const node_iterator &other) {
        elem_ = other.elem;
        return *this;
    }
    node_iterator &operator=(node_iterator &&other) {
        elem_ = other.elem;
        return *this;
    }
    node_iterator &operator=(node_ptr other) {
        elem_ = other;
        return *this;
    }
    node get_elem() {return *elem_;}
protected:
    s21_Node<value_type> * elem_;
};

#endif  // _CONTAINERS_SRC_S21_NODE_