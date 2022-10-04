// #include <gtest>
#include "stack.h"

int main() {
    Stack<int> c({5, 4, 3, 2});
    bool g = c.empty();
    std::cout<<" "<<c.size()<<std::endl;
    c.push(4);
    c.push(4);
    c.push(4);
    std::cout<<" "<<c.size()<<std::endl;

    return 0;
}