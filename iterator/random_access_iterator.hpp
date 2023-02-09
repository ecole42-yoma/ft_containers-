#pragma once
#ifndef __RANDOM__ACCESS__ITERATOR_HPP__
#define __RANDOM__ACCESS__ITERATOR_HPP__

#include "_iterator_traits.hpp"

namespace ft {
//
template< typename _Iter >
// class randomIterator { // for primitive alloc pointer
// public:
// 	typedef _Iter															 iterator_type;
class randomIterator : public ft::iterator< ft::random_access_iterator_tag, _Iter > {
	public:
	typedef randomIterator< _Iter >											 iterator_type;
	typedef typename ft::iterator_traits< iterator_type >::iterator_category iterator_category;
	typedef typename ft::iterator_traits< iterator_type >::value_type		 value_type;
	typedef typename ft::iterator_traits< iterator_type >::difference_type	 difference_type;
	typedef typename ft::iterator_traits< iterator_type >::pointer			 pointer;
	typedef typename ft::iterator_traits< iterator_type >::reference		 reference;

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

}

#endif
