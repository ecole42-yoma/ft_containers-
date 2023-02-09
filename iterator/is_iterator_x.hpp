#pragma once
#ifndef __IS_ITERATOR_X_HPP__
#define __IS_ITERATOR_X_HPP__

#include "has_iterator_x.hpp"
#include "iterator_tag.hpp"

namespace ft {

template< typename _Iter >
struct is_iterator : has_iterator_typedefs< _Iter > {};

template< typename _Iter >
struct is_iterator_of_input : ft::has_iterator_category_convertible_to< _Iter, ft::input_iterator_tag > {};

template< typename _Iter >
struct is_iterator_of_output : ft::has_iterator_category_convertible_to< _Iter, ft::output_iterator_tag > {};

template< typename _Iter >
struct is_iterator_of_forward : ft::has_iterator_category_convertible_to< _Iter, ft::forward_iterator_tag > {};

template< typename _Iter >
struct is_iterator_of_bidirectional
  : ft::has_iterator_category_convertible_to< _Iter, ft::bidirectional_iterator_tag > {};

template< typename _Iter >
struct is_iterator_of_random : ft::has_iterator_category_convertible_to< _Iter, ft::random_access_iterator_tag > {};

}
#endif
