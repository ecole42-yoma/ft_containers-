#pragma once
#ifndef __IS_INTEGRAL_HPP__
#define __IS_INTEGRAL_HPP__

#include "integral_constant.hpp"

namespace ft {

// TODO : need to add CV-qualifiers version

template< typename _Tp >
struct _is_integral : public ft::false_type {};

template<>
struct _is_integral< bool > : public ft::true_type {};
template<>
struct _is_integral< char > : public ft::true_type {};
template<>
struct _is_integral< signed char > : public ft::true_type {};
template<>
struct _is_integral< unsigned char > : public ft::true_type {};
template<>
struct _is_integral< wchar_t > : public ft::true_type {};
template<>
struct _is_integral< short > : public ft::true_type {};
template<>
struct _is_integral< unsigned short > : public ft::true_type {};
template<>
struct _is_integral< int > : public ft::true_type {};
template<>
struct _is_integral< unsigned int > : public ft::true_type {};
template<>
struct _is_integral< long > : public ft::true_type {};
template<>
struct _is_integral< unsigned long > : public ft::true_type {};
template<>
struct _is_integral< long long > : public ft::true_type {};
template<>
struct _is_integral< unsigned long long > : public ft::true_type {};

#if FT_VERSION > 14
template< typename _Tp >
const bool _is_integral_v = _is_integral< _Tp >::value; // template variable in c++14

template< typename _Tp >
struct is_integral : public _is_integral_v< _Tp > {};

template< typename _Tp >
const bool is_integral_v = is_integral< _Tp >::value; // template variable in c++14
#else
template< typename _Tp >
struct is_integral : public _is_integral< _Tp > {};
#endif

template< typename _Tp >
struct is_integral_t : public _is_integral< _Tp >::type {};

}
#endif
