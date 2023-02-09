#pragma once

#include <memory>
#include <stdexcept>
#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#ifdef BASIC
#include "_core_utils.hpp"
#include "_iterator_traits.hpp"
#include "_type_traits.hpp"
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#else
#include "../iterator/_iterator_traits.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/random_access_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../type/_type_traits.hpp"
#include "../util/_core_utils.hpp"
#endif

#include <iostream>

#define __vector__			 vector< _Tp, _Alloc >
#define __template__		 template< typename _Tp, typename _Alloc >
#define __template_iter__	 template< typename _Iter >
#define __template_input__	 template< typename _Input >
#define __template_forward__ template< typename _Forward >
#define __return__(type)	 type

namespace ft {

template< typename _Tp, typename _Alloc = std::allocator< _Tp > >
class vector {
	public:
	typedef vector< _Tp, _Alloc >					 self_type;
	typedef _Tp										 value_type;
	typedef _Alloc									 allocator_type;
	typedef typename allocator_type::size_type		 size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef randomIterator< pointer >				 iterator;
	typedef const randomIterator< pointer >			 const_iterator;
	typedef ft::reverse_iterator< iterator >		 reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >	 const_reverse_iterator;

	private:
	allocator_type __alloc;
	size_type	   __size;
	size_type	   __capacity;
	pointer		   __data;

	/**
	 * * [ default form] ---------------------------------------------------------------------------
	 */
	public:
	explicit vector(const allocator_type& alloc = allocator_type()); // default
	explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()); // fill

	__template_input__ vector(
	  _Input																										first,
	  typename ft::enable_if< !ft::is_integral< _Input >::value && ft::is_iterator< _Input >::value, _Input >::type last,
	  const allocator_type& alloc = std::allocator< typename ft::iterator_traits< _Input >::value_type >()); // range

	vector(const vector& from); // copy
	~vector();
	vector& operator=(const vector& from);

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
	void					   assign(InputIterator first, InputIterator last);
	void					   assign(size_type n, const value_type& u);
	void					   push_back(const value_type& x);
	void					   pop_back();
	iterator				   insert(const_iterator position, const value_type& x);
	iterator				   insert(const_iterator position, size_type n, const value_type& x);
	__template_iter__ iterator insert(const_iterator position, _Iter first, _Iter last);
	iterator				   erase(iterator position);
	iterator				   erase(iterator first, iterator last);
	void					   clear();
	void					   swap(vector& x);
	void					   resize(size_type sz, value_type c = value_type());

	/**
	 * * [ internal workhorse ] --------------------------------------------------------------------
	 */
	protected:
	inline bool invariants_size__() const;
	inline bool invariants_capacity__() const;
}; /* class vector */

/**
 * * [ non-member function overloads ] -------------------------------------------------------------
 */
__template__
__return__(bool)
operator==(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs);
__template__
__return__(bool)
operator!=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs);
__template__
__return__(bool)
operator<(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs);
__template__
__return__(bool)
operator<=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs);
__template__
__return__(bool)
operator>(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs);
__template__
__return__(bool)
operator>=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs);
__template__
__return__(void) swap(ft::vector< _Tp, _Alloc >& lhs, ft::vector< _Tp, _Alloc >& rhs);

/**
 * * [ default form] -------------------------------------------------------------------------------
 */
__template__
__vector__::vector(const allocator_type& alloc) // default
  try
  : __alloc(alloc)
  , __size(0)
  , __capacity(0)
  , __data(NULL) {
	LOG_("default constructor");
} catch (...) {
}

__template__
__vector__::vector(size_type			 n,
				   const value_type&	 val,
				   const allocator_type& alloc) // fill
  try
  : __alloc(alloc)
  , __size(n)
  , __capacity(n)
  , __data(NULL) {
	LOG_("fill constructor");
	if (n > 0) {
		__data	   = __alloc.allocate(n * sizeof(value_type));
		__capacity = n;
		__size	   = n;
		for (size_type i = 0; i < n; ++i) {
			__alloc.construct(__data + i, val);
		}
	}
} catch (const std::exception& e) {
} catch (...) {
}

__template__ __template_input__
__vector__::vector(_Input																										 first,
				   typename ft::enable_if< !ft::is_integral< _Input >::value && ft::is_iterator< _Input >::value, _Input >::type last,
				   const allocator_type& alloc) // range
  try
  : __alloc(alloc)
  , __size(0)
  , __capacity(0)
  , __data(NULL) {
	LOG_("range constructor : input iterator");
	(void)first;
	(void)last;
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
} catch (...) {
}

// __template__ __template_iter__
// __vector__::vector(typename ft::enable_if< ft::is_iterator< _Iter >::value, _Iter >::type first,
// 				   _Iter																  last,
// 				   const allocator_type&												  alloc) // range
//   try
//   : __alloc(alloc)
//   , __size(0)
//   , __capacity(0)
//   , __data(NULL) {
// 	LOG_("range constructor");
// 	(void)first;
// 	(void)last;
// } catch (const std::exception& e) {
// 	std::cerr << e.what() << std::endl;
// } catch (...) {
// }
__template__
__vector__::vector(const vector& from) // copy
  try
  : __alloc(allocator_type())
  , __size(0)
  , __capacity(0)
  , __data(NULL) {
} catch (...) {
	(void)from;
}

__template__
__return__(__vector__&) __vector__::operator=(const vector& from) {
	LOG_("copy assignment operator");
	if (this != &from) {
		this->~vector();
		if (from.size() > 0) { // TODO: make to __function, check how to  unalloc copy
			__data	   = __alloc.allocate(from.size() * sizeof(value_type));
			__capacity = from.size();
			__size	   = from.size();
			for (size_type i = 0; i < from.size(); ++i) {
				__alloc.construct(__data + i, from[i]);
			}
		}
	}
	return *this;
}
__template__
__return__() __vector__::~vector() {
	if (std::uncaught_exceptions() == true) {
		LOG_("called during stack unwinding");
	} else {
		LOG_("called normally");
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
__template__
__return__() typename __vector__::reference __vector__::operator[](size_type n) {
	if (n >= __size) {
		// throw std::out_of_range("vector::operator[]");
		throw std::range_error("vector::operator[]");
	}
	return __data[n];
}

__template__
__return__() typename __vector__::const_reference __vector__::operator[](size_type n) const {
	if (n >= __size) {
		// throw std::out_of_range("vector::operator[]");
		throw std::range_error("vector::operator[]");
	}
	return __data[n];
}
// const_reference
// operator[](size_type n) const;

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
// __template__
// void
// __vector__::reserve(size_type n) {
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
__template__
__return__(void) __vector__::clear() {
	while (__size--) {
		__alloc.destroy(&__data[__size]);
	}
}

/**
 * * [ internal workhorse ] ------------------------------------------------------------------------
 */

} /* namespace ft */
#endif /* __VECTOR_HPP__ */
