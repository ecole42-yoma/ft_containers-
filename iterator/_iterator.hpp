#pragma once
#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <cstddef>

namespace ft {

template< class _Category, class _Tp, class _Distance = ptrdiff_t, class _Pointer = _Tp*, class _Reference = _Tp& >
struct iterator {
	typedef _Tp		   value_type;
	typedef _Distance  difference_type;
	typedef _Pointer   pointer_type;
	typedef _Reference reference_type;
	typedef _Category  iterator_category;
};

}
#endif
