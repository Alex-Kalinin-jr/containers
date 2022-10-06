#ifndef _CONTAINERS_SRC_s21_Node_
#define _CONTAINERS_SRC_s21_Node_

template <typename T> class s21_Node {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    public:
        const value_type * elem;
        s21_Node * back;
        s21_Node * fwd;

        s21_Node(const value_type  * elem) : elem(elem), back(nullptr), fwd(nullptr) {};
        s21_Node(const_reference data) { elem = &data; };
        s21_Node() {
            elem = nullptr;
            back = nullptr;
            fwd = nullptr;
        };
        ~s21_Node() {};

        s21_Node & operator=(const s21_Node & other) {
            elem = other.elem;
            back = other.back;
            fwd = other.fwd;
            return *this;
        }

        s21_Node & operator=(s21_Node && other) {
            elem = other.elem;
            back = other.back;
            fwd = other.fwd;
            return *this;
        }
};

#endif  // _CONTAINERS_SRC_s21_Node_