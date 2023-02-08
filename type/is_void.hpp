#pragma once
#ifndef __IS_VOID_HPP__
#define __IS_VOID_HPP__

#include "integral_constant.hpp"

namespace ft {

template< typename _Tp >
struct is_void : public ft::false_type {};

template<>
struct is_void< void > : public ft::true_type {};

template< typename >
struct void_t {
	typedef void type;
};

}
#endif
