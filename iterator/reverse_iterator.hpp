#pragma once
#include "has_iterator_x.hpp"
#ifndef __REVERSE__ITERATOR_HPP__
#define __REVERSE__ITERATOR_HPP__

#include "../util/_core_utils.hpp"
#include "_iterator_traits.hpp"

#define __template_iter1__ template< typename _Iter1 >
#define __template_iter2__ template< typename _Iter1, typename _Iter2 >

namespace ft {

__template_iter__ class reverse_iterator
  : public ft::iterator< typename ft::iterator_traits< _Iter >::iterator_category,
						 typename ft::iterator_traits< _Iter >::value_type,
						 typename ft::iterator_traits< _Iter >::difference_type,
						 typename ft::iterator_traits< _Iter >::pointer,
						 typename ft::iterator_traits< _Iter >::reference > {
	public:
	typedef _Iter								 iterator_type;
	typedef ft::iterator_traits< iterator_type > traits_;
	typedef typename traits_::iterator_category	 iterator_category;
	typedef typename traits_::value_type		 value_type;
	typedef typename traits_::difference_type	 difference_type;
	typedef typename traits_::pointer			 pointer;
	typedef typename traits_::reference			 reference;

	private:
	iterator_type __itr;

	public:
	reverse_iterator() _es_noexcept_ : __itr(iterator_type()) {}

	reverse_iterator(const iterator_type& itr) _es_noexcept_ : __itr(itr) {}

	template< class _Up >
	reverse_iterator(const reverse_iterator< _Up >& u) _es_noexcept_ : __itr(u.base()) {}

	reverse_iterator& operator=(const reverse_iterator& x) {
		if (this != &x) {
			__itr = x.base();
		}
		return *this;
	}

	/**
	 * * [ forward iterator requirements ] ---------------------------------------------------------
	 */
	reference operator*() const _es_noexcept_ {
		iterator_type temp = __itr;
		return *(--temp);
	}
	pointer			  operator->() const _es_noexcept_ { return &operator*(); }
	reverse_iterator& operator++() _es_noexcept_ {
		--__itr;
		return *this;
	}
	reverse_iterator operator++(int) _es_noexcept_ {
		reverse_iterator temp(*this);
		--__itr;
		return temp;
	}

	/**
	 * * [ bidirectional iterator requirements ] ---------------------------------------------------
	 */
	reverse_iterator& operator--() _es_noexcept_ {
		++__itr;
		return *this;
	}
	reverse_iterator operator--(int) _es_noexcept_ {
		reverse_iterator temp(*this);
		++__itr;
		return temp;
	}

	/**
	 * * [ random access iterator requirements ] ---------------------------------------------------
	 */
	reference		  operator[](difference_type n) const _es_noexcept_ { return *(*this + n); }
	reverse_iterator  operator+(difference_type n) const _es_noexcept_ { return reverse_iterator(__itr - n); }
	reverse_iterator  operator-(difference_type n) const _es_noexcept_ { return reverse_iterator(__itr + n); }
	reverse_iterator& operator+=(difference_type n) _es_noexcept_ {
		__itr -= n;
		return *this;
	}
	reverse_iterator& operator-=(difference_type n) _es_noexcept_ {
		__itr += n;
		return *this;
	}

	// inline difference_type
	// operator-(const iterator_type& i) const _es_noexcept_ { return this->base() - i.base(); }

	inline iterator_type base() const _es_noexcept_ { return __itr; }

	private:
	template< typename _Up >
	friend class reverse_iterator;
	template< typename _Tp, typename _Alloc >
	friend class vector;
	template< class _CharT, class _Traits, class _Alloc >
	friend class basic_string;
	template< class _Tp, size_t >
	friend class span;

}; // class reverse_iterator

__template_iter2__
__return__() inline bool
operator==(const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs) _es_noexcept_ {
	return lhs.base() == rhs.base();
}

__template_iter2__
__return__() inline bool
operator<(const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs) _es_noexcept_ {
	return lhs.base() > rhs.base();
}

__template_iter2__
__return__() inline bool
operator!=(const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs) _es_noexcept_ {
	return !(lhs == rhs);
}

__template_iter2__
__return__() inline bool
operator>(const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs) _es_noexcept_ {
	return rhs < lhs;
}

__template_iter2__
__return__() inline bool
operator>=(const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs) _es_noexcept_ {
	return !(lhs < rhs);
}

__template_iter2__
__return__() inline bool
operator<=(const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs) _es_noexcept_ {
	return !(rhs < lhs);
}

__template_iter1__
__return__() inline reverse_iterator< _Iter1 >
operator+(typename reverse_iterator< _Iter1 >::difference_type n, const reverse_iterator< _Iter1 >& rhs) _es_noexcept_ {
	return reverse_iterator< _Iter1 >(rhs.base() - n);
}

__template_iter2__
__return__() inline typename reverse_iterator< _Iter1 >::difference_type
operator-(const reverse_iterator< _Iter1 >& lhs, const reverse_iterator< _Iter2 >& rhs) _es_noexcept_ {
	return rhs.base() - lhs.base();
}

__template_iter__ inline reverse_iterator< _Iter >
make_reverse_iterator(_Iter __i) {
	return reverse_iterator< _Iter >(__i);
}

} // namespace ft

#undef __template_iter1__
#undef __template_iter2__

#endif
