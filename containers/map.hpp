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

	//
};

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
