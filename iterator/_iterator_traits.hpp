#pragma once

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

#include "../type/_type_traits.hpp"
#include "has_iterator_category.hpp"
#include "has_iterator_typedefs.hpp"

#include <cstddef>

namespace ft {

/**
 * * [ iterator category ] -------------------------------------------------------------------------
 */
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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
							has_iterator_typedefs< _Iter >::value &&
							  (ft::is_convertible< typename _Iter::iterator_category, input_iterator_tag >::value ||
							   ft::is_convertible< typename _Iter::iterator_category, output_iterator_tag >::value) > {
};

template< class _Tp >
struct iterator_traits< _Tp* > {
	typedef ptrdiff_t				   difference_type;
	typedef _Tp						   value_type;
	typedef value_type*				   pointer;
	typedef value_type&				   reference;
	typedef random_access_iterator_tag iterator_category;
};

template< class _Tp >
struct iterator_traits< const _Tp* > {
	typedef ptrdiff_t				   difference_type;
	typedef _Tp						   value_type;
	typedef const value_type*		   pointer;
	typedef const value_type&		   reference;
	typedef random_access_iterator_tag iterator_category;
};

}
#endif
