#include<iostream>

void makeAllocator(size_t maxSize);
void reset();
char* alloc(size_t size);

int ALLOCATOR_CAPACITY = 100;

int SMALL_CHUNK_SIZE = 10;
int MEDIUM_CHUNK_SIZE = 50;
int LARGE_CHUNK_SIZE = 99;
int OVER_CHUNK_SIZE = 101;

int main() {

    makeAllocator(ALLOCATOR_CAPACITY);

    char* small_chunk = alloc(SMALL_CHUNK_SIZE);
    if (small_chunk == nullptr) {
        std::cout << "Failed to allocate a small chunk of size " << SMALL_CHUNK_SIZE << " out of " << ALLOCATOR_CAPACITY << std::endl;
    }

    reset();
    char* medium_chunk = alloc(MEDIUM_CHUNK_SIZE);
    if (medium_chunk == nullptr) {
        std::cout << "Failed to allocate a medium chunk of size " << MEDIUM_CHUNK_SIZE << " out of " << ALLOCATOR_CAPACITY << std::endl;
    }

    reset();
    char* large_chunk = alloc(LARGE_CHUNK_SIZE);
    if (large_chunk == nullptr) {
        std::cout << "Failed to allocate a large chunk of size " << LARGE_CHUNK_SIZE << " out of " << ALLOCATOR_CAPACITY << std::endl;
    }

    reset();
    char* over_chunk = alloc(OVER_CHUNK_SIZE);
    if (over_chunk != nullptr) {
        std::cout << "Failed to allocate chunk of size " << OVER_CHUNK_SIZE << " out of " << ALLOCATOR_CAPACITY << std::endl;
    }
    
    std::cout << "All tests have passed" << std::endl;
    return 0;
}