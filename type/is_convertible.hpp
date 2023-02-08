#pragma once
#ifndef __IS_CONVERTIBLE_HPP__
#define __IS_CONVERTIBLE_HPP__

#include "integral_constant.hpp"

namespace ft {

template< typename _T1, typename _T2 >
struct __is_convertible_work {
	private:
	typedef char (&__true)[1];
	typedef char (&__false)[2];

	static __false __test(...);
	static __true  __test(_T2*);

	public:
	static const bool value = sizeof(__test(static_cast< _T1 >(0))) == true;
};

template< typename _T1, typename _T2 >
struct is_convertible : __is_convertible_work< _T1, _T2 > {};

template< typename _T1, typename _T2 >
struct is_convertible< _T1, _T2[] > : ft::false_type {};

}

#endif
