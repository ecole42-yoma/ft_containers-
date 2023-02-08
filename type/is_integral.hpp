#pragma once
#ifndef __IS_INTEGRAL_HPP__
#define __IS_INTEGRAL_HPP__

#include "integral_constant.hpp"
#include "remove_cv.hpp"

namespace ft {

template< typename _Tp >
struct __is_integral_work : public ft::false_type {};
template<>
struct __is_integral_work< bool > : public ft::true_type {};
template<>
struct __is_integral_work< char > : public ft::true_type {};
template<>
struct __is_integral_work< signed char > : public ft::true_type {};
template<>
struct __is_integral_work< unsigned char > : public ft::true_type {};
template<>
struct __is_integral_work< wchar_t > : public ft::true_type {};
template<>
struct __is_integral_work< short > : public ft::true_type {};
template<>
struct __is_integral_work< unsigned short > : public ft::true_type {};
template<>
struct __is_integral_work< int > : public ft::true_type {};
template<>
struct __is_integral_work< unsigned int > : public ft::true_type {};
template<>
struct __is_integral_work< long > : public ft::true_type {};
template<>
struct __is_integral_work< unsigned long > : public ft::true_type {};

// template<> // C++ 11
// struct __is_integral_work< long long > : public ft::true_type {};
// template<> // C++ 11
// struct __is_integral_work< unsigned long long > : public ft::true_type {};

#if FT_VERSION > 14
template< typename _Tp >
const bool _is_integral_v = __is_integral_work< _Tp >::value; // template variable in c++14

template< typename _Tp >
struct is_integral : public _is_integral_v< _Tp > {};

template< typename _Tp >
const bool is_integral_v = is_integral< _Tp >::value; // template variable in c++14
#else
template< typename _Tp >
// struct is_integral : public __is_integral_work< _Tp > {};
struct is_integral : public __is_integral_work< typename ft::remove_cv< _Tp >::type > {};
#endif

template< typename _Tp >
struct is_integral_t : public __is_integral_work< typename ft::remove_cv< _Tp >::type >::type {};

}
#endif
