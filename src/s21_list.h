#include "s21_node.h"

template<typename T> class s21_List {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using node = s21_Node<value_type>;
    using node_iterator = s21_Node<value_type> *;

public:
    s21_List() : begin_(nullptr), end_(nullptr), sizeOf(0) {};
    s21_List(size_type n, const_reference el) : sizeOf(n) {
        node_iterator prev = new node(el);
        begin_ = prev;
        while (--n > 0) {
            node_iterator buff = new node(el);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
        }
        end_ = prev;
    }
    s21_List(std::initializer_list<value_type> const &items) : s21_List() {
        auto el = items.begin();
        node_iterator prev = new node(*el);
        begin_ = prev;
        ++sizeOf;
        while ((++el) != items.end()) {
            node_iterator buff = new node(*el);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
            ++sizeOf;
        }
        end_ = prev;
    }

    s21_List(const s21_List &other) {
        sizeOf = other.sizeOf;
        node_iterator iter = other.begin_;
        node_iterator prev = new node(*iter);
        begin_ = prev;
        while (iter != other.end_) {
            iter = iter->fwd;
            node_iterator buff = new node(*iter);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
        }
        end_ = prev;
    }

    s21_List(s21_List &&other) {
        begin_ = other.begin_;
        end_ = other.end_;
        sizeOf = other.sizeOf;
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.sizeOf = 0;
    }

    ~s21_List() {
            clear();
    }

    s21_List & operator=(s21_List &&other) {
        clear();
        begin_ = other.begin_;
        end_ = other.end_;
        sizeOf = other.sizeOf;
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.sizeOf = 0;
        return *this;
    }

    s21_List & operator=(const s21_List &other) {
        if (this != &other) {
            clear();
            *this = s21_List(other);
        }
        return *this;
    }

    size_type size() const {return sizeOf;}
    bool empty() {return ((sizeOf == 0) && (begin_ == nullptr));}

    void clear() {
            node_iterator prev;
            while (end_) {
                prev = end_->back;
                if (end_) delete end_;
                end_ = prev;
            }
            begin_ = nullptr;
            end_ = nullptr;
    }

    const_reference front() const {
        if (begin_ == nullptr) throw std::out_of_range("s21_list is empty: can not get an elem");
        return begin_->get_elem();
        }
    const_reference back() const {
        if (begin_ == nullptr) throw std::out_of_range("s21_list is empty: can not get an elem");
        return end_->get_elem();
    }

    node_iterator begin() const {return begin_;}
    node_iterator end() const {return end_;}
    bool empty() const {return begin_ == nullptr || sizeOf != 0;}
    size_type size() {return sizeOf;}
    size_type max_size() const {return size_type(-1);}

    node_iterator insert(node_iterator pos, const_reference value) {
        node_iterator chunck = new node(value);
        pos.back.fwd = chunck;
        chunck->back = pos.back;
        chunck->fwd = pos;
        pos.back = chunck;
        sizeOf++;
        return chunck;
    }

    void erase(node_iterator pos) {
        pos->back->fwd = pos->fwd;
        pos->fwd->back = pos->back;
        sizeOf--;
        delete pos;
    }

private:
    node_iterator begin_;
    node_iterator end_;
    size_type sizeOf;

};