#pragma once

#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

#include "../type/_type_traits.hpp"
#include "has_iterator_x.hpp"
#include "is_iterator_x.hpp"
#include "iterator.hpp"
#include "iterator_tag.hpp"

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
// template< typename _Iter > // XXX: need to check if this is needed
// struct iterator_traits< const _Iter* > {
// 	typedef ptrdiff_t				   difference_type;
// 	typedef _Iter					   value_type;
// 	typedef const value_type*		   pointer;
// 	typedef const value_type&		   reference;
// 	typedef random_access_iterator_tag iterator_category;
// };

template< class _InputIter >
inline typename iterator_traits< _InputIter >::difference_type
__distance(_InputIter __first, _InputIter __last, input_iterator_tag) {
	typename iterator_traits< _InputIter >::difference_type __r(0);
	for (; __first != __last; ++__first)
		++__r;
	return __r;
}

template< class _RandIter >
inline typename iterator_traits< _RandIter >::difference_type
__distance(_RandIter __first, _RandIter __last, random_access_iterator_tag) {
	return __last - __first;
}

template< class _InputIter >
inline typename iterator_traits< _InputIter >::difference_type
distance(_InputIter __first, _InputIter __last) {
	return __distance(__first, __last, typename iterator_traits< _InputIter >::iterator_category());
}

}
#endif
