#pragma once
#ifndef __IS_ITERATOR_X_HPP__
#define __IS_ITERATOR_X_HPP__

#include "has_iterator_x.hpp"
#include "iterator_tag.hpp"

namespace ft {

template< typename _Iter >
struct is_iterator : has_iterator_typedefs< _Iter > {};

template< typename _Iter >
struct is_iterator_of_input
  : ft::bool_constant<
	  ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category, ft::input_iterator_tag >::value > {};
// : ft::bool_constant< ft::is_same< typename ft::true_type::type, typename is_iterator< _Iter >::type >::value >
// {};
//: ft::has_iterator_category_convertible_to< _Iter, ft::input_iterator_tag > {};
template< typename _Iter >
struct is_iterator_of_output
  : ft::bool_constant<
	  ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category, ft::output_iterator_tag >::value > {};
template< typename _Iter >
struct is_iterator_of_forward
  : ft::bool_constant<
	  ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category, ft::forward_iterator_tag >::value > {};
template< typename _Iter >
struct is_iterator_of_bidirectional
  : ft::bool_constant<
	  ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category, ft::bidirectional_iterator_tag >::value > {
};
template< typename _Iter >
struct is_iterator_of_random
  : ft::bool_constant<
	  ft::is_same< typename ft::iterator_traits< _Iter >::iterator_category, ft::random_access_iterator_tag >::value > {
};

}
#endif
