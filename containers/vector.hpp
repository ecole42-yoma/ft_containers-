#pragma once

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#ifdef BASIC
#include "_core_utils.hpp"
#include "_iterator.hpp"
#include "_iterator_traits.hpp"
#include "_type_traits.hpp"
#include "reverse_iterator.hpp"
#else
#include "../iterator/_iterator.hpp"
#include "../iterator/_iterator_traits.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../type/_type_traits.hpp"
#include "../util/_core_utils.hpp"
#endif

#include <iostream>

#define THIS vector< _Tp, _Allocator >

namespace ft {

template< typename Vector >
class randomIterator : public ft::iterator< ft::random_access_iterator_tag, typename Vector::value_type > {

	public:
	// typedef typename randomIterator::difference_type   difference_type;
	// typedef typename randomIterator::value_type		   value_type;
	// typedef typename randomIterator::iterator_category iterator_category;
	typedef typename randomIterator::pointer   pointer;
	typedef typename randomIterator::reference reference;

	private:
	pointer __pointer;

	public:
	randomIterator(pointer input_pointer = NULL)
	  : __pointer(input_pointer) {}

	randomIterator& operator++() {
		++__pointer;
		return *this;
	}
	randomIterator operator++(int) {
		randomIterator tmp = *this;
		++(*this);
		return tmp;
	}
	randomIterator& operator--() {
		--__pointer;
		return *this;
	}
	randomIterator operator--(int) {
		randomIterator tmp = *this;
		--(*this);
		return tmp;
	}

	reference operator[](int index) { return __pointer[index]; }
	pointer	  operator->() { return __pointer; }
	reference operator*() { return *__pointer; }
	bool	  operator==(const randomIterator& rhs) const { return __pointer == rhs.__pointer; }
	bool	  operator!=(const randomIterator& rhs) const { return !(*this == rhs); }
	// TODO: add <=, >=, <, >

}; // class randomIterator

template< typename _Tp, typename _Allocator = std::allocator< _Tp > >
class vector {

	public:
	typedef vector< _Tp, _Allocator >				 self_type;
	typedef _Tp										 value_type;
	typedef _Allocator								 allocator_type;
	typedef typename allocator_type::size_type		 size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef randomIterator< self_type >				 iterator;
	typedef const randomIterator< self_type >		 const_iterator;
	typedef ft::reverse_iterator< iterator >		 reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >	 const_reverse_iterator;

	private:
	_Allocator __alloc;
	size_type  __size;
	size_type  __capacity;
	pointer	   __data;

	/**
	 * * [ default form] ---------------------------------------------------------------------------
	 */
	public:
	vector();
	explicit vector(const allocator_type& alloc); // default
	explicit vector(size_type			  n,
					const value_type&	  val	= value_type(),
					const allocator_type& alloc = allocator_type()); // fill
	template< typename _Iter >
	vector(_Iter																  first,
		   typename ft::enable_if< ft::is_iterator< _Iter >::value, _Iter >::type last,
		   const allocator_type&												  alloc = allocator_type()); // range
	vector(const vector& x);								// copy
	~vector();
	vector& operator=(const vector& x);

	/**
	 * * [ allocator ] -----------------------------------------------------------------------------
	 */
	allocator_type get_allocator() const;

	/**
	 * * [ element access ] ------------------------------------------------------------------------
	 */
	reference		  at(size_type n);
	const_reference	  at(size_type n) const;
	reference		  operator[](size_type n);
	const_reference	  operator[](size_type n) const;
	reference		  front();
	const_reference	  front() const;
	reference		  back();
	const_reference	  back() const;
	value_type*		  data();
	const value_type* data() const;

	/**
	 * * [ iterators ] -----------------------------------------------------------------------------
	 */
	iterator			   begin() { return iterator(__data); }
	iterator			   end() { return iterator(__data + __size); }
	const_iterator		   begin() const { return const_iterator(__data); }
	const_iterator		   end() const { return const_iterator(__data + __size); }
	reverse_iterator	   rbegin();
	reverse_iterator	   rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;

	/**
	 * * [ capacity ] ------------------------------------------------------------------------------
	 */
	size_type size() const { return __size; }
	size_type max_size() const { return __alloc.max_size() / sizeof(value_type); }
	size_type capacity() const { return __capacity; }
	bool	  empty() const { return size() == size_type(); };
	void	  reserve(size_type n);

	/**
	 * * [ modifiers ] -----------------------------------------------------------------------------
	 */
	template< typename InputIterator >
	void	 assign(InputIterator first, InputIterator last);
	void	 assign(size_type n, const value_type& u);
	void	 push_back(const value_type& x);
	void	 pop_back();
	iterator insert(const_iterator position, const value_type& x);
	iterator insert(const_iterator position, size_type n, const value_type& x);
	template< typename InputIterator >
	iterator insert(const_iterator position, InputIterator first, InputIterator last);
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);
	void	 clear();
	void	 swap(vector& x);
	void	 resize(size_type sz, value_type c = value_type());
	bool	 __invariants() const;

