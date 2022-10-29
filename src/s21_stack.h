#ifndef _CONTAINERS_SRC_S21_STACK_
#define _CONTAINERS_SRC_S21_STACK_
#include <iostream>

#include "s21_node.h"

/* remember that stack is an method to organize data ordering,
therefore it stores and handles the order of elements, not the elements
themselves/ If you put a VAR into stack and then change this VAR somwhere else,
it is changed in stack too. For exmpl, when you try int d = 0; while (++d <
1000) stack.push(d) the last 1000 elements are all the "d" and are all equal to
1000*/

namespace s21 {

template <typename T>
class Stack {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    using node = s21_Node<value_type>;
    using node_ptr = s21_Node<value_type> *;

   private:
    node_ptr head;
    size_type sizeOf;

   public:
    Stack() : head(nullptr), sizeOf(0){};
    Stack(const Stack &s) : Stack() { *this = s; };
    Stack(Stack &&s) : head(s.head), sizeOf(s.sizeOf){};
    Stack(std::initializer_list<value_type> buff) : Stack() {
        for (const value_type *start = buff.begin(); start < buff.end();
             ++start) {
            push(*start);
        }
    }
    ~Stack() {
        while (sizeOf > 0) {
            pop();
        }
    };

    Stack &operator=(Stack &&s) {
        head = s.head;
        sizeOf = s.sizeOf;
        return *this;
    }

    Stack &operator=(const Stack &s) {
        while (!empty()) {
            pop();
        }
        if (s.head != nullptr) {
            node_ptr chunk = new s21_Node(*(s.head));
            head = chunk;
            sizeOf++;
            node_ptr iterator(head);
            while (sizeOf < s.sizeOf) {
                chunk = new s21_Node(*(chunk->back));
                sizeOf++;
                iterator->back = chunk;
                iterator = iterator->back;
            }
        }
        return *this;
    }

    const_reference top() {
        if (empty())
            throw std::out_of_range("Stack::top() - the Stack is empty");
        return head->get_elem();
    }

    bool empty() { return (head) ? false : true; }

    size_type size() { return sizeOf; }

    void push(const_reference value) {
        node_ptr chunk = new node(value);
        chunk->back = head;
        head = chunk;
        ++sizeOf;
    }

    void pop() {
        if (head != nullptr) {
            node_ptr buffNode = head;
            head = head->back;
            delete buffNode;
            --sizeOf;
        }
    }

    void swap(Stack &other) {
        if (this != &other) {
            size_type buff_size = sizeOf;
            node_ptr buff_head = head;
            sizeOf = other.sizeOf;
            head = other.head;
            other.sizeOf = buff_size;
            other.head = buff_head;
        }
    }
};

}  // namespace s21
#endif  // _CONTAINERS_SRC_S21_STACK_