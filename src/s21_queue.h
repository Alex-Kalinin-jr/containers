#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_
#include <iostream>

#include "s21_iterator.h"

namespace s21 {

template <typename T>
class Queue {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

   public:
    Queue() : head(nullptr), tail(nullptr), sizeOf(0){};
    Queue(const Queue &s) : Queue() { *this = s; };
    Queue(Queue &&s) : head(s.head), tail(s.tail), sizeOf(s.sizeOf){};
    Queue(std::initializer_list<value_type> buff) : Queue() {
        for (auto it : buff) {
            push(it);
        }
    }
    ~Queue() {
        while (sizeOf > 0) {
            pop();
        }
    };

    Queue &operator=(Queue &&s) {
        head = s.head;
        tail = s.tail;
        sizeOf = s.sizeOf;
        return *this;
    }

    Queue &operator=(const Queue &s) {
        while (!empty()) {
            pop();
        }
        if (s.head != nullptr) {
            list_Node<value_type> *chunk = new list_Node<value_type>(*(s.head));
            head = chunk;
            tail = chunk;
            sizeOf++;
            // HERE TO BE CAREFUL
            list_Node<value_type> *iterator(head);
            while (sizeOf < s.sizeOf) {
                chunk = new list_Node<value_type>(*(chunk->back));
                sizeOf++;
                chunk->fwd = iterator;
                iterator->back = chunk;
                iterator = iterator->back;
            }
        }
        return *this;
    }

    const_reference front() const {
        if (empty())
            throw std::out_of_range("Queue::front() - the Queue is empty");
        return head->get_elem();
    }

    const_reference back() const {
        if (empty())
            throw std::out_of_range("Queue::back() - the Queue is empty");
        return tail->get_elem();
    }

    bool empty() const { return (head) ? false : true; }

    size_type size() const { return sizeOf; }

    void push(const_reference value) {
        list_Node<value_type> *chunk = new list_Node<value_type>(value);
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
            list_Node<value_type> *buffNode = head;
            if (tail == head) tail = nullptr;
            head = head->back;
            delete buffNode;
            --sizeOf;
        }
    }

    void swap(Queue &other) {
        if (this != &other) {
            size_type buff_size = sizeOf;
            list_Node<value_type> *buff_head = head;
            list_Node<value_type> *buff_tail = tail;
            sizeOf = other.sizeOf;
            head = other.head;
            tail = other.tail;
            other.sizeOf = buff_size;
            other.head = buff_head;
            other.tail = buff_tail;
        }
    }

   private:
    list_Node<value_type> *head;
    list_Node<value_type> *tail;
    size_type sizeOf;
};

}  // namespace s21
#endif  // S21_QUEUE_H_