#include "queue.h"

int main() {
    s21_Queue<int> c(s21_Queue<int> {3});
    c.pop();
    c.pop();
    c.push(34);
    return 0;
}