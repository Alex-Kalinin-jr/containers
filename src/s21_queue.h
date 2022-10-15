#ifndef _CONTAINERS_SRC_S21_QUEUE_
#define _CONTAINERS_SRC_S21_QUEUE_
#include <iostream>

#include "s21_node.h"

/* remember that queue is an method to organize data ordering,
therefore it stores and handles the order of elements, not the elements
themselves/ If you put a VAR into queue and then change this VAR somwhere else,
it is changed in queue too. For exmpl, when you try int d = 0; while (++d <
1000) queue.push(d) the last 1000 elements are all the "d" and are all equal to
1000*/
template <typename T>
class s21_Queue {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using node = s21_Node<value_type>;
    using node_ptr = s21_Node<value_type> *;

   public:
    s21_Queue() : head(nullptr), tail(nullptr), sizeOf(0){};
    s21_Queue(const s21_Queue &s) : s21_Queue() { *this = s; };
    s21_Queue(s21_Queue &&s) : head(s.head), tail(s.tail), sizeOf(s.sizeOf){};
    s21_Queue(std::initializer_list<value_type> buff) : s21_Queue() {
        for (const value_type *start = buff.begin(); start < buff.end();
             ++start) {
            push(*start);
        }
    }
    ~s21_Queue() {
        while (sizeOf > 0) {
            pop();
        }
    };

    s21_Queue &operator=(s21_Queue &&s) {
        head = s.head;
        tail = s.tail;
        sizeOf = s.sizeOf;
        return *this;
    }

    s21_Queue &operator=(const s21_Queue &s) {
        while (!empty()) {
            pop();
        }

        if (s.head != nullptr) {
            s21_Node<value_type> *chunk = new node(*(s.head));
            head = chunk;
            tail = chunk;
            sizeOf++;
            // HERE TO BE CAREFUL
            node_ptr iterator(head);
            while (sizeOf < s.sizeOf) {
                chunk = new s21_Node<value_type>(*(chunk->back));
                sizeOf++;
                chunk->fwd = iterator;
                iterator->back = chunk;
                iterator = iterator->back;
            }
        }
        return *this;
    }

    const_reference front() {
        if (empty())
            throw std::out_of_range(
                "s21_Queue::front() - the s21_Queue is empty");
        return head->get_elem();
    }

    const_reference back() {
        if (empty())
            throw std::out_of_range(
                "s21_Queue::back() - the s21_Queue is empty");
        return tail->get_elem();
    }

    bool empty() { return (head) ? false : true; }

    size_type size() { return sizeOf; }

    void push(const_reference value) {
        node_ptr chunk = new s21_Node<value_type>(value);
        if (head == nullptr) {
            head = chunk;
            tail = chunk;
        } else {
            chunk->fwd = tail;
            tail->back = chunk;
            tail = chunk;
        }
        ++sizeOf;
    }

    void pop() {
        if (head != nullptr) {
            node_ptr buffNode = head;
            if (tail == head) tail = nullptr;
            head = head->back;
            delete buffNode;
            --sizeOf;
        }
    }

    void swap(s21_Queue &other) {
        if (this != &other) {
            size_type buff_size = sizeOf;
            node_ptr buff_head = head;
            node_ptr buff_tail = tail;
            sizeOf = other.sizeOf;
            head = other.head;
            tail = other.tail;
            other.sizeOf = buff_size;
            other.head = buff_head;
            other.tail = buff_tail;
        }
    }

   private:
    node_ptr head;
    node_ptr tail;
    size_type sizeOf;
};

#endif  // _CONTAINERS_SRC_S21_QUEUE_