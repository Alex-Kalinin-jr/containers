#include <iostream>
#include "node.h"

template<typename T> class s21_Stack {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    public:
        s21_Stack() : sizeOf(0) {};
        s21_Stack(const s21_Stack &s) : head(s.head), sizeOf(s.sizeOf) {};
        s21_Stack(s21_Stack &&s) : head(s.head), sizeOf(s.sizeOf) {};
        s21_Stack(std::initializer_list<value_type> buff) {
            for (const value_type * start = buff.begin(); start != buff.end(); ++start) {
                push(*start);
            }
        }
        ~s21_Stack<T>() {};

        s21_Stack & operator=(s21_Stack &&s) {
            head = s.head;
            sizeOf = s.sizeOf;
            return *this;
        }

        s21_Stack & operator=(s21_Stack &s) {
            head = s.head;
            sizeOf = s.sizeOf;
            return *this;
        }

        const_reference top() {
            if (!head) throw std::out_of_range("s21_Stack::top() - the s21_Stack is empty");
            return *(head->elem);
        }

        bool empty() { return (head) ? false : true; }

        size_type size() { return sizeOf; }

        void push(const_reference value) {
            s21_Node<value_type> * chunk = new s21_Node<value_type>(value);
            chunk->back = (head == nullptr) ? nullptr : head;
            head = chunk;
            ++sizeOf;
        }

        void pop() {
            if (head != nullptr) {
                s21_Node<value_type> * buffNode = head;
                head = (head->back != nullptr) ? head->back : head;
                delete buffNode;
                --sizeOf;
            }
        }

        void swap(s21_Stack & other) {
            if (this != other) {
                size_type buff_size = sizeOf;
                s21_Node<value_type> buff_head = head;
                sizeOf = other.sizeOf;
                head = other.head;
                other.sizeOf = buff_size;
                other.head = buff_head;
            }
        }

    private:
        s21_Node<value_type> * head;
        size_type sizeOf;
};
