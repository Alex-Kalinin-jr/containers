#include <iostream>
#include "main.h"
template<typename T>
class A {
    public:
    T a;
    A() : a(5) {};
    ~A() {};
};

template<typename T>
class B : public A<T> {
    public:
    B() : A<T>::A() {};
    ~B() {};
};

int main() {
    B<int> z;
    std::cout<<z.a<<std::endl;
}