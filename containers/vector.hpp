#pragma once

#include <exception>
#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#ifdef BASIC
#include "_core_utils.hpp"
#include "_type_traits.hpp"
#include "reverse_iterator.hpp"
#else
#include "../iterator/reverse_iterator.hpp"
#include "../type/_type_traits.hpp"
#include "../util/_core_utils.hpp"
#endif

#ifdef LOG
#include <iostream>
#endif

namespace ft {

template< class _Tp, class _Allocator = std::allocator< _Tp > >
class vector {

	public:
	typedef _Tp										 value_type;
	typedef _Allocator								 allocator_type;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::size_type		 size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef pointer									 iterator;
	typedef const_pointer							 const_iterator;
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
	vector(_InputIterator first, _InputIterator last, const allocator_type& = allocator_type()); // range
	vector(const vector& x);																	 // copy
	~vector() {
#ifdef LOG
		if (m_uncaught_exceptions != std::uncaught_exceptions()) {
			std::cout << "~vector() called during stack unwinding" << std::endl;
		} else {
			std::cout << "~vector() called normally" << std::endl;
		}
#endif
	};
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
}; /* class vector */

template< typename _Tp, typename _Allocator >
ft::vector< _Tp, _Allocator >::vector(const allocator_type& alloc) // default
  try
  : m_alloc(alloc)
  , m_size(0)
  , m_capacity(0)
  , m_data(NULL)
  , m_u_c(std::uncaught_exceptions()) {
} catch (...) {
}

template< typename _Tp, typename _Allocator >
ft::vector< _Tp, _Allocator >::vector(size_type				n,
									  const value_type&		val,
									  const allocator_type& alloc) // fill
  try
  : m_alloc(alloc)
  , m_size(0)
  , m_capacity(0)
  , m_data(NULL)
  , m_u_c(std::uncaught_exceptions()) {
	if (n > 0) {
	}
} catch (...) {
}

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

} /* namespace ft */

#endif /* __VECTOR_HPP__ */
