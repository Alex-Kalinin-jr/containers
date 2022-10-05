// #include <gtest>
#include "Stack.h"

int main() {
    Stack<int> d {5, 4, 3, 1, 6};
    // d.push(5);
    // d.push(10);
    // d.push(11);
    // std::cout<<" "<<d.size()<<std::endl;
    std::cout<<" "<<d.head.back -> elem <<std::endl;
    std::cout<<" "<<d.head.back -> back -> elem <<std::endl;
    std::cout<<" "<<d.head.back -> back -> back -> elem <<std::endl;
    //     d.pop();
    // std::cout<<" "<<d.size()<<std::endl;
    // std::cout<<" "<<d.top()<<std::endl;
    //     d.pop();
    // std::cout<<" "<<d.size()<<std::endl;
    // std::cout<<" "<<d.top()<<std::endl;
    return 0;
}