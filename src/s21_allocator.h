// to be prepared in the case of free time
// to be prepared in the case of free time
// to be prepared in the case of free time
// to be prepared in the case of free time
// to be prepared in the case of free time
// to be prepared in the case of free time
// to be prepared in the case of free time
// to be prepared in the case of free time
// to be prepared in the case of free time
// to be prepared in the case of free time
#define DEFAULT_SIZE 100

// namespace s21 {

template<typename T> class list_alloc {
using value_type = T;
using reference = T &;
using const_reference = const T &;
using size_type = size_t;

public:
    list_allocr() : mem(0), ptr(0), capacity(DEFAULT_SIZE), offset(0),  {}
    ~list_allocr() { if (mem) delete[] mem }

    size_type * allocate() {
        capacity = DEFAULT_SIZE;
        reinterpret_cast<value_type *>mem = new value_type[DEFAULT_SIZE];
    }

    size_type * allocate(size_type n) {
        capacity = n;
        reinterpret_cast<value_type *>mem = new value_type[n];
    }

    void realloc(size_type n) {
        if (mem && (n > capacity)) {
            size_type buff * = new value_type[n];
            std::strcpy(buff, mem, capacity * sizeof(size_type));
        }
    }


protected:
    size_type * mem;
    size_type * ptr;
    size_type capacity;
    size_type offset;

};











// }