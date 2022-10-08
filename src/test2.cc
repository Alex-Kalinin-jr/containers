#include "queue.h"

using kljd = const int &;

void f(const int &b) { const int *c = &b; }

int main() {
    // s21_Queue<int> c(s21_Queue<int> {3});
    // c.pop();
    // c.pop();
    // c.pop();
    // c.pop();
    // c.pop();
    // c.pop();
    // c.push(34);

    const int a = 5;

    f(a);

    return 0;
}