	/**
	 * * [ internal workhorse ] --------------------------------------------------------------------
	 */
}; /* class vector */

/**
 * * [ non-member function overloads ] -------------------------------------------------------------
 */
template< typename _Tp, typename _Allocator >
bool
operator==(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);
template< typename _Tp, typename _Allocator >
bool
operator!=(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);
template< typename _Tp, typename _Allocator >
bool
operator<(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);
template< typename _Tp, typename _Allocator >
bool
operator<=(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);
template< typename _Tp, typename _Allocator >
bool
operator>(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);
template< typename _Tp, typename _Allocator >
bool
operator>=(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);
template< typename _Tp, typename _Allocator >
void
swap(ft::vector< _Tp, _Allocator >& lhs, ft::vector< _Tp, _Allocator >& rhs);

/**
 * * [ default form] -------------------------------------------------------------------------------
 */
template< typename _Tp, typename _Allocator >
THIS::vector() // default
  try
  : __alloc(allocator_type())
  , __size(0)
  , __capacity(0)
  , __data(NULL) {
	LOG_("empty default constructor");
} catch (...) {
}
template< typename _Tp, typename _Allocator >
THIS::vector(const allocator_type& alloc) // default
  try
  : __alloc(alloc)
  , __size(0)
  , __capacity(0)
  , __data(NULL) {
	LOG_("default constructor");
} catch (...) {
}
template< typename _Tp, typename _Allocator >
THIS::vector(size_type			   n,
			 const value_type&	   val,
			 const allocator_type& alloc) // fill
  try
  : __alloc(alloc)
  , __size(n)
  , __capacity(n)
  , __data(NULL) {
	LOG_("fill constructor");
	if (n > 0) {
		__data	   = __alloc.allocate(n);
		__capacity = n;
		__size	   = n;
		for (size_type i = 0; i < n; ++i) {
			__alloc.construct(__data + i, val);
		}
	}
} catch (const std::exception& e) {
} catch (...) {
}
template< typename _Tp, typename _Allocator >
template< typename _Iter >
THIS::vector(_Iter																	first,
			 typename ft::enable_if< ft::is_iterator< _Iter >::value, _Iter >::type last,
			 const allocator_type&													alloc) // range
  try
  : __alloc(alloc)
  , __size(0)
  , __capacity(0)
  , __data(NULL) {
	LOG_("range constructor");
	(void)first;
	(void)last;
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
} catch (...) {
}
template< typename _Tp, typename _Allocator >
THIS::vector(const vector& x) // copy
  try
  : __alloc(allocator_type())
  , __size(0)
  , __capacity(0)
  , __data(NULL) {
} catch (...) {
	(void)x;
}
template< typename _Tp, typename _Allocator >
THIS&
THIS::operator=(const vector& x) {
	(void)x;
}
template< typename _Tp, typename _Allocator >
THIS::~vector() {
	if (std::uncaught_exceptions() == true) {
		LOG_("destructor called during stack unwinding");
	} else {
		LOG_("destructor called normally");
	}
	if (__data) {
		clear();
		__alloc.deallocate(__data, __capacity * sizeof(value_type));
	}
}

/**
 * * [ allocator ] ---------------------------------------------------------------------------------
 */

/**
 * * [ element access ] ----------------------------------------------------------------------------
 */

/**
 * * [ iterators ] ---------------------------------------------------------------------------------
 */
// reverse_iterator
// rbegin();
// reverse_iterator
// rend();
// const_reverse_iterator
// rbegin() const;
// const_reverse_iterator
// rend() const;

/**
 * * [ capacity ] ----------------------------------------------------------------------------------
 */
// template< typename _Tp, typename _Allocator >
// void
// THIS::reserve(size_type n) {
// 	if (n > max_size()) {
// 		throw std::length_error("vector::reserve");
// 	}
// 	if (n > capacity()) {
// 		try {
// 		} catch (const std::exception& e) {
// 		} catch (...) {
// 		}
// 	}
// }

/**
 * * [ modifiers ] ---------------------------------------------------------------------------------
 */
template< typename _Tp, typename _Allocator >
void
THIS::clear() {
	size_type i = __size;
	while (i--) {
		__alloc.destroy(__data + i);
	}
	__size = 0;
}

/**
 * * [ internal workhorse ] ------------------------------------------------------------------------
 */

} /* namespace ft */
#endif /* __VECTOR_HPP__ */
