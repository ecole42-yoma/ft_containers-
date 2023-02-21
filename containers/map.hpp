#pragma once
#ifndef __MAP__HPP__
#define __MAP__HPP__

#ifdef BASIC
#else
#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"

#include "../iterator/_iterator_traits.hpp"

#include "../type/_type_traits.hpp"
#include "../type/allocator_traits.hpp"

#include "../util/_core_utils.hpp"
#include "../util/utility.hpp"
#endif

#include <functional>

#define __template__ template< class _Key, class _Tp, class _Comp, class _Alloc >
#define __map__		 map< _Key, _Tp, _Comp, _Alloc >

namespace ft {

template< class _Arg1, class _Arg2, class _Result >
struct binary_function {
	typedef _Arg1	first_argument_type;
	typedef _Arg2	second_argument_type;
	typedef _Result result_type;
};

enum _Rb_tree_color { _M_red = false, _M_black = true };

struct _Rb_tree_node_base {
	typedef _Rb_tree_node_base* _Base_ptr;

	_Rb_tree_color _M_color;
	_Base_ptr	   _M_parent;
	_Base_ptr	   _M_left;
	_Base_ptr	   _M_right;

	static _Base_ptr _S_minimum(_Base_ptr __x) {
		while (__x->_M_left != 0)
			__x = __x->_M_left;
		return __x;
	}

	static _Base_ptr _S_maximum(_Base_ptr __x) {
		while (__x->_M_right != 0)
			__x = __x->_M_right;
		return __x;
	}
};

/**
 * * [ map base ] ----------------------------------------------------------------------
 * ! []
 * TODO - todo list
 * ? blue color
 *  @param parameter-name description
 *  @param ss
 */
template< class _Key,
		  class _Tp,
		  class _Comp  = std::less< _Key >,
		  class _Alloc = std::allocator< ft::pair< const _Key, _Tp > > >
class map {

	public:
	typedef _Key								key_type;
	typedef _Tp									mapped_type;
	typedef pair< const key_type, mapped_type > value_type;
	typedef typename _Comp::type				key_compare;
	typedef typename _Alloc::type				allocator_type;
	typedef value_type&							reference;
	typedef const value_type&					const_reference;

	class value_compare : public binary_function< value_type, value_type, bool > {

		friend class map;

		protected:
		key_compare __comp;

		value_compare(key_compare c)
		  : __comp(c) {}

		public:
		bool operator()(const value_type& x, const value_type& y) const { return __comp(x.first, y.first); }
	}; /* value_compare class */

	private:
}; /* map class*/

} /*
namespace ft*/

#undef __template__
#undef __map__

#endif

/*
[ member function table ]
map
~map
operator=
begin
end
rbegin
rend
operator[]
empty
size
max_size
clear
insert
erase
swap
count
find
lower_bound
upper_bound
equal_range
key_comp
value_comp
get_allocator
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
