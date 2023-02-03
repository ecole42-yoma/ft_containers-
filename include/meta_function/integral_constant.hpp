#pragma once
#ifndef __INTGRAL_CONSTANT_HPP__
#define __INTGRAL_CONSTANT_HPP__

namespace ft {

// integral_constant
template< typename _Tp, _Tp __v >
struct integral_constant {
	static const _Tp		  value = __v;
	typedef _Tp				  value_type;
	typedef integral_constant type;
							  operator value_type() const { return value; }
	const value_type		  operator()() const { return value; }
	// constexpr				  operator value_type() const { return value; } // c++11
	// constexpr value_type	  operator()() const { return value; } // c++14
};

template< class _Tp, _Tp __v >
const _Tp integral_constant_v = integral_constant< _Tp, __v >::value;

// template< typename _Tp, _Tp __v >
// struct integral_constant_v : integral_constant< _Tp, __v >::value {};

// bool_constant
#define _BOOL_CONS_(__b) integral_constant< bool, (__b) >
typedef _BOOL_CONS_(true) true_type;
typedef _BOOL_CONS_(false) false_type;

template< bool __v >
struct _BoolConstant : integral_constant< bool, __v > {};

}
#endif
