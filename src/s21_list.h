#ifndef _CONTAINERS_SRC_S21_LIST_
#define _CONTAINERS_SRC_S21_LIST_

#include "s21_node.h"
#include "s21_iterator.h"

namespace s21 {

template <typename T>
class List {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using node = s21_Node<value_type>;
    using node_ptr = s21_Node<value_type> *;
    using node_iter = node_iterator<value_type>;

   public:
    List() : begin_(nullptr), end_(nullptr), sizeOf(0) {
        value_type zero;
        node_ptr endNode = new node(zero);
        end_ = endNode;
    };
    List(size_type n, const_reference el) : List() {
        ++n;
        node_iter iter = end();
        while (--n > 0) insert(iter, el);
    }
    List(std::initializer_list<value_type> const &items) : List() {
        auto el = items.begin();
        node_iter iter = end();
        while (el != items.end()) {
            insert(iter, *el);
            ++el;
        }
    }
    List(const List &other) : List() {
        if (other.begin_ != nullptr) {
            node_iter iter = end();
            node_iter iter_2 = other.begin();
            while (iter_2.node_iter::get_elem() != other.end()) {
                insert(iter, *iter_2);
                ++iter_2;
            }
        }
    }
    List(List &&other) {
        begin_ = other.begin_;
        end_ = other.end_;
        sizeOf = other.sizeOf;
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.sizeOf = 0;
    }
    ~List() {
        clear();
        delete end_;
    }

    List &operator=(List &&other) {
        clear();
        delete end_;
        begin_ = other.begin_;
        end_ = other.end_;
        sizeOf = other.sizeOf;
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.sizeOf = 0;
        return *this;
    }

    List &operator=(const List &other) {
        if (this != &other) {
            clear();
            *this = List(other);
        }
        return *this;
    }

    void clear() {
        node_ptr next;
        if (begin_ != nullptr) {
            while (begin_ != end_) {
                next = begin_->fwd;
                delete begin_;
                begin_ = next;
            }
            begin_ = nullptr;
            end_->back = nullptr;
        }
    }

    const_reference front() const {
        if (begin_ == nullptr)
            throw std::out_of_range("List is empty: can not get an elem");
        return begin_->node::get_elem();
    }

    const_reference back() const {
        if (begin_ == nullptr)
            throw std::out_of_range("List is empty: can not get an elem");
        return end_->back->node::get_elem();
    }

    bool empty() const { return begin_ == nullptr; }

    node_ptr begin() const { return begin_; }

    node_ptr end() const { return end_; }

    size_type size() const { return sizeOf; }

    size_type max_size() const { return size_type(-1); }

    node_iter insert(node_iter iter, const_reference value) {
        node_ptr pos = iter.node_iter::get_elem();
        node_ptr chunck = new node(value);
        if (begin_ == nullptr) {
            begin_ = chunck;
            chunck->fwd = end_;
            end_->back = chunck;
        } else if (pos == begin_) {
            pos->back = chunck;
            chunck->fwd = pos;
            begin_ = chunck;
        } else {
            chunck->fwd = pos;
            chunck->back = pos->back;
            pos->back->fwd = chunck;
            pos->back = chunck;
        }
        ++sizeOf;
        iter = chunck;
        return iter;
    }

    void erase(node_iter itr) {
        node_ptr pos = itr.get_elem();
        if (pos == nullptr || pos == end_) return;
        if (pos == begin_) {
            pos->fwd->back = nullptr;
            begin_ = (begin_->fwd == end_) ? nullptr : begin_->fwd;
        } else {
            pos->back->fwd = pos->fwd;
            pos->fwd->back = pos->back;
        }
        --sizeOf;
        delete pos;
    }

    void push_back(const_reference value) { insert(end_, value); }

    void pop_back() { erase(end_->back); }

    void push_front(const_reference value) { insert(begin_, value); }

    void pop_front() { erase(begin_); }

    void swap(List &other) {
        if (this != &other) {
            List b(other);
            other = *this;
            *this = b;
        }
    }

    void merge(List &other) {
        if (other.begin_ == nullptr) return;
        if (begin_ == nullptr) {
            *this = List(other);
            return;
        }
        sizeOf += other.sizeOf;
        node_ptr buff = begin_, buff_2 = other.begin_, newList, chunck;
        if (buff->node::get_elem() < buff_2->node::get_elem()) {
            newList = buff;
            buff = buff->fwd;
        } else {
            newList = buff_2;
            buff_2 = buff_2->fwd;
        }
        begin_ = newList;
        while (buff != end_ && buff_2 != other.end_) {
            if (buff->node::get_elem() < buff_2->node::get_elem()) {
                chunck = buff;
                buff = buff->fwd;
            } else {
                chunck = buff_2;
                buff_2 = buff_2->fwd;
            }
            chunck->back = newList;
            newList->fwd = chunck;
            newList = newList->fwd;
        }
        if (buff == end_) {
            delete buff;
            newList->fwd = buff_2;
            buff_2->back = newList;
            end_ = other.end_;
            other.end_ = nullptr;
        } else {
            newList->fwd = buff;
            buff->back = newList;
            other.end_->back = nullptr;
        }
        other.begin_ = nullptr;
        other.sizeOf = 0;
    }

    void splice(const node_iter poshn, List &other) {
        if (other.begin_ == nullptr) return;
        node_ptr pos = poshn.get_elem();
        pos->back = other.end_->back;
        other.end_->back->fwd = pos;
        begin_ = other.begin_;
        sizeOf += other.sizeOf;
        delete other.end_;
        other.end_ = nullptr;
        other.begin_ = nullptr;
        other.sizeOf = 0;
    }

    void reverse() {
        if (begin_ == nullptr) return;
        node_ptr buff;
        node_ptr swapper = begin_;
        while (begin_ != end_) {
            buff = begin_->fwd;
            begin_->fwd = begin_->back;
            if (buff != end_) begin_->back = buff;
            begin_ = buff;
        }
        swapper->fwd = end_;
        begin_ = end_->back;
        end_->back = swapper;
    }

    void unique() {
        if (begin_ == nullptr) return;
        node_ptr buff = begin_;
        node_ptr for_del;
        while (buff->fwd != end_) {
            if (buff->fwd->node::get_elem() == buff->node::get_elem() &&
                buff->fwd != end_) {
                for_del = buff->fwd;
                buff->fwd = for_del->fwd;
                for_del->fwd->back = buff;
                sizeOf--;
                delete for_del;
            } else {
                buff = buff->fwd;
            }
        }
    }

    void sort() {
        if (begin_ == nullptr || end_->back == begin_) return;
        node_ptr buff = begin_;
        node_ptr chunck;
        node_ptr optimizer = end_;
        while (optimizer->back != begin_) {
            while (buff != optimizer->back) {
                chunck = buff->fwd;
                if (chunck->node::get_elem() < buff->node::get_elem()) {
                    if (buff == begin_) {
                        begin_ = chunck;
                    }
                    chunck->back = buff->back;
                    if (chunck != begin_) buff->back->fwd = chunck;
                    buff->back = chunck;
                    buff->fwd = chunck->fwd;
                    chunck->fwd->back = buff;
                    chunck->fwd = buff;
                } else {
                    buff = chunck;
                }
            }
            buff = begin_;
            optimizer = optimizer->back;
        }
    }

   private:
    node_ptr begin_;
    node_ptr end_;
    size_type sizeOf;
};

}  // namespace s21

#endif  // _CONTAINERS_SRC_S21_LIST_