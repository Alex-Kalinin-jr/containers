#include "s21_node.h"

template<typename T> class s21_List {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using node = s21_Node<value_type>;
    using node_ptr = s21_Node<value_type> *;
    using node_iter = node_iterator<value_type>;

public:
    s21_List() : begin_(nullptr), end_(nullptr), sizeOf(0) {
        value_type zero;
        node_ptr endNode = new node(zero);
        end_ = endNode;
    };
    s21_List(size_type n, const_reference el) : sizeOf(n) {
        node_ptr prev = new node(el);
        begin_ = prev;
        while (--n > 0) {
            node_ptr buff = new node(el);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
        }
        node_ptr endNode = new node(el);
        endNode->back = prev;
        prev->fwd = endNode;
        end_ = endNode;
    }

    s21_List(std::initializer_list<value_type> const &items) : s21_List() {
        auto el = items.begin();
        node_ptr prev = new node(*el);
        begin_ = prev;
        ++sizeOf;
        while ((++el) != items.end()) {
            node_ptr buff = new node(*el);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
            ++sizeOf;
        }
        end_->back = prev;
        prev->fwd = end_;
    }

    s21_List(const s21_List &other) : s21_List() {
        sizeOf = other.sizeOf;
        node_ptr iter = other.begin_;
        node_ptr prev = new node(*iter);
        begin_ = prev;
        while (iter != other.end_->back) {
            iter = iter->fwd;
            node_ptr buff = new node(*iter);
            buff->back = prev;
            prev->fwd = buff;
            prev = buff;
        }
        end_->back = prev;
        prev->fwd = end_;
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
        delete end_;
    }


    s21_List & operator=(s21_List &&other) {
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
        if (begin_ == nullptr) throw std::out_of_range("s21_list is empty: can not get an elem");
        return begin_->node::get_elem();
        }

    const_reference back() const {
        if (begin_ == nullptr) throw std::out_of_range("s21_list is empty: can not get an elem");
        return end_->back->node::get_elem();
    }

    node_ptr begin() const {return begin_;}
    node_ptr end() const {return end_;}

    bool empty() const {return begin_ == nullptr || sizeOf != 0;}
    size_type size() {return sizeOf;}
    size_type max_size() const {return size_type(-1);}

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
            if (begin_ == nullptr) {
                begin_ = chunck;
                pos->back = chunck;
            } else {
                chunck->back = pos->back;
                pos->back->fwd = chunck;
                pos->back = chunck;
            }
        }
        sizeOf++;
        iter = chunck;
        return iter;
    }

    void erase(node_iter itr) {
        node_ptr pos = itr.get_elem();
        if (pos == nullptr || pos == end_) return;
        if (pos == begin_) {
            pos->fwd->back = nullptr;
            begin_ = (begin_->fwd == end_) ? nullptr : begin_ -> fwd;
        } else {
            pos->back->fwd = pos->fwd;
            pos->fwd->back = pos->back;
        }
        sizeOf--;
        delete pos;
    }

    void push_back(const_reference value) {
        insert(end_, value);
    }

    void pop_back() {
        erase(end_->back);
    }

    void push_front(const_reference value) {
        insert(begin_, value);
    }

    void pop_front() {
        erase(begin_);
    }

    void swap(s21_List & other) {
        if (this != &other) {
            s21_List b(other);
            other = *this;
            *this = b;
        }
    }

    void merge(s21_List& other) {
        if (other.begin_ == nullptr) return;
        if (begin_ == nullptr) {
            *this = s21_List(other);
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

    void splice(const node_iter poshn, s21_List& other) {
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
        while(buff->fwd != end_) {
            if (buff->fwd->node::get_elem() ==
            buff->node::get_elem()) {
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















