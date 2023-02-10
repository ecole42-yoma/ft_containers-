#pragma once
#ifndef __TO_ADDRESS_HPP__
#define __TO_ADDRESS_HPP__

#include "../type/_type_traits.hpp"
#include "../util/_core_utils.hpp"

namespace ft {

template< class _Pointer, class = void >
struct __to_address_helper;

template< class _Tp >
_Tp*
to_address(_Tp* __p) _es_noexcept_ {
	static_assert_((!is_function< _Tp >::value), "_Tp is a function type");
	return __p;
}

// // enable_if is needed here to avoid instantiating checks for fancy pointers on raw pointers
// template< class _Pointer,
// 		  class = __enable_if_t< !is_pointer< _Pointer >::value && !is_array< _Pointer >::value &&
// 								 !is_function< _Pointer >::value > >

// typename decay< decltype(__to_address_helper< _Pointer >::__call(declval< const _Pointer& >())) >::type
// __to_address(const _Pointer& __p) _NOEXCEPT {
// 	return __to_address_helper< _Pointer >::__call(__p);
// }

}

#endif
