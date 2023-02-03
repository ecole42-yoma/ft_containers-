#pragma once
#ifndef __IS_INTEGRAL_HPP__
#define __IS_INTEGRAL_HPP__

#include "integral_constant.hpp"

namespace ft {

// is_integral
template< typename _Tp >
struct _is_integral : ft::false_type {};

template<>
struct _is_integral< bool > : ft::true_type {};
template<>
struct _is_integral< char > : ft::true_type {};
template<>
struct _is_integral< signed char > : ft::true_type {};
template<>
struct _is_integral< unsigned char > : ft::true_type {};
template<>
struct _is_integral< wchar_t > : ft::true_type {};
template<>
struct _is_integral< short > : ft::true_type {};
template<>
struct _is_integral< unsigned short > : ft::true_type {};
template<>
struct _is_integral< int > : ft::true_type {};
template<>
struct _is_integral< unsigned int > : ft::true_type {};
template<>
struct _is_integral< long > : ft::true_type {};
template<>
struct _is_integral< unsigned long > : ft::true_type {};
template<>
struct _is_integral< long long > : ft::true_type {};
template<>
struct _is_integral< unsigned long long > : ft::true_type {};

template< typename _Tp >
struct is_integral : ft::_BoolConstant< _is_integral< _Tp > > {};

template< typename _Tp >
struct is_integral_v : is_integral< _Tp >::value {};

}
#endif
