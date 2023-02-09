#pragma once
#ifndef __IS_ITERATOR_HPP__
#define __IS_ITERATOR_HPP__

#include "has_iterator_x.hpp"

namespace ft {

template< typename _Iter >
struct is_iterator : has_iterator_typedefs< _Iter > {};

}
#endif
