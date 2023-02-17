#pragma once

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

#include "../type/_type_traits.hpp"
#include "has_iterator_x.hpp"
#include "is_iterator_x.hpp"
#include "iterator.hpp"

#include <cstddef>

namespace ft {

/**
 * * [ iterator_traits ] ---------------------------------------------------------------------------
 */
template< typename _Iter, bool >
struct __iterator_traits_work {};

template< typename _Iter >
struct __iterator_traits_work< _Iter, true > {
	typedef typename _Iter::difference_type	  difference_type;
	typedef typename _Iter::value_type		  value_type;
	typedef typename _Iter::pointer			  pointer;
	typedef typename _Iter::reference		  reference;
	typedef typename _Iter::iterator_category iterator_category;
};

template< typename _Iter, bool >
struct __iterator_traits {};

template< typename _Iter >
struct __iterator_traits< _Iter, true >
  : __iterator_traits_work< _Iter, ft::__has_iterator_category< _Iter >::value > {};

template< typename _Iter >
struct iterator_traits : __iterator_traits< _Iter, ft::has_iterator_typedefs< _Iter >::value > {};

template< typename _Iter >
struct iterator_traits< _Iter* > {
	typedef std::ptrdiff_t					difference_type;
	typedef _Iter							value_type;
	typedef value_type*						pointer;
	typedef value_type&						reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template< typename _Iter > // XXX: need to check if this is needed
struct iterator_traits< const _Iter* > {
	typedef std::ptrdiff_t						  difference_type;
	typedef typename ft::remove_cv< _Iter >::type value_type;
	typedef const value_type*					  pointer;
	typedef const value_type&					  reference;
	typedef std::random_access_iterator_tag		  iterator_category;
};

}
#endif
