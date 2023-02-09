#pragma once
#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <cstddef>

namespace ft {

template< typename _Category,
		  typename _Tp,
		  typename _Distance  = ptrdiff_t,
		  typename _Pointer	  = _Tp*,
		  typename _Reference = _Tp& >
struct iterator {
	typedef _Tp		   value_type;
	typedef _Distance  difference_type;
	typedef _Pointer   pointer;
	typedef _Reference reference;
	typedef _Category  iterator_category;
};

}
#endif
