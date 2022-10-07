#include "Stack.h"

int main() {
    s21_Stack<int> a {3, 5, 6};
    s21_Stack<int> b(a);
    std::cout<<" "<<std::endl;
    return 0;
}