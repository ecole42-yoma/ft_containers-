#pragma once
#ifndef __TYPE_TRAITS_HPP__
#define __TYPE_TRAITS_HPP__

// #include "is_integral.hpp"
#include "./meta_function/integral_constant.hpp"
#include "./meta_function/is_integral.hpp"

namespace ft {

// enable_if
template< bool, typename _Tp = void >
struct enable_if {};
template< class _Tp >
struct enable_if< true, _Tp > {
	typedef _Tp type;
};

template< bool _Bp, typename _Tp = void >
struct enable_if_t : public enable_if< _Bp, _Tp >::type {};

// is_same
template< typename _Tp, typename _Up >
struct is_same : public ft::false_type {};

template< typename _Tp >
struct is_same< _Tp, _Tp > : public ft::true_type {};

//
}
#endif // __TYPE_TRAITS_HPP__
