#pragma once
#ifndef __HAS_ITERATOR_TYPEDEFS_HPP__
#define __HAS_ITERATOR_TYPEDEFS_HPP__

#include "../type/_type_traits.hpp"
#include <cstddef>

namespace ft {

template< class _Iter >
struct iterator_traits;

template< class _Tp >
struct has_iterator_typedefs {
	private:
	typedef char (&__true)[1];
	typedef char (&__false)[2];

	template< class _Up >
	static __false __test(...);
	template< class _Up >
	static __true __test(typename ft::void_t< typename _Up::iterator_category >::type* = 0,
						 typename ft::void_t< typename _Up::difference_type >::type*   = 0,
						 typename ft::void_t< typename _Up::value_type >::type*		   = 0,
						 typename ft::void_t< typename _Up::reference >::type*		   = 0,
						 typename ft::void_t< typename _Up::pointer >::type*		   = 0);

	public:
	static const bool value = sizeof(__test< _Tp >(0, 0, 0, 0, 0)) == true;
};

}
#endif
