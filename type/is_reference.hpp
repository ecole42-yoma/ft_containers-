#pragma once
#ifndef __IS_REFERENCE_HPP__
#define __IS_REFERENCE_HPP__

#include "integral_constant.hpp"

namespace ft {
template< typename _Tp >
struct is_reference : ft::false_type {};

template< typename _Tp >
struct is_reference< _Tp& > : ft::true_type {};

}

#endif
