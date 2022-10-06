#include <iostream>

template <typename T> class Node {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    public:
        const value_type * elem;
        Node * back;
        Node * fwd;

        Node(const value_type  * elem) : elem(elem), back(nullptr), fwd(nullptr) {};
        Node(const_reference data) { elem = &data; };
        Node() {
            elem = nullptr;
            back = nullptr;
            fwd = nullptr;
        };
        ~Node() {};

        Node & operator=(const Node & other) {
            elem = other.elem;
            back = other.back;
            fwd = other.fwd;
            return *this;
        }

        Node & operator=(Node && other) {
            elem = other.elem;
            back = other.back;
            fwd = other.fwd;
            return *this;
        }
};

template<typename T> class Stack {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    public:
        Stack() : sizeOf(0) {};
        Stack(const Stack &s) : head(s.head), sizeOf(s.sizeOf) {};
        Stack(Stack &&s) : head(s.head), sizeOf(s.sizeOf) {};
        Stack(std::initializer_list<value_type> buff) {
            for (const value_type * start = buff.begin(); start != buff.end(); ++start) {
                push(*start);
            }
        }
        ~Stack<T>() {};

        Stack & operator=(Stack &&s) {
            head = s.head;
            sizeOf = s.sizeOf;
            return *this;
        }

        Stack & operator=(Stack &s) {
            head = s.head;
            sizeOf = s.sizeOf;
            return *this;
        }

        const_reference top() {
            if (!head) throw std::out_of_range("stack::top() - the stack is empty");
            return *(head->elem);
        }

        bool empty() { return (head) ? false : true; }

        size_type size() { return sizeOf; }

        void push(const_reference value) {
            Node<value_type> * chunk = new Node<value_type>(value);
            chunk->back = (head == nullptr) ? nullptr : head;
            head = chunk;
            ++sizeOf;
        }

        void pop() {
            if (head != nullptr) {
                Node<value_type> * buffNode = head;
                head = (head->back != nullptr) ? head->back : head;
                delete buffNode;
                --sizeOf;
            }
        }

        void swap(Stack & other) {
            if (this != other) {
                size_type buff_size = sizeOf;
                Node<value_type> buff_head = head;
                sizeOf = other.sizeOf;
                head = other.head;
                other.sizeOf = buff_size;
                other.head = buff_head;
            }
        }


    private:
        Node<value_type> * head;
        size_type sizeOf;
};
