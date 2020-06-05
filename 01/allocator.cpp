#include <iostream>


char* main_ptr;
char* end_ptr;
char* current_ptr;

void makeAllocator(size_t maxSize) {
    main_ptr = nullptr;
    if (maxSize > 0) {
        main_ptr = (char*)malloc(maxSize);
        if (main_ptr == nullptr){
            throw std :: bad_alloc();
        }
    }
    current_ptr = main_ptr;
    end_ptr = main_ptr + maxSize;
}

void reset() {
    current_ptr = main_ptr;
}

char* alloc(size_t size) {
    current_ptr = current_ptr + size;
    if (current_ptr > end_ptr) {
        return nullptr;
    }
    return current_ptr - size;
}