#pragma once
#ifndef __ALLOCATOR__TRAITS__HPP__
#define __ALLOCATOR__TRAITS__HPP__

#include "_type_traits.hpp"

namespace ft {

/**
 * * [ is allocator ] ------------------------------------------------------------------------------
 */
template< typename _Tp >
struct __is_allocator_work {
	private:
	typedef char (&__true)[1];
	typedef char (&__false)[2];

	template< typename _Up >
	static __false test__(...);

	template< typename _Up >
	static __true test__(typename ft::void_t< typename _Up::value_type >::type*								= 0,
						 typename ft::void_t< typename _Up::pointer >::type*								= 0,
						 typename ft::void_t< typename _Up::const_pointer >::type*							= 0,
						 typename ft::void_t< typename _Up::difference_type >::type*						= 0,
						 typename ft::void_t< typename _Up::size_type >::type*								= 0,
						 typename ft::void_t< typename _Up::propagate_on_container_move_assignment >::type* = 0,
						 // typename ft::void_t< typename _Up::allocator_type >::type*							= 0,
						 //  typename ft::void_t< typename _Up::propagate_on_container_swap >::type*			= 0,
						 //  typename ft::void_t< typename _Up::propagate_on_container_copy_assignment >::type* = 0,
						 //  typename ft::void_t< typename _Up::void_pointer >::type*							= 0,
						 //  typename ft::void_t< typename _Up::const_void_pointer >::type* = 0,
						 typename ft::void_t< typename _Up::is_always_equal >::type* = 0);

	public:
	static const bool value = sizeof(test__< _Tp >(0, 0, 0, 0, 0, 0, 0)) == sizeof(__true);
};

template< typename _Tp, bool = __is_allocator_work< _Tp >::value >
struct __is_allocator : ft::true_type {};

template< typename _Tp >
struct __is_allocator< _Tp, false > : ft::false_type {};

template< typename _Tp >
struct is_allocator : __is_allocator< _Tp > {};

/**
 * * [ allocator traits ] --------------------------------------------------------------------------
 */
template< class _Alloc, bool >
struct __allocator_traits_work {};

template< class _Alloc >
struct __allocator_traits_work< _Alloc, true > {
	typedef _Alloc													allocator_type;
	typedef typename _Alloc::value_type								value_type;
	typedef typename _Alloc::pointer								pointer;
	typedef typename _Alloc::const_pointer							const_pointer;
	typedef typename _Alloc::difference_type						difference_type;
	typedef typename _Alloc::size_type								size_type;
	typedef typename _Alloc::propagate_on_container_move_assignment propagate_on_container_move_assignment;
	typedef typename _Alloc::is_always_equal						is_always_equal;
	// ANNOTATION: the following are not required by the is_allocator
	// typedef typename _Alloc::void_pointer							void_pointer;
	// typedef typename _Alloc::const_void_pointer						const_void_pointer;
	// typedef typename _Alloc::propagate_on_container_copy_assignment propagate_on_container_copy_assignment;
	// typedef typename _Alloc::propagate_on_container_swap			propagate_on_container_swap;
};

template< class _Alloc >
struct allocator_traits : __allocator_traits_work< _Alloc, is_allocator< _Alloc >::value > {};

}
#endif
