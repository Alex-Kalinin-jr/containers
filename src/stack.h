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
        Node(const_reference data) : Node (nullptr) { elem = &data; };
        Node() : Node(nullptr) {};
        ~Node() {};

        Node & operator=(Node & other) {
            elem = other.elem;
            back = other.back;
            fwd = other.fwd;
        std::cout<<"the copy is invoked"<<std::endl;
            return *this;
        }
};

template<typename T>
class Stack {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    public:
        Stack() : head(nullptr) {};
        Stack(std::initializer_list<value_type> buff) {
            for (const value_type * start = buff.begin(); start != buff.end(); ++start) {
                Node<value_type> node(start);
                node.back = (start == buff.begin()) ? nullptr : &head;
                head = node;
                ++sizeOf;
            }
        }
        ~Stack<T>() {};

        bool empty() { return (&head == nullptr); }
        size_type size() { return sizeOf; }
        void push(const_reference value) {
            Node<value_type> chunk(value);
            chunk.back = (&head == nullptr) ? nullptr : &head;
            head = chunk;
            ++sizeOf;
        }

    private:
        Node<value_type> head;
        size_type sizeOf = 0;
};

