// what is better?
// to save flexibility and implicit redefinition to have possibility of:
// erase(ptr)::danger:: node can be of other container, i.e. stack and bad programming
// will crash all the program
// or to redefine classes node and iterator, to write "explicit" and to lose flexibility
// but increase safety??????
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
        endNode->fwd = endNode;
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
        node_ptr endNode = new node(*prev);
        endNode->back = prev;
        endNode->fwd = nullptr;
        prev->fwd = endNode;
        end_ = endNode;
    }
    s21_List(const s21_List &other) {
        sizeOf = other.sizeOf;
        node_ptr iter = other.begin_;
        node_ptr prev = new node(*iter);
        begin_ = prev;
        while (iter != other.end_) {
            iter = iter->fwd;
            node_ptr buff = new node(*iter);
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
        if (begin_ != nullptr) {
            clear();
        }
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
            node_ptr prev;
            while (end_ != nullptr) {
                prev = end_->back;
                if (end_!= nullptr) delete end_;
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
        return end_->back->get_elem();
    }

    node_ptr begin() const {return begin_;}
    node_ptr end() const {return end_;}

private:
    node_ptr begin_;
    node_ptr end_;
    size_type sizeOf;

};










    // bool empty() const {return begin_ == nullptr || sizeOf != 0;}
    // size_type size() {return sizeOf;}
    // size_type max_size() const {return size_type(-1);}

    // node_iter insert(node_iter iter, const_reference value) {
    //     node_ptr pos = iter.node_iter::get_elem();
    //     node_ptr chunck = new node(value);
    //     if (pos == nullptr) {
    //         begin_ = chunck;
    //         end_ = chunck;
    //     } else if (pos == begin_) {
    //         pos->back = chunck;
    //         chunck->fwd = pos;
    //         begin_ = chunck;
    //     } else {
    //         pos->back->fwd = chunck;
    //         chunck->back = pos->back;
    //         chunck->fwd = pos;
    //         pos->back = chunck;
    //     }
    //     sizeOf++;
    //     iter = chunck;
    //     return iter;
    // }

    // void erase(node_iter itr) {
    //     node_ptr pos = itr.get_elem();
    //     if (pos == nullptr) return;
    //     if (begin_ != end_) {
    //         if (pos == begin_) {
    //             pos->fwd->back = nullptr;
    //             begin_ = pos->fwd;
    //         } else if (pos == end_) {
    //             pos->back->fwd = nullptr;
    //             end_ = pos -> back;
    //         } else {
    //             pos->back->fwd = pos->fwd;
    //             pos->fwd->back = pos->back;
    //         }
    //     } else {
    //         begin_ = nullptr;
    //         end_ = nullptr;
    //     }
    //     sizeOf--;
    //     delete pos;
    // }

    // void push_back(const_reference value) {
    //     insert(end_, value);
    // }

    // void pop_back() {
    //     erase(end_);
    // }

    // void push_front(const_reference value) {
    //     insert(begin_, value);
    // }

    // void pop_front() {
    //     erase(begin_);
    // }

