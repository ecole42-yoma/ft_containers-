#pragma once
#ifndef __INTGRAL_CONSTANT_HPP__
#define __INTGRAL_CONSTANT_HPP__

namespace ft {

template< typename _Tp, _Tp __v >
struct integral_constant {
	static const _Tp					  value = __v;
	typedef _Tp							  value_type;
	typedef integral_constant< _Tp, __v > type;
										  operator value_type() const { return value; }
	const value_type					  operator()() const { return value; }
	// constexpr				  operator value_type() const { return value; } // c++11
	// constexpr value_type	  operator()() const { return value; } // c++14
};

template< typename _Tp, _Tp __v >
struct integral_constant_t : integral_constant< _Tp, __v > {}; // alias template

#if FT_VERSION > 14
template< typename _Tp, _Tp __v >
const _Tp integral_constant_v = integral_constant< _Tp, __v >::value; // template variable in c++14
#endif

// bool_constant
template< bool __v >
struct bool_constant : integral_constant< bool, __v > {}; // alias template

typedef bool_constant< true >  true_type;
typedef bool_constant< false > false_type;

}
#endif
