#pragma once
#ifndef __IS_CONST_HPP__
#define __IS_CONST_HPP__

#include "integral_constant.hpp"

namespace ft {
template< typename _Tp >
struct is_const : ft::false_type {};

template< typename _Tp >
struct is_const< const _Tp > : ft::true_type {};

}

#endif
