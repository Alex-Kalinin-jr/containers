#ifndef _CONTAINERS_SRC_S21_NODE_
#define _CONTAINERS_SRC_S21_NODE_

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

template <typename T>
class node_iterator {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using node = s21_Node<value_type>;
    using node_ptr = s21_Node<value_type> *;
    using node_iter = node_iterator<value_type> &;

   public:
    node_iterator() : elem_(nullptr){};
    node_iterator(const node &elem) : elem_(&elem){};
    node_iterator(const node_iter &elem) : elem_(elem.elem_){};
    node_iterator(node_ptr elem) : elem_(elem){};
    ~node_iterator(){};

    void operator++() {
        if (elem_ != nullptr && elem_->fwd != nullptr) elem_ = elem_->fwd;
    }
    void operator--() {
        if (elem_ != nullptr && elem_->back != nullptr) elem_ = elem_->back;
    }

    node_iter operator++(int) {
        node_iter buff(*this);
        if (elem_ != nullptr) elem_ = elem_->fwd;
        return buff;
    }

    node_iter operator--(int) {
        node_iter buff(*this);
        if (elem_ != nullptr) elem_ = elem_->back;
        return buff;
    }

    node_iter operator-(const int &rv) {
        node_iter buff(*this);
        for (int i = 0; i < rv; ++i) {
            if (buff.elem_ != nullptr && buff.elem_->back != nullptr)
                buff.elem_ = buff.elem_->back;
        }
        return buff;
    }

    node_iter operator+(const int &rv) {
        node_iter buff(*this);
        for (int i = 0; i < rv; ++i) {
            if (buff.elem_ != nullptr && buff.elem_->fwd != nullptr)
                buff.elem_ = buff.elem_->fwd;
        }
        return buff;
    }

    bool operator==(const node_iterator other) const {
        return elem_ == other.elem;
    }
    bool operator!=(const node_iterator other) const {
        return elem_ != other.elem;
    }
    node_iterator &operator=(const node_iterator &other) {
        elem_ = other.elem_;
        return *this;
    }
    node_iterator &operator=(node_iterator &&other) {
        elem_ = other.elem_;
        other.elem_ = nullptr;
        return *this;
    }
    node_iterator &operator=(node_ptr other) {
        elem_ = other;
        return *this;
    }
    node_ptr get_elem() const { return elem_; }

   protected:
    node_ptr elem_;
};

#endif  // _CONTAINERS_SRC_S21_NODE_