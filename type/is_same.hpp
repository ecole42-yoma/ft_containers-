#pragma once
#ifndef __IS_SAME_HPP__
#define __IS_SAME_HPP__

#include "integral_constant.hpp"

namespace ft {

template< typename _Tp, typename _Up >
struct is_same : ft::false_type {};

template< typename _Tp >
struct is_same< _Tp, _Tp > : ft::true_type {};

}
#endif
