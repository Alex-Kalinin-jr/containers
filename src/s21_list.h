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
    s21_List() : begin(0), end(0), capacity(0) {};
    s21_List(size_type n) : capacity(n) {
        node_iterator prev = new node();
        begin = prev;
        while (n-- > 0) {
            node_iterator buff = new node();
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
        }
        end = prev;
    }
    ~s21_List() {
        node_iterator prev;
        while (capacity-- > 0) {
            prev = end->back;
            if (end) delete end;
            end = prev;
        }
        delete end;
    }

    size_type size() {return capacity;}

private:
    node_iterator begin;
    node_iterator end;
    size_type capacity;

};