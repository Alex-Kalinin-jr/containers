#include "Stack.h"

int main() {
    s21_Stack<int> c;
    int d = 0;
    while (d != 2) {
        c.push(d);
        ++d;
    }
    std::cout<<" "<<std::endl;
    return 0;
}