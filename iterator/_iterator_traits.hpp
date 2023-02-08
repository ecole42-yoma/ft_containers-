#pragma once

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

#include "../type/_type_traits.hpp"
#include <cstddef>

namespace ft {

/**
 * * [ iterator_traits forward declare ] -----------------------------------------------------------
 */
template< class _Iter >
struct iterator_traits;

/**
 * * [ iterator category ] -------------------------------------------------------------------------
 */
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/**
 * * [ has iterator_typedefs , has iterator_category ] ---------------------------------------------
 */
template< class _Tp >
struct __has_iterator_typedefs {
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
struct __has_iterator_category {
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

template< class _Tp, class _Up, bool = __has_iterator_category< iterator_traits< _Tp > >::value >
struct __has_iterator_category_convertible_to
  : ft::is_convertible< typename iterator_traits< _Tp >::iterator_category, _Up > {};

template< class _Tp, class _Up >
struct __has_iterator_category_convertible_to< _Tp, _Up, false > : ft::false_type {};

/**
 * * [ iterator_traits ] ---------------------------------------------------------------------------
 */
template< class _Iter, bool >
struct __iterator_traits_work {};
template< class _Iter >
struct __iterator_traits_work< _Iter, true > {
	typedef typename _Iter::difference_type	  difference_type;
	typedef typename _Iter::value_type		  value_type;
	typedef typename _Iter::pointer			  pointer;
	typedef typename _Iter::reference		  reference;
	typedef typename _Iter::iterator_category iterator_category;
};

template< class _Iter >
struct iterator_traits
  : __iterator_traits_work< _Iter,
							__has_iterator_typedefs< _Iter >::value &&
							  (ft::is_convertible< typename _Iter::iterator_category, input_iterator_tag >::value ||
							   ft::is_convertible< typename _Iter::iterator_category, output_iterator_tag >::value) > {
};

template< class _Tp >
struct iterator_traits< _Tp* > {
	typedef ptrdiff_t						difference_type;
	typedef typename remove_cv< _Tp >::type value_type;
	typedef _Tp*							pointer;
	typedef _Tp&							reference;
	typedef random_access_iterator_tag		iterator_category;
};

}
#endif
