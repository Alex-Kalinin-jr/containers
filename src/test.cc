// #include <gtest>
#include "Stack.h"

int main() {
    Stark<int> c({5, 4, 3, 2});
    Stark<int> d;
    d.push(5);
    d.push(10);
    std::cout<<" "<<d.size()<<std::endl;
    std::cout<<" "<<d.top()<<std::endl;
    d.pop();
    d.push(11);
    std::cout<<" "<<d.size()<<std::endl;
    std::cout<<" "<<d.top()<<std::endl;
        d.pop();
    std::cout<<" "<<d.size()<<std::endl;
    std::cout<<" "<<d.top()<<std::endl;
    return 0;
}