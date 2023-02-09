#pragma once
#ifndef __IS_ITERATOR_HPP__
#define __IS_ITERATOR_HPP__

#include "has_iterator_typedefs.hpp"

namespace ft {

template< class _Iter >
struct iterator_traits;

// template< bool, typename _Tp >
// struct is_iterator : ft::false_type {};

template< typename _Iter >
struct is_iterator : has_iterator_typedefs< _Iter > {};

}
#endif
