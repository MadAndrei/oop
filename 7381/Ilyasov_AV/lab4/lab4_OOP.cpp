#include "pch.h"
#include <iostream>

template <typename T>
class shared_ptr
{
public:
	template<class Y>
	friend class shared_ptr;

	explicit shared_ptr(T *ptr = nullptr)
		: ptr(ptr), ptr_count(ptr ? new long(1) : nullptr)
	{}

	~shared_ptr()
	{
		destroy();
	}

	shared_ptr(const shared_ptr<T> &other)
		: ptr(other.ptr), ptr_count(other.ptr_count)
	{
		increase_ptr_count();
	}

	shared_ptr & operator=(const shared_ptr<T> &other)
	{
		if (ptr != other.get()) {
			destroy();

			shared_ptr tmp(other);
			tmp.swap(*this);

			increase_ptr_count();
		}
		return *this;
	}

	template <typename Y>
	shared_ptr(const shared_ptr<Y> &other)
		: ptr(other.ptr), ptr_count(other.ptr_count)
	{
		//increase_ptr_count();
	}

	template <typename Y>
	shared_ptr & operator=(const shared_ptr<Y> &other)
	{
		if (ptr != other.get()) {
			//destroy();

			shared_ptr tmp(other);
			tmp.swap(*this);

			//increase_ptr_count();
		}
		return *this;
	}

	explicit operator bool() const
	{
		return ptr != nullptr;
	}

	T * get() const
	{
		return ptr;
	}

	long use_count() const
	{
		return ptr_count ? *ptr_count : 0;
	}

	T & operator*() const
	{
		return *ptr;
	}

	T * operator->() const
	{
		return ptr;
	}

	void swap(shared_ptr &x) noexcept
	{
		std::swap(ptr, x.ptr);
		std::swap(ptr_count, x.ptr_count);
	}

	void reset(T *new_ptr = nullptr)
	{
		destroy();

		ptr = new_ptr;
		ptr_count = ptr ? new long(1) : nullptr;
	}

	
private:
	T *ptr;
	long *ptr_count;

	void increase_ptr_count() {
		if (ptr_count)
			(*ptr_count)++;
	}

	void destroy() {
		if (ptr_count)
			(*ptr_count)--;
		if (!use_count()) {
			delete ptr;
			delete ptr_count;
		}
	}
};

	template<typename T, typename Y>
	bool operator ==(const shared_ptr<T> &left, const shared_ptr<Y> &right) {
		return left.get() == right.get();
	}

	template<typename T, typename Y>
	bool operator !=(const shared_ptr<T> &left, const shared_ptr<Y> &right) {
		return left.get() != right.get();
	}

class Base {
public:
	Base(int b) : m_b(b) {}
protected:
	int m_b;
};

class Derived : public Base {
public:
	Derived(int b, int d) : Base(b), m_d(d) {}
private:
	int m_d;
};

int main() {
	shared_ptr<Derived> a(new Derived(1, 1));
	std::cout << "a: " << a.use_count() << std::endl;
	shared_ptr<Base> b = a;

	std::cout << "a: " << a.use_count() << std::endl;
	std::cout << "b: " << b.use_count() << std::endl;

	a == b ? std::cout << "+" << std::endl : std::cout << "-" << std::endl;
	return 0;
}