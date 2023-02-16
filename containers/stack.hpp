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

/**
 * * [ stack container ] ---------------------------------------------------------------------------
 * ! []
 * TODO - todo list
 * ? blue color
 *  @param parameter-name description
 *  @param ss
 */
template< typename _Tp, typename _Container = ft::vector< _Tp > >
class stack {
	/**
	 * * [ default type] ---------------------------------------------------------------------------
	 */
	public:
	typedef _Tp										 value_type;
	typedef _Container								 container_type;
	typedef typename container_type::size_type		 size_type;
	typedef typename container_type::reference		 reference;
	typedef typename container_type::const_reference const_reference;

	protected:
	container_type __c;

	/**
	 * * [ default form] ---------------------------------------------------------------------------
	 */
	public:
	stack()
	  : __c() {}
	explicit stack(const container_type& ctnr = container_type())
	  : __c(ctnr) {}
	stack(const stack& from)
	  : __c(from.__c) {
		LOG_("copy constructor");
	}
	stack& operator=(const stack& q) {
		LOG_("copy assignment operator");
		if (this != &q) {
			__c = q.__c;
		}
		return *this;
	}
	~stack() { LOG_("destructor"); }

	/**
	 * * [ Element Access ] ------------------------------------------------------------------------
	 */
	reference		top() _es_noexcept_ _ub_ { return __c.back(); }
	const_reference top() const _es_noexcept_ _ub_ { return __c.back(); }

	/**
	 * * [ Capacity ] ------------------------------------------------------------------------------
	 */
	bool	  empty() const _es_noexcept_ { return __c.empty(); }
	size_type size() const _es_noexcept_ { return __c.size(); }

	/**
	 * * [ Modifiers ] -----------------------------------------------------------------------------
	 */
	void push(const value_type& x) _es_strong_ _ub_ { __c.push_back(x); }
	void pop() _es_strong_ _ub_ { __c.pop_back(); }

}; /* class stack */

/**
 * * [ non-member function overloads ] -------------------------------------------------------------
 */
__template__
__return__() inline bool
operator==(const __stack__& __x, const __stack__& __y) {
	return __x.c == __y.c;
}

__template__
__return__() inline bool
operator<(const __stack__& __x, const __stack__& __y) {
	return __x.c < __y.c;
}

__template__ inline _LIBCPP_INLINE_VISIBILITY bool
operator!=(const __stack__& __x, const __stack__& __y) {
	return !(__x == __y);
}

__template__ inline _LIBCPP_INLINE_VISIBILITY bool
operator>(const __stack__& __x, const __stack__& __y) {
	return __y < __x;
}

__template__ inline _LIBCPP_INLINE_VISIBILITY bool
operator>=(const __stack__& __x, const __stack__& __y) {
	return !(__x < __y);
}

__template__ inline _LIBCPP_INLINE_VISIBILITY bool
operator<=(const __stack__& __x, const __stack__& __y) {
	return !(__y < __x);
}

} /* ft namespace */

#undef __stack__
#undef __template__

#endif
