// #include <gtest>
#include "Stack.h"

int main() {
    // Stack<int> d {5, 4, 3, 1, 6};
    Stack<int> d({5, 3, 2});
    std::cout<<" "<<d.top()<<std::endl;
    d.push(11);
    float k = 15.4;
    d.push(k);
    std::cout<<" "<<d.top()<<std::endl;
    d.pop();
    std::cout<<" "<<d.top()<<std::endl;
    d.pop();
    std::cout<<" "<<d.top()<<std::endl;
    d.pop();
    std::cout<<" "<<d.top()<<std::endl;
    d.pop();
    std::cout<<" "<<d.top()<<std::endl;
    // std::cout<<" "<<d.size()<<std::endl;
    // std::cout<<" "<<d.head.back -> elem <<std::endl;
    // std::cout<<" "<<d.head.back -> back -> elem <<std::endl;
    // std::cout<<" "<<d.head.back -> back -> back -> elem <<std::endl;
    // std::cout<<" "<<d.size()<<std::endl;
    //     d.pop();
    // std::cout<<" "<<d.size()<<std::endl;
    // std::cout<<" "<<d.top()<<std::endl;
    return 0;
}