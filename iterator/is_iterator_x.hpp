#pragma once
#ifndef __IS_ITERATOR_X_HPP__
#define __IS_ITERATOR_X_HPP__

#include "has_iterator_x.hpp"
#include <iterator>

namespace ft {

template< typename _Iter >
struct is_iterator : has_iterator_typedefs< _Iter > {};

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

}
#endif
