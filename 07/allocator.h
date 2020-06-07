#pragma once

template <class T>
class Allocator {
public:
	using value_type = T;
	using size_type = size_t;
	using ptr_t = T*;

	ptr_t allocate(size_type n)
	{
		return static_cast<ptr_t>(::operator new(sizeof(value_type) * n));
	}

	void deallocate(ptr_t p)
	{
		::operator delete(p);
	}

	template<class... ArgsT>
	void construct(ptr_t p, ArgsT&&... args)
	{
		::new(p) value_type(std::forward<ArgsT>(args)...);
	}

	void destroy(ptr_t p)
	{
		p->~value_type();
	}
};