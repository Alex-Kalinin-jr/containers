// #include <gtest>
#include "stack.h"

int main() {
    Stack<int> c({5, 4, 3, 2});
    Stack<int> d({5, 4, 3, 2});
    bool g = c.empty();
    std::cout<<" "<<c.size()<<std::endl;
    c.push(4);
    c.push(4);
    c.push(4);
    std::cout<<" "<<c.size()<<std::endl;
    c.pop();
    std::cout<<" "<<c.size()<<std::endl;
    c.pop();
    std::cout<<" "<<c.size()<<std::endl;
    c.swap(d);
    std::cout<<" "<<c.size()<<std::endl;
    std::cout<<" "<<c.top()<<std::endl;
    c = Stack<int>({3, 2, 1});
    std::cout<<" "<<c.top()<<std::endl;
    return 0;
}