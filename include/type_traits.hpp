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

	const value_type operator()() const { return value; }
					 operator value_type() const { return value; }
	// constexpr value_type	  operator()() const { return value; }
	// constexpr				  operator value_type() const { return value; }
};

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
