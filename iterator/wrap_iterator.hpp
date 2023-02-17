#pragma once
#ifndef __WRAP__ITERATOR_HPP__
#define __WRAP__ITERATOR_HPP__

#include "../util/_core_utils.hpp"
#include "_iterator_traits.hpp"

#define __template_iter1__ template< typename _Iter1 >
#define __template_iter2__ template< typename _Iter1, typename _Iter2 >

namespace ft {

__template_iter__ class _wrap_iter {
	public:
	typedef _Iter															 iterator_type;
	typedef typename ft::iterator_traits< iterator_type >::iterator_category iterator_category;
	typedef typename ft::iterator_traits< iterator_type >::value_type		 value_type;
	typedef typename ft::iterator_traits< iterator_type >::difference_type	 difference_type;
	typedef typename ft::iterator_traits< iterator_type >::pointer			 pointer;
	typedef typename ft::iterator_traits< iterator_type >::reference		 reference;

	private:
	iterator_type __itr;

	public:
	_wrap_iter() _es_noexcept_ : __itr() {}

	template< class _Up >
	_wrap_iter(const _wrap_iter< _Up >& u,
			   typename ft::enable_if< ft::is_convertible< _Up, iterator_type >::value >::type* = NULL) _es_noexcept_
	  : __itr(u.base()) {}

	_wrap_iter(const _wrap_iter& x)
	  : __itr(x.base()) {}

	_wrap_iter& operator=(const _wrap_iter& x) {
		if (this != &x) {
			__itr = x.base();
		}
		return *this;
	}

	/**
	 * * [ forward iterator requirements ] ---------------------------------------------------------
	 */
	reference	operator*() const _es_noexcept_ { return *__itr; }
	pointer		operator->() const _es_noexcept_ { return __itr; }
	_wrap_iter& operator++() _es_noexcept_ {
		++__itr;
		return *this;
	}
	_wrap_iter operator++(int) _es_noexcept_ {
		_wrap_iter temp(*this);
		++(*this);
		return temp;
	}

	/**
	 * * [ bidirectional iterator requirements ] ---------------------------------------------------
	 */
	_wrap_iter& operator--() _es_noexcept_ {
		--__itr;
		return *this;
	}
	_wrap_iter operator--(int) _es_noexcept_ {
		_wrap_iter temp(*this);
		--(*this);
		return temp;
	}

	/**
	 * * [ random access iterator requirements ] ---------------------------------------------------
	 */
	reference  operator[](difference_type n) const _es_noexcept_ { return __itr[n]; }
	_wrap_iter operator+(difference_type n) const _es_noexcept_ {
		_wrap_iter temp(*this);
		temp += n;
		return temp;
	}
	_wrap_iter	operator-(difference_type n) const _es_noexcept_ { return *this + (-n); }
	_wrap_iter& operator+=(difference_type n) _es_noexcept_ {
		__itr += n;
		return *this;
	}
	_wrap_iter& operator-=(difference_type n) _es_noexcept_ {
		*this += -n;
		return *this;
	}

	// inline difference_type
	// operator-(const iterator_type& i) const _es_noexcept_ { return this->base() - i.base(); }

	inline iterator_type base() const _es_noexcept_ { return __itr; }

	private:
	_wrap_iter(iterator_type itr) _es_noexcept_ : __itr(itr) {}

	template< typename _Tp, typename _Alloc >
	friend class vector;

}; // class _wrap_iter

__template_iter2__
__return__() inline bool
operator==(const _wrap_iter< _Iter1 >& lhs, const _wrap_iter< _Iter2 >& rhs) _es_noexcept_ {
	return lhs.base() == rhs.base();
}

__template_iter2__
__return__() inline bool
operator<(const _wrap_iter< _Iter1 >& lhs, const _wrap_iter< _Iter2 >& rhs) _es_noexcept_ {
	return lhs.base() < rhs.base();
}

__template_iter2__
__return__() inline bool
operator!=(const _wrap_iter< _Iter1 >& lhs, const _wrap_iter< _Iter2 >& rhs) _es_noexcept_ {
	return !(lhs == rhs);
}

__template_iter2__
__return__() inline bool
operator>(const _wrap_iter< _Iter1 >& lhs, const _wrap_iter< _Iter2 >& rhs) _es_noexcept_ {
	return rhs < lhs;
}

__template_iter2__
__return__() inline bool
operator>=(const _wrap_iter< _Iter1 >& lhs, const _wrap_iter< _Iter2 >& rhs) _es_noexcept_ {
	return !(lhs < rhs);
}

__template_iter2__
__return__() inline bool
operator<=(const _wrap_iter< _Iter1 >& lhs, const _wrap_iter< _Iter2 >& rhs) _es_noexcept_ {
	return !(rhs < lhs);
}

__template_iter1__
__return__() _wrap_iter< _Iter1 >
operator+(typename _wrap_iter< _Iter1 >::difference_type n, const _wrap_iter< _Iter1 >& rhs) _es_noexcept_ {
	return rhs += n;
}

__template_iter2__
__return__() typename _wrap_iter< _Iter1 >::difference_type
operator-(const _wrap_iter< _Iter1 >& lhs, const _wrap_iter< _Iter2 >& rhs) _es_noexcept_ {
	return lhs.base() - rhs.base();
}

} // namespace ft

#undef __template_iter1__
#undef __template_iter2__

#endif
