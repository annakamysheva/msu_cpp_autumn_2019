#include <cstddef>
#include <limits>
#include <utility>
#include <stdexcept>
#include "iterator.h"
#include "allocator.h"
#pragma once

template <class T, class Alloc = Allocator<T>>
class Vector
{
private:
    Alloc alloc_;
    T* data_;
    size_t size_;
    size_t capacity_;
    
public:
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    Vector() : data_(nullptr), size_(0), capacity_(0) {}
    
    explicit Vector(size_t initial_size): data_(alloc_.allocate(initial_size*2)), size_(initial_size), capacity_(initial_size*2)
    {
        for(size_t i = 0; i < size_; i++)
            alloc_.construct(data_ + i);
    }
    
    void resize(size_t size)
    {
        if (size_ < size)
        {
            reserve(size*2);
            for (size_t i = size_; i < size; i++)
                alloc_.construct(data_ + i);
            size_ = size;
        } else if(size_ > size)
        {
            for (size_t i = size; i < size_; i++)
                alloc_.destroy(data_ + i);
            size_ = size;
        }
    }
    
    void reserve(size_t new_cap)
    {
        if (capacity_ < new_cap)
        {
            pointer buf = alloc_.allocate(new_cap);
            for(size_t i = 0; i < size_; i++)
            {
                alloc_.construct(buf + i, std::forward<T>(*(data_ + i)));
                alloc_.destroy(data_ + i);
            }
            alloc_.deallocate(data_);
            capacity_ = new_cap;
            data_ = buf;
        }
    }
    
    size_t capacity() const
    {
        return capacity_;
    }
    
    void pop_back()
    {
        if (size_ > 0)
        {
            alloc_.destroy(data_ + size_);
            --size_;
        }
    }

    void push_back(const T& new_el)
    {
        if (size_ >= capacity_)
        {
            size_t new_cap = (capacity_ > 0) ? (capacity_ * 2) : 2;
            reserve(new_cap);
        }
        alloc_.construct(data_ + size_, (new_el));
        size_++;
    }
    
    void push_back(T&& new_el)
    {
        if (size_ >= capacity_)
        {
            size_t new_cap = (capacity_ > 0) ? (capacity_ * 2) : 2;
            reserve(new_cap);
        }
        alloc_.construct(data_ + size_, std::move(new_el));
        size_++;
    }
    
    iterator begin()
    {
        return iterator(data_);
    }
    
    iterator end()
    {
        return iterator(data_ + size_);
    }
    
    reverse_iterator rbegin()
    {
        return reverse_iterator(this -> end());
    }
    
    reverse_iterator rend()
    {
        return reverse_iterator(this -> begin());
    }
    
    reference operator[](int i)
    {
        if (i >= size_)
            throw std::out_of_range("Out of range");
        else 
            return data_[i];          
    }
    
    size_t size() const
    {
        return size_;
    }
    
    bool empty()
    {
        return (size_ == 0);
    }
    
    void clear()
    {
        for(size_t i = 0; i < size_; ++i)
            alloc_.destroy(data_ + i);
        size_ = 0;
        capacity_ = 0;
    }
    
    ~Vector()
    {
        clear();
        alloc_.deallocate(data_);
    }
};