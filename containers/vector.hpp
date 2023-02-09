#pragma once

#include <exception>
#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#ifdef BASIC
#include "_core_utils.hpp"
#include "_type_traits.hpp"
#include "reverse_iterator.hpp"
#else
#include "../iterator/_iterator.hpp"
#include "../iterator/_iterator_traits.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../type/_type_traits.hpp"
#include "../util/_core_utils.hpp"
#endif

#ifdef LOG
#include <iostream>
#endif

#define THIS vector< _Tp, _Allocator >

namespace ft {

template< typename Vector >
class randomIterator : ft::iterator< ft::random_access_iterator_tag, typename Vector::value_type > {

	public:
	typedef typename randomIterator::value_type		value_type;
	typedef typename randomIterator::pointer_type	pointer_type;
	typedef typename randomIterator::reference_type reference_type;

	private:
	pointer_type m_pointer;

	public:
	randomIterator(pointer_type input_pointer = NULL)
	  : m_pointer(input_pointer) {}

	randomIterator& operator++() {
		++m_pointer;
		return *this;
	}

	randomIterator operator++(int) {
		randomIterator tmp = *this;
		++(*this);
		return tmp;
	}

	randomIterator& operator--() {
		--m_pointer;
		return *this;
	}

	randomIterator operator--(int) {
		randomIterator tmp = *this;
		--(*this);
		return tmp;
	}

	reference_type operator[](int index) { return m_pointer[index]; }
	pointer_type   operator->() { return m_pointer; }
	reference_type operator*() { return *m_pointer; }

	bool operator==(const randomIterator& rhs) const { return m_pointer == rhs.m_pointer; }
	bool operator!=(const randomIterator& rhs) const { return !(*this == rhs); }
	// if integral type then allow <=, >=, <, >

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
	_Allocator m_alloc;
	size_type  m_size;
	size_type  m_capacity;
	pointer	   m_data;
	int		   m_u_c;

	/**
	 * * [ default form] ---------------------------------------------------------------------------
	 */
	public:
	vector();
	explicit vector(const allocator_type& alloc); // default
	explicit vector(size_type			  n,
					const value_type&	  val	= value_type(),
					const allocator_type& alloc = allocator_type()); // fill
	template< class _InputIterator >
	vector(_InputIterator first, _InputIterator last, const allocator_type& alloc = allocator_type()); // range
	vector(const vector& x);																		   // copy

	~vector();
	vector& operator=(const vector& x);

	/**
	 * * [ allocator ] -----------------------------------------------------------------------------
	 */
	allocator_type get_allocator() const;

	/**
	 * * [ element access ] ------------------------------------------------------------------------
	 */
	reference		at(size_type n);
	const_reference at(size_type n) const;
	reference		operator[](size_type n);
	const_reference operator[](size_type n) const;

	reference		front();
	const_reference front() const;
	reference		back();
	const_reference back() const;

	value_type*		  data();
	const value_type* data() const;

	/**
	 * * [ iterators ] -----------------------------------------------------------------------------
	 */
	iterator			   begin();
	iterator			   end();
	const_iterator		   begin() const;
	const_iterator		   end() const;
	reverse_iterator	   rbegin();
	reverse_iterator	   rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;

	/**
	 * * [ capacity ] ------------------------------------------------------------------------------
	 */
	size_type size() const;
	size_type max_size() const;
	size_type capacity() const;
	bool	  empty() const;
	void	  reserve(size_type n);

	/**
	 * * [ modifiers ] -----------------------------------------------------------------------------
	 */
	template< class InputIterator >
	void assign(InputIterator first, InputIterator last);
	void assign(size_type n, const value_type& u);

	void push_back(const value_type& x);
	void pop_back();

	iterator insert(const_iterator position, const value_type& x);
	iterator insert(const_iterator position, size_type n, const value_type& x);
	template< class InputIterator >
	iterator insert(const_iterator position, InputIterator first, InputIterator last);
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last);

	void clear();

	void swap(vector& x);

	void resize(size_type sz, value_type c = value_type());

	bool __invariants() const;

	/**
	 * * [ internal workhorse ] --------------------------------------------------------------------
	 */

}; /* class vector */

/**
 * * [ non-member function overloads ] -------------------------------------------------------------
 */
template< class _Tp, class _Allocator >
bool
operator==(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);

template< class _Tp, class _Allocator >
bool
operator!=(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);

template< class _Tp, class _Allocator >
bool
operator<(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);

template< class _Tp, class _Allocator >
bool
operator<=(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);

template< class _Tp, class _Allocator >
bool
operator>(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);

template< class _Tp, class _Allocator >
bool
operator>=(const ft::vector< _Tp, _Allocator >& lhs, const ft::vector< _Tp, _Allocator >& rhs);

template< class _Tp, class _Allocator >
void
swap(ft::vector< _Tp, _Allocator >& lhs, ft::vector< _Tp, _Allocator >& rhs);

/**
 * * [ default form] -------------------------------------------------------------------------------
 */
template< typename _Tp, typename _Allocator >
THIS::vector() // default
  try
  : m_alloc(allocator_type())
  , m_size(0)
  , m_capacity(0)
  , m_data(NULL)
  , m_u_c(std::uncaught_exceptions()) {
} catch (...) {
}

template< typename _Tp, typename _Allocator >
THIS::vector(const allocator_type& alloc) // default
  try
  : m_alloc(alloc)
  , m_size(0)
  , m_capacity(0)
  , m_data(NULL)
  , m_u_c(std::uncaught_exceptions()) {
} catch (...) {
}

template< typename _Tp, typename _Allocator >
THIS::vector(size_type			   n,
			 const value_type&	   val,
			 const allocator_type& alloc) // fill
  try
  : m_alloc(alloc)
  , m_size(0)
  , m_capacity(0)
  , m_data(NULL)
  , m_u_c(std::uncaught_exceptions()) {
	if (n > 0) {
		m_data	   = m_alloc.allocate(n);
		m_capacity = n;
		m_size	   = n;
		for (size_type i = 0; i < n; ++i) {
			m_alloc.construct(m_data[i], val);
		}
	}
} catch (...) {
}

template< typename _Tp, typename _Allocator >
template< class _InputIterator >
THIS::vector(_InputIterator first, _InputIterator last, const allocator_type& alloc) // range
  try
  : m_alloc(alloc)
  , m_size(0)
  , m_capacity(0)
  , m_data(NULL)
  , m_u_c(std::uncaught_exceptions()) {
} catch (...) {
}

template< typename _Tp, typename _Allocator >
THIS::vector(const vector& x) // copy
  try
  : m_alloc(allocator_type())
  , m_size(0)
  , m_capacity(0)
  , m_data(NULL)
  , m_u_c(std::uncaught_exceptions()) {
} catch (...) {
}

template< typename _Tp, typename _Allocator >
THIS&
THIS::operator=(const vector& x) {}

template< typename _Tp, typename _Allocator >
THIS::~vector() {
#ifdef LOG
	if (m_uncaught_exceptions != std::uncaught_exceptions()) {
		std::cout << "~vector() called during stack unwinding" << std::endl;
	} else {
		std::cout << "~vector() called normally" << std::endl;
	}
#endif

	if (m_data) {
		clear();
		m_alloc.deallocate(m_data, m_capacity * sizeof(value_type));
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
template< typename _Tp, typename _Allocator >
typename THIS::iterator
THIS::begin() {
	return iterator(m_data);
}

template< typename _Tp, typename _Allocator >
typename THIS::iterator
THIS::end() {
	return iterator(m_data + m_size);
}

template< typename _Tp, typename _Allocator >
typename THIS::const_iterator
THIS::begin() const {
	return iterator(m_data);
}

template< typename _Tp, typename _Allocator >
typename THIS::const_iterator
THIS::end() const {
	return iterator(m_data + m_size);
}

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

/**
 * * [ modifiers ] ---------------------------------------------------------------------------------
 */

/**
 * * [ internal workhorse ] ------------------------------------------------------------------------
 */
} /* namespace ft */
#endif /* __VECTOR_HPP__ */
