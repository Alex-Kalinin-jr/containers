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
        while (--n > 0) {
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

    s21_List(const s21_List &other) {
        sizeOf = other.sizeOf;
        node_iterator iter = other.begin;
        node_iterator prev = new node(*iter);
        begin = prev;
        while (iter != other.end) {
            iter = iter->fwd;
            node_iterator buff = new node(*iter);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
        }
        end = prev;
    }

    s21_List(s21_List &&other) {
        begin = other.begin;
        end = other.end;
        sizeOf = other.sizeOf;
        other.begin = 0;
        other.end = 0;
        other.sizeOf = 0;
    }

    ~s21_List() {
            clear();
    }

    s21_List & operator=(s21_List &&other) {
        if (*this != other) {
            clear();
            begin = other.begin;
            end = other.end;
            sizeOf = other.sizeOf;
        }
        return *this;
    }

    s21_List & operator=(const s21_List &other) {
        if (this != &other) {
            clear();
            begin = other.begin;
            end = other.end;
            sizeOf = other.sizeOf;
        }
        return *this;
    }

    size_type size() {return sizeOf;}
    bool empty() {return ((sizeOf == 0) && (begin == 0));}

    void clear() {
        node_iterator prev;
        while (end) {
            prev = end->back;
            delete end;
            end = prev;
        }
        begin = 0;
        end = 0;
    }

private:
    node_iterator begin;
    node_iterator end;
    size_type sizeOf;

};