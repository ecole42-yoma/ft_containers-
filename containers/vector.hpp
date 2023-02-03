#pragma once

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <memory>

#ifdef LOG
#include <iostream>
#endif

namespace ft {

template< class T, class Allocator = std::allocator< T > >
class vector {

	public:
	typedef T										 value_type;
	typedef Allocator								 allocator_type;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::size_type		 size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef pointer									 iterator;
	typedef const_pointer							 const_iterator;
	typedef std::reverse_iterator< iterator >		 reverse_iterator;
	typedef std::reverse_iterator< const_iterator >	 const_reverse_iterator;

	private:
	Allocator m_alloc_;
	size_type m_size_;
	size_type m_capacity_;
	pointer	  m_data_;

	/**
	 * * [ default form] ---------------------------------------------------------------------------
	 */
	public:
	explicit vector(const allocator_type& alloc = allocator_type()); // default
	explicit vector(size_type			  n,
					const value_type&	  val	= value_type(),
					const allocator_type& alloc = allocator_type()); // fill
	template< class InputIterator >
	vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type()); // range
	vector(const vector& x);																   // copy
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
}; /* class vector */

/**
 * * [ non-member function overloads ] -------------------------------------------------------------
 */
template< class T, class Alloc >
bool
operator==(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs);

template< class T, class Alloc >
bool
operator!=(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs);

template< class T, class Alloc >
bool
operator<(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs);

template< class T, class Alloc >
bool
operator<=(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs);

template< class T, class Alloc >
bool
operator>(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs);

template< class T, class Alloc >
bool
operator>=(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs);

template< class T, class Alloc >
void
swap(ft::vector< T, Alloc >& lhs, ft::vector< T, Alloc >& rhs);

} /* namespace ft */

#endif /* __VECTOR_HPP__ */
