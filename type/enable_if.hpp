#pragma once
#ifndef __ENABLE_IF_HPP__
#define __ENABLE_IF_HPP__

#include "integral_constant.hpp"

namespace ft {

template< bool, typename _Tp = void >
struct enable_if {};

// template< typename _Tp >
// struct enable_if< true, _Tp > : ft::true_type {
// 	typedef _Tp type;
// };

template< typename _Tp >
struct enable_if< true, _Tp > {
	typedef _Tp type;
};

template< bool _Bp, typename _Tp = void >
struct enable_if_t : enable_if< _Bp, _Tp >::type {};

}

#endif
