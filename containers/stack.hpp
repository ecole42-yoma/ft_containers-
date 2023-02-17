#pragma once

#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "vector.hpp"

#define __stack__		stack< _Tp, _Container >
#define __template__	template< typename _Tp, typename _Container >
#define __stack_in__	stack< _T, _Cont >
#define __template_in__ template< typename _T, typename _Cont >

namespace ft {

__template__ class stack;

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

	/**
	 * * [ non-member function overloads ] ---------------------------------------------------------
	 */
	__template_in__ friend bool operator==(const __stack_in__& x, const __stack_in__& y);
	__template_in__ friend bool operator<(const __stack_in__& x, const __stack_in__& y);

}; /* class stack */

/**
 * * [ non-member function overloads ] -------------------------------------------------------------
 */
__template__
__return__() inline bool
operator==(const __stack__& lhs, const __stack__& rhs) {
	return lhs.__c == rhs.__c;
}

__template__
__return__() inline bool
operator<(const __stack__& lhs, const __stack__& rhs) {
	return lhs.__c < rhs.__c;
}

__template__ inline bool
operator!=(const __stack__& lhs, const __stack__& rhs) {
	return !(lhs == rhs);
}

__template__ inline bool
operator>(const __stack__& lhs, const __stack__& rhs) {
	return rhs < lhs;
}

__template__ inline bool
operator>=(const __stack__& lhs, const __stack__& rhs) {
	return !(lhs < rhs);
}

__template__ inline bool
operator<=(const __stack__& lhs, const __stack__& rhs) {
	return !(rhs < lhs);
}

} /* ft namespace */

#undef __stack__
#undef __template__
#undef __stack_in__
#undef __template_in__

#endif
