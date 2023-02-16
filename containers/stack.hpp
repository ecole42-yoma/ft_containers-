#pragma once

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "vector.hpp"

#define __stack__	 stack< _Tp, _Container >
#define __template__ template< typename _Tp, typename _Container >

namespace ft {

__template__ class stack;

__template__
__return__(bool)
operator==(const __stack__& x, const __stack__& y);

__template__
__return__(bool)
operator<(const __stack__& x, const __stack__& y);

template< typename _Tp, typename _Container = ft::vector< _Tp > >
class stack {
	public:
	typedef _Tp										 value_type;
	typedef _Container								 container_type;
	typedef typename container_type::size_type		 size_type;
	typedef typename container_type::reference		 reference;
	typedef typename container_type::const_reference const_reference;

	protected:
	container_type __c;

	public:
	stack()
	  : __c() {}
	explicit stack(const container_type& c)
	  : __c(c) {}
}; /* class stack */

/*
[ member function table ]
stack
~stack
operator=
top
empty
size
push
pop

-------------------------
[ non member function ]
operator==
operator!=
operator<
operator<=
operator>
operator>=
swap

*/

}

#undef __stack__
#undef __template__

#endif
