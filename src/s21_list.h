#include "s21_node.h"

template<typename T> class s21_List {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using node = s21_Node<value_type>;
    using node_iterator = s21_Node<value_type> *;
    friend node;

public:
    s21_List() : begin(0), end(0), sizeOf(0) {};
    s21_List(size_type n, const_reference el) : sizeOf(n) {
        node_iterator prev = new node(el);
        begin = prev;
        while (n-- > 0) {
            node_iterator buff = new node(el);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
        }
        end = prev;
    }
    s21_List(std::initializer_list<value_type> const &items) : s21_List() {
        auto el = items.begin();
        node_iterator prev = new node(*el);
        begin = prev;
        ++sizeOf;
        while ((++el) != items.end()) {
            node_iterator buff = new node(*el);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
            ++sizeOf;
        }
        end = prev;
    }

    ~s21_List() {
        node_iterator prev;
        while (sizeOf-- > 0) {
            prev = end->back;
            if (end) delete end;
            end = prev;
        }
        delete end;
    }

    size_type size() {return sizeOf;}
    bool empty() {return ((sizeOf == 0) && (begin == 0));}

private:
    node_iterator begin;
    node_iterator end;
    size_type sizeOf;

};