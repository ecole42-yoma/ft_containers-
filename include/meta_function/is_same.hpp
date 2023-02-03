#pragma once
#ifndef __IS_SAME_HPP__
#define __IS_SAME_HPP__

#include "integral_constant.hpp"

namespace ft {

// is_same
template< typename _Tp, typename _Up >
struct is_same : public ft::false_type {};

template< typename _Tp >
struct is_same< _Tp, _Tp > : public ft::true_type {};

}
#endif
