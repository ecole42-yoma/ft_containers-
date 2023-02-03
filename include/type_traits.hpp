#pragma once
#ifndef __TYPE_TRAITS_HPP__
#define __TYPE_TRAITS_HPP__

namespace ft {

// integral_constant
template< class _Tp, _Tp __v >
struct integral_constant {
	static const _Tp		  value = __v;
	typedef _Tp				  value_type;
	typedef integral_constant type;
							  operator value_type() const { return value; }
	const value_type		  operator()() const { return value; }
	// constexpr				  operator value_type() const { return value; } // c++11
	// constexpr value_type	  operator()() const { return value; } // c++14
};

// template< class _Tp, _Tp __v >
// const _Tp integral_constant< _Tp, __v >::value;

// enable_if
template< bool, class _Tp = void >
struct enable_if {};
template< class _Tp >
struct enable_if< true, _Tp > {
	typedef _Tp type;
};

template< bool _Bp, class _Tp = void >
struct enable_if_t : public enable_if< _Bp, _Tp >::type {};

// bool_constant
#define _FT_BOOL_CONSTANT_(__b) integral_constant< bool, (__b) >
typedef _FT_BOOL_CONSTANT_(true) true_type;
typedef _FT_BOOL_CONSTANT_(false) false_type;

// is_same
template< class _Tp, class _Up >
struct is_same : public false_type {};

template< class _Tp >
struct is_same< _Tp, _Tp > : public true_type {};

//

//

}
#endif // __TYPE_TRAITS_HPP__
