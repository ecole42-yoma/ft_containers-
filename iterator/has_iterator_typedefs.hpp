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

template< class _Tp >
struct has_iterator_category {
	private:
	typedef char (&__true)[1];
	typedef char (&__false)[2];

	template< class _Up >
	static __false __test(...);
	template< class _Up >
	static __true __test(typename _Up::iterator_category* = NULL);

	public:
	static const bool value = sizeof(__test< _Tp >(NULL)) == true;
};

template< class _Tp, class _Up, bool = has_iterator_category< iterator_traits< _Tp > >::value >
struct __has_iterator_category_convertible_to
  : ft::is_convertible< typename iterator_traits< _Tp >::iterator_category, _Up > {};

template< class _Tp, class _Up >
struct __has_iterator_category_convertible_to< _Tp, _Up, false > : ft::false_type {};

}
#endif
