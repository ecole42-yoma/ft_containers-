#pragma once
#ifndef __IS_ITERATOR_X_HPP__
#define __IS_ITERATOR_X_HPP__

#include "../type/_type_traits.hpp"
#include "_iterator_traits.hpp"
#include "has_iterator_x.hpp"

#include <cstddef>
#include <iterator>

namespace ft {

template< typename _Iter >
struct is_iterator : has_iterator_typedefs< ft::iterator_traits< _Iter > > {};

/**
 * * [ is iterator of X ] --------------------------------------------------------------------------
 */
template< typename _Iter >
struct is_iterator_of_input
  : ft::bool_constant<
	  ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category, std::input_iterator_tag >::value > {};

template< typename _Iter >
struct is_iterator_of_output
  : ft::bool_constant<
	  ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category, std::output_iterator_tag >::value > {};

template< typename _Iter >
struct is_iterator_of_forward
  : ft::bool_constant<
	  ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category, std::forward_iterator_tag >::value > {};

template< typename _Iter >
struct is_iterator_of_bidirectional
  : ft::bool_constant< ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category,
									std::bidirectional_iterator_tag >::value > {};

template< typename _Iter >
struct is_iterator_of_random
  : ft::bool_constant< ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category,
									std::random_access_iterator_tag >::value > {};

/**
 * * [ is iterator category convertible to] --------------------------------------------------------
 */

template< typename _Tp, typename _Up >
struct is_iterator_category_convertible_to
  : ft::is_convertible< typename ft::iterator_traits< _Tp >::iterator_category, _Up > {};

}

#endif
