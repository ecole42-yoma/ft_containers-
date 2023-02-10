#pragma once
#ifndef __IS_FUNCTION_HPP__
#define __IS_FUNCTION_HPP__

#include "integral_constant.hpp"
#include "is_const.hpp"
#include "is_reference.hpp"

namespace ft {

template< typename _Tp >
struct is_function : public ft::bool_constant< !(ft::is_reference< _Tp >::value || ft::is_const< _Tp >::value) > {};

}
#endif
