#include <iterator>
#include "allocator.h"
#pragma once

template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>
{

private:
	T* ptr_;

public:
    using ref_t = T&;

	explicit Iterator(T* p) : ptr_(p)
	{
	}

	bool operator==(const Iterator& a) const
	{
		return ptr_ == a.ptr_;
	}

	bool operator!=(const Iterator& a) const
	{
		return !(ptr_ == a.ptr_);
	}

	ref_t operator*() const
	{
		return *ptr_;
	}

	Iterator& operator++()
	{
		ptr_++;
		return *this;
	}

	Iterator& operator--()
	{
		ptr_--;
		return *this;
	}

	Iterator& operator+=(size_t n)
	{
		return *this += n;
	}

	Iterator& operator-=(size_t n)
	{
		return *this += -n;
	}

	Iterator operator+(size_t n) const
	{
		return Iterator(ptr_ + n);
	}

	Iterator operator-(size_t n) const
	{
		return Iterator(ptr_ - n);
	}


	bool operator<(const Iterator& a) const
	{
		return ptr_ < a.ptr_;
	}

	bool operator>(const Iterator& a) const
	{
		return ptr_ > a.ptr_;
	}

	bool operator>=(const Iterator& a) const
	{
		return ptr_ >= a.ptr_;
	}

	bool operator<=(const Iterator& a) const
	{
		return ptr_ <= a.ptr_;
	}

	ref_t operator[](size_t n)
	{
		return ptr_[n];
	}
};