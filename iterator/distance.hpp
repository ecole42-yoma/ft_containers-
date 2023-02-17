#pragma once
#ifndef __DISTANCE_HPP__
#define __DISTANCE_HPP__

#include "_iterator_traits.hpp"

namespace ft {

template< class _InputIter >
inline typename ft::iterator_traits< _InputIter >::difference_type
__distance(_InputIter __first, _InputIter __last, std::input_iterator_tag) {
	typename ft::iterator_traits< _InputIter >::difference_type __r(0);
	for (; __first != __last; ++__first)
		++__r;
	return __r;
}

template< class _RandIter >
inline typename ft::iterator_traits< _RandIter >::difference_type
__distance(_RandIter __first, _RandIter __last, std::random_access_iterator_tag) {
	return (__last - __first);
}

template< class _InputIter >
inline typename ft::iterator_traits< _InputIter >::difference_type
distance(_InputIter __first, _InputIter __last) {
	return ft::__distance(__first, __last, typename ft::iterator_traits< _InputIter >::iterator_category());
}

}

#endif
