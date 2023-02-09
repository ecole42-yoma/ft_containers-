#pragma once

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

#include "../type/_type_traits.hpp"
#include "_iterator.hpp"
#include "has_iterator_x.hpp"
#include "is_iterator.hpp"

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
template< typename _Iter >
struct iterator_traits
  : __iterator_traits_work< _Iter,
							has_iterator_typedefs< _Iter >::value &&
							  (ft::is_convertible< typename _Iter::iterator_category, input_iterator_tag >::value ||
							   ft::is_convertible< typename _Iter::iterator_category, output_iterator_tag >::value) > {
};
template< typename _Iter >
struct iterator_traits< _Iter* > {
	typedef ptrdiff_t				   difference_type;
	typedef _Iter					   value_type;
	typedef value_type*				   pointer;
	typedef value_type&				   reference;
	typedef random_access_iterator_tag iterator_category;
};

}
#endif
