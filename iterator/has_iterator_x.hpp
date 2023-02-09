#pragma once
#ifndef __HAS_ITERATOR_X_HPP__
#define __HAS_ITERATOR_X_HPP__

#include "../type/_type_traits.hpp"
#include <cstddef>

namespace ft {

template< typename _Iter >
struct iterator_traits;

/**
 * * [ has iterator typedefs ] ---------------------------------------------------------------------
 */
template< typename _Tp >
struct has_iterator_typedefs {
	private:
	typedef char (&__true)[1];
	typedef char (&__false)[2];
	template< typename _Up >
	static __false test__(...);
	template< typename _Up >
	static __true test__(typename ft::void_t< typename _Up::iterator_category >::type* = 0,
						 typename ft::void_t< typename _Up::difference_type >::type*   = 0,
						 typename ft::void_t< typename _Up::value_type >::type*		   = 0,
						 typename ft::void_t< typename _Up::reference >::type*		   = 0,
						 typename ft::void_t< typename _Up::pointer >::type*		   = 0);

	public:
	static const bool value = sizeof(test__< _Tp >(0, 0, 0, 0, 0)) == sizeof(__true);
};

/**
 * * [ has iterator category ] ---------------------------------------------------------------------
 */
template< typename _Tp >
struct has_iterator_category {
	private:
	typedef char (&__true)[1];
	typedef char (&__false)[2];
	template< typename _Up >
	static __false test__(...);
	template< typename _Up >
	static __true test__(typename _Up::iterator_category* = NULL);

	public:
	static const bool value = sizeof(test__< _Tp >(NULL)) == sizeof(__true);
};

/**
 * * [ has iterator category convertible to] -------------------------------------------------------
 */
template< typename _Tp, typename _Up, bool = has_iterator_category< iterator_traits< _Tp > >::value >
struct has_iterator_category_convertible_to
  : ft::is_convertible< typename iterator_traits< _Tp >::iterator_category, _Up > {};
template< typename _Tp, typename _Up >
struct has_iterator_category_convertible_to< _Tp, _Up, false > : ft::false_type {};

}
#endif
