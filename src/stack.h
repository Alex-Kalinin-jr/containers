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

        Node & operator=(const Node & other) {
            elem = other.elem;
            back = other.back;
            fwd = other.fwd;
        std::cout<<"the copy is invoked"<<std::endl;
            return *this;
        }

        Node & operator=(Node && other) {
            elem = other.elem;
            back = other.back;
            fwd = other.fwd;
        std::cout<<"the move is invoked"<<std::endl;
            return *this;
        }
};

template<typename T> class Stark {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    public:
        Stark() {
            std::cout<<"is invoked 1"<<std::endl;
            sizeOf = 0;
            head = Node<value_type>();
        };

        Stark(const Stark &s) {
            std::cout<<"is invoked 2"<<std::endl;
            head = s.head;
            sizeOf = s.sizeOf;
        }

        Stark(Stark &&s) {
            head = s.head;
            sizeOf = s.sizeOf;
        }

        Stark(std::initializer_list<value_type> buff) {
            for (const value_type * start = buff.begin(); start != buff.end(); ++start) {
                Node<value_type> node(start);
                node.back = (start == buff.begin()) ? nullptr : &head;
                head = node;
                ++sizeOf;
            }
        }

        ~Stark<T>() {};

        Stark & operator=(Stark &&s) {
            head = s.head;
            sizeOf = s.sizeOf;
            return *this;
        }

        const_reference top() {return *(head.elem);}

        bool empty() { return (&head == nullptr); }

        size_type size() { return sizeOf; }

        void push(const_reference value) {
            Node<value_type> chunk(value);
            chunk.back = (&head == nullptr) ? nullptr : &head;
            head = chunk;
            ++sizeOf;
        }

        void pop() {
            if (head.elem != nullptr) {
                if (head.back != nullptr) {
                    head = *(head.back);
                } else {
                    head = Node<value_type>();
                }
                --sizeOf;
            }
        }

        void swap(Stark & other) {
            size_type buff_size = sizeOf;
            Node<value_type> buff_head = head;
            sizeOf = other.sizeOf;
            head = other.head;
            other.sizeOf = buff_size;
            other.head = buff_head;
        }


    private:
        Node<value_type> head;
        size_type sizeOf;
};

