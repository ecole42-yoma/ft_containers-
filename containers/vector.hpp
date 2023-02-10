#pragma once

#include <memory>
#include <stdexcept>
#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#ifdef BASIC
#include "_core_utils.hpp"
#include "_iterator_traits.hpp"
#include "_type_traits.hpp"
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#else
#include "../iterator/_iterator_traits.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/random_access_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../type/_type_traits.hpp"
#include "../type/allocator_traits.hpp"
#include "../util/_core_utils.hpp"
#endif

#include <algorithm>
#include <iostream>
#include <iterator>

#define __vector__			 vector< _Tp, _Alloc >
#define __vector_base__		 in_vector_base< _Tp, _Alloc >
#define __template_input__	 template< typename _Input >
#define __template_forward__ template< typename _Forward >
#define __template_up__		 template< typename _Up >
#define __template_ptr__	 template< typename _Ptr >

namespace ft {

/**
 * * [ internal vector base ] ----------------------------------------------------------------------
 * ! []
 * TODO - todo list
 * ? blue color
 *  @param parameter-name description
 *  @param ss
 */
template< typename _Tp, typename _Alloc >
class in_vector_base {
	public:
	typedef _Alloc								   allocator_type;
	typedef ft::allocator_traits< allocator_type > _allocator_traits;
	typedef typename _allocator_traits::size_type  size_type;

	protected:
	typedef _Tp											value_type;
	typedef value_type&									reference;
	typedef const value_type&							const_reference;
	typedef typename _allocator_traits::difference_type difference_type;
	typedef typename _allocator_traits::pointer			pointer;
	typedef typename _allocator_traits::const_pointer	const_pointer;
	typedef pointer										iterator;
	typedef const_pointer								const_iterator;

	pointer		   __begin;
	pointer		   __end;
	pointer		   __end_capacity;
	allocator_type __alloc;

	explicit in_vector_base(const allocator_type& alloc = allocator_type()) _es_noexcept_;
	explicit in_vector_base(size_type n) _es_noexcept_;
	~in_vector_base() _es_noexcept_;

	void		allocate_(size_type n) throw(std::length_error) _es_strong_;
	inline void deallocate_() _es_noexcept_;
	void		destruct_at_end_(pointer new_last) _es_noexcept_;
	void		construct_at_end_(size_type n, const_reference value = 0) _es_noexcept_;

	inline size_type capacity_() const _es_noexcept_ { return static_cast< size_type >(__end_capacity - __begin); }
	void			 clear_() _es_noexcept_ { destruct_at_end_(__begin); }

	void copy_data_(const in_vector_base& from) _es_noexcept_;
	void swap_data_(in_vector_base& from) _es_noexcept_;

	private:
};

__template__
__vector_base__::in_vector_base(const allocator_type& alloc) _es_noexcept_
  : __begin(NULL)
  , __end(NULL)
  , __end_capacity(NULL)
  , __alloc(alloc) {
	LOG_("constuctor in_vector_base");
}

__template__ __vector_base__::~in_vector_base() _es_noexcept_ {
	if (std::uncaught_exceptions() == true) {
		LOG_("destructor ~in_vector_base - called during stack unwinding");
	} else {
		LOG_("destructor ~in_vector_base - called normally");
	}
	deallocate_();
}

__template__
__return__(void) __vector_base__::allocate_(size_type n) throw(std::length_error) _es_strong_ {
	LOG_("in_vector_base");
	if (n > (__alloc.max_size() / sizeof(value_type))) {
		throw std::length_error("vector : allocate_ : length_error");
	}
	__begin = __end = __alloc.allocate(n);
	__end_capacity	= __begin + n;
}

__template__
__return__() inline void __vector_base__::deallocate_() _es_noexcept_ {
	LOG_("in_vector_base");
	if (__begin != NULL) {
		clear_();
		__alloc.deallocate(__begin, capacity_());
		__begin = __end = __end_capacity = NULL;
	}
}

__template__
__return__(void) __vector_base__::destruct_at_end_(pointer new_last) _es_noexcept_ {
	LOG_("in_vector_base");
	pointer soon_to_be_end = __end;
	while (new_last != soon_to_be_end) {
		__alloc.destroy(--soon_to_be_end);
	}
	__end = new_last;
}

__template__
__return__(void) __vector_base__::copy_data_(const in_vector_base& from) _es_noexcept_ {
	LOG_("in_vector_base");
	__begin		   = from.__begin;
	__end		   = from.__end;
	__end_capacity = from.__end_capacity;
}

__template__
__return__(void) __vector_base__::swap_data_(in_vector_base& from) _es_noexcept_ {
	LOG_("in_vector_base");
	pointer temp_begin		  = __begin;
	pointer temp_end		  = __end;
	pointer temp_end_capacity = __end_capacity;
	__begin					  = from.__begin;
	__end					  = from.__end;
	__end_capacity			  = from.__end_capacity;
	from.__begin			  = temp_begin;
	from.__end				  = temp_end;
	from.__end_capacity		  = temp_end_capacity;
}

/**
 * * [ vector container ] ---------------------------------------------------------------------------
 * ! []
 * TODO - todo list
 * ? blue color
 *  @param parameter-name description
 *  @param ss
 */
template< typename _Tp, typename _Alloc = std::allocator< _Tp > >
class vector : private in_vector_base< _Tp, _Alloc > {
	private:
	typedef in_vector_base< _Tp, _Alloc > __base;

	public:
	typedef vector< _Tp, _Alloc >				   self_type;
	typedef _Tp									   value_type;
	typedef _Alloc								   allocator_type;
	typedef typename __base::size_type			   size_type;
	typedef typename __base::difference_type	   difference_type;
	typedef typename __base::pointer			   pointer;
	typedef typename __base::const_pointer		   const_pointer;
	typedef typename __base::reference			   reference;
	typedef typename __base::const_reference	   const_reference;
	typedef randomIterator< pointer >			   iterator;
	typedef const randomIterator< pointer >		   const_iterator;
	typedef ft::reverse_iterator< iterator >	   reverse_iterator;
	typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;

	/**
	 * * [ default form] ---------------------------------------------------------------------------
	 * TODO - not done yet
	 */
	public:
	explicit vector(const allocator_type& alloc = allocator_type()) _es_strong_ _ub_; // default
	explicit vector(size_type			  n,
					const_reference		  val	= value_type(),
					const allocator_type& alloc = allocator_type()) _es_strong_ _ub_; // fill
	__template_input__ vector(
	  _Input																   first,
	  typename ft::enable_if< ft::is_iterator< _Input >::value, _Input >::type last,
	  const allocator_type& alloc = std::allocator< typename ft::iterator_traits< _Input >::value_type >())
	  _es_strong_ _ub_;							 // range
	vector(const vector& from) _es_strong_ _ub_; // copy
	vector& operator=(const vector& from) _es_basic_ _ub_;
	~vector() _es_noexcept_;

	/**
	 * * [ allocator ] -----------------------------------------------------------------------------
	 */
	allocator_type get_allocator() const _es_noexcept_ { return this->__alloc; }

	/**
	 * * [ element access ] ------------------------------------------------------------------------
	 */
	reference		  at(size_type n) throw(std::out_of_range) _es_strong_;
	const_reference	  at(size_type n) const throw(std::out_of_range) _es_strong_;
	reference		  operator[](size_type n) _es_noexcept_ _ub_;
	const_reference	  operator[](size_type n) const _es_noexcept_ _ub_;
	reference		  front() _es_noexcept_ _ub_;
	const_reference	  front() const _es_noexcept_ _ub_;
	reference		  back() _es_noexcept_ _ub_;
	const_reference	  back() const _es_noexcept_ _ub_;
	value_type*		  data() _es_noexcept_;
	const value_type* data() const _es_noexcept_;

	/**
	 * * [ iterators ] -----------------------------------------------------------------------------
	 */
	iterator			   begin() _es_noexcept_ { return iterator(this->__begin); }
	const_iterator		   begin() const _es_noexcept_ { return const_iterator(this->__begin); }
	iterator			   end() _es_noexcept_ { return iterator(this->__end); }
	const_iterator		   end() const _es_noexcept_ { return const_iterator(this->__end); }
	reverse_iterator	   rbegin() _es_noexcept_ { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const _es_noexcept_ { return const_reverse_iterator(end()); }
	reverse_iterator	   rend() _es_noexcept_ { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const _es_noexcept_ { return const_reverse_iterator(begin()); }

	/**
	 * * [ capacity ] ------------------------------------------------------------------------------
	 * TODO - reserve
	 */
	inline size_type size() const _es_noexcept_ { return this->__end - this->__begin; }
	inline size_type max_size() const _es_noexcept_ { return this->__alloc.max_size() / sizeof(value_type); }
	inline size_type capacity() const _es_noexcept_ { return __base::capacity_(); }
	inline bool		 empty() const _es_noexcept_ { return this->__begin == this->__end; };
	void			 reserve(size_type n) throw(std::length_error) _es_strong_;

	/**
	 * * [ modifiers ] -----------------------------------------------------------------------------
	 * TODO --
	 */
	__template_input__ __return__() typename ft::enable_if< ft::is_iterator< _Input >::value, void >::type
	  assign(_Input first, _Input last) _es_basic_ _ub_;
	void					   assign(size_type n, const_reference value) _es_basic_ _ub_;
	void					   push_back(const_reference x) _es_strong_ _ub_;
	void					   pop_back() _es_noexcept_ _ub_;
	iterator				   insert(const_iterator position, const_reference x) _es_strong_ _ub_;
	iterator				   insert(const_iterator position, size_type n, const_reference x) _es_strong_ _ub_;
	__template_iter__ iterator insert(const_iterator position, _Iter first, _Iter last) _es_strong_ _ub_;
	iterator				   erase(iterator position) _es_basic_ _ub_;
	iterator				   erase(iterator first, iterator last) _es_basic_ _ub_;
	void					   clear() _es_noexcept_ { __base::clear_(); }
	void					   swap(vector& x) _es_noexcept_ _ub_;
	void					   resize(size_type sz, value_type c = value_type()) _es_strong_;

	/**
	 * * [ private workhorse ] ---------------------------------------------------------------------
	 */
	private:
	inline bool invariants__() const _es_noexcept_;
	size_type	recommend_size__(size_type new_size) const throw(std::length_error) _es_basic_;

	__template_up__ inline _Up*											data_ptr__(_Up* ptr) _es_noexcept_;
	__template_up__ inline _Up*											data_ptr__(_Up* ptr) const _es_noexcept_;
	__template_ptr__ inline typename __vector_base__::value_type*		data_ptr__(_Ptr ptr) _es_noexcept_;
	__template_ptr__ inline const typename __vector_base__::value_type* data_ptr__(_Ptr ptr) const _es_noexcept_;

	/**
	 * * [ internal workhorse ] --------------------------------------------------------------------
	 * TODO iterator_construct
	 */
	private:
	__template_input__
	  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
								!ft::has_iterator_category_convertible_to< _Input, ft::forward_iterator_tag >::value,
							  _Input >::type
	  internal_iterator_construct__(_Input first, _Input last);
	__template_forward__
	  typename ft::enable_if< ft::has_iterator_category_convertible_to< _Forward, ft::forward_iterator_tag >::value,
							  _Forward >::type
	  internal_iterator_construct__(_Forward first, _Forward last);
	__template_input__
	  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
								!ft::has_iterator_category_convertible_to< _Input, ft::forward_iterator_tag >::value,
							  _Input >::type
	  internal_assign__(_Input first, _Input last);
	__template_forward__
	  typename ft::enable_if< ft::has_iterator_category_convertible_to< _Forward, ft::forward_iterator_tag >::value,
							  _Forward >::type
	  internal_assign__(_Forward first, _Forward last);

}; /* class vector */

/**
 * * [ non-member function overloads ] -------------------------------------------------------------
 */
__template__
__return__(bool)
operator==(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_;
__template__
__return__(bool)
operator!=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_;
__template__
__return__(bool)
operator<(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_;
__template__
__return__(bool)
operator<=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_;
__template__
__return__(bool)
operator>(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_;
__template__
__return__(bool)
operator>=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_;

__template__
__return__(void) swap(ft::vector< _Tp, _Alloc >& lhs, ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_ _ub_;

/**
 * * [ default form] -------------------------------------------------------------------------------
 */
__template__
__vector__::vector(const allocator_type& alloc) _es_strong_ _ub_ // default
  try : __base(alloc) {
	LOG_("default constructor");
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
} catch (...) {
}

__template__
__vector__::vector(size_type			 n,
				   const_reference		 val,
				   const allocator_type& alloc) _es_strong_ _ub_ // fill
  try : __base(alloc) {
	LOG_("fill constructor");

	if (n > 0) {
		__data = __alloc.allocate(n * sizeof(value_type));
		for (size_type i = 0; i < n; ++i) {
			__alloc.construct(__data + i, val);
		}
	}

} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
} catch (...) {
}

__template__ __template_input__
__vector__::vector(_Input																	first,
				   typename ft::enable_if< ft::is_iterator< _Input >::value, _Input >::type last,
				   const allocator_type& alloc) _es_strong_ _ub_ // range
  try : __base(alloc) {
	LOG_("range constructor : iterator");
	internal_iterator_construct__(first, last);
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
} catch (...) {
}

__template__
__vector__::vector(const vector& from) _es_strong_ _ub_ // copy
  try : __base(from.__alloc) {
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
} catch (...) {
	(void)from;
}

__template__
__return__(__vector__&) __vector__::operator=(const vector& from) _es_basic_ _ub_ {
	LOG_("copy assignment operator");

	if (this != &from) {
		this->~vector();
		if (from.size() > 0) { // TODO: make to __function, check how to  unalloc copy
			__data	   = __alloc.allocate(from.size());
			__capacity = from.size();
			__size	   = from.size();
			for (size_type i = 0; i < from.size(); ++i) {
				__alloc.construct(__data + i, from[i]);
			}
		}
	}
	return *this;
}
__template__
__return__() __vector__::~vector() _es_noexcept_ {
	if (std::uncaught_exceptions() == true) {
		LOG_("called during stack unwinding");
	} else {
		LOG_("called normally");
	}
}

/**
 * * [ allocator ] ---------------------------------------------------------------------------------
 */

/**
 * * [ element access ] ----------------------------------------------------------------------------
 */
__template__
__return__() typename __vector__::reference __vector__::at(size_type n) throw(std::out_of_range) _es_strong_ {
	LOG_("vector: at");
	if (n >= size()) {
		throw std::out_of_range("vector : at : index out of bounds");
	}
	return this->__begin[n];
}
__template__
__return__() typename __vector__::const_reference __vector__::at(size_type n) const
  throw(std::out_of_range) _es_strong_ {
	LOG_("vector: at [const]");
	if (n >= size()) {
		throw std::out_of_range("vector : at [const]: index out of bounds");
	}
	return this->__begin[n];
}
__template__
__return__() typename __vector__::reference __vector__::operator[](size_type n) _es_noexcept_ _ub_ {
	LOG_("vector: operator[]");
	assert_((n < size()), "vector : operator[] : index out of bounds");
	return this->__begin[n];
}
__template__
__return__() typename __vector__::const_reference __vector__::operator[](size_type n) const _es_noexcept_ _ub_ {
	LOG_("vector: operator[] [const]");
	assert_((n < size()), "vector : operator[] [const] : index out of bounds");
	return this->__begin[n];
}
__template__
__return__() typename __vector__::reference __vector__::front() _es_noexcept_ _ub_ {
	LOG_("vector: front");
	assert_((!empty()), "vector : front : called for empty vector");
	return *this->__begin;
}
__template__
__return__() typename __vector__::const_reference __vector__::front() const _es_noexcept_ _ub_ {
	LOG_("vector: front [const]");
	assert_((!empty()), "vector : front [const] : called for empty vector");
	return *this->__begin;
}
__template__
__return__() typename __vector__::reference __vector__::back() _es_noexcept_ _ub_ {
	LOG_("vector: back ");
	assert_((!empty()), "vector : back  : called for empty vector");
	return *(this->__end - 1);
}
__template__
__return__() typename __vector__::const_reference __vector__::back() const _es_noexcept_ _ub_ {
	LOG_("vector: back [const]");
	assert_(!empty(), "vector : back [const] : called for empty vector");
	return *(this->__end - 1);
}
__template__
__return__() typename __vector__::value_type* __vector__::data() _es_noexcept_ {
	LOG_("vector: data");
	return data_ptr_(this->__begin);
}
__template__
__return__() const typename __vector__::value_type* __vector__::data() const _es_noexcept_ {
	LOG_("vector: data [const]");
	return data_ptr_(this->__begin);
}

/**
 * * [ iterators ] ---------------------------------------------------------------------------------
 */
// reverse_iterator
// rbegin();
// reverse_iterator
// rend();
// const_reverse_iterator
// rbegin() const;
// const_reverse_iterator
// rend() const;

/**
 * * [ capacity ] ----------------------------------------------------------------------------------
 */
// __template__
// void
// __vector__::reserve(size_type n) {
// 	if (n > max_size()) {
// 		throw std::length_error("vector::reserve");
// 	}
// 	if (n > capacity()) {
// 		try {
// 		} catch (const std::exception& e) {
// 		} catch (...) {
// 		}
// 	}
// }

/**
 * * [ modifiers ] ---------------------------------------------------------------------------------
 */

__template__ __template_input__
__return__() typename ft::enable_if< ft::is_iterator< _Input >::value, void >::type
  __vector__::assign(_Input first, _Input last) _es_basic_ _ub_ {
	LOG_("vector: assign (range)");
	internal_assign__(first, last);
}
__template__ void
__vector__::assign(size_type n, const_reference value) _es_basic_ _ub_ {
	LOG_("vector: assign (fill)");
	if (n > capacity()) {
		vector temp(recomend_size__(n), value);
		temp.swap_data_(this);
	} else if (n > size()) {
		std::fill(this->__begin, this->__end, value);
		const size_type remain = n - size();
		std::uninitialized_fill_n(this->__end, remain, value);
		std::advance(this->__end, remain);
	} else {
		std::fill_n(this->__begin, n, value);
		const size_type remain = size() - n;
		this->destruct_at_end_(std::advance(this->__end, -remain));
	}
}

/**
 * * [ private workhorse ] -------------------------------------------------------------------------
 */
__template__
__return__(bool) __vector__::invariants__() const _es_noexcept_ {
	if ((this->__begin == NULL && (this->__end != NULL || this->__end_capacity != NULL)) ||
		(this->__begin > this->__end) || (this->__begin == this->__end_capacity) ||
		(this->__end > this->__end_capacity)) {
		return false;
	}
	return true;
}
__template__ typename __vector__::size_type
__vector__::recommend_size__(size_type new_size) const throw(std::length_error) _es_basic_ {
	if (new_size > max_size()) {
		throw std::length_error("vector: recommend_size__ : length_error");
	}
	return _VSTD::max< size_type >(2 * capacity(), new_size);
}

__template__ template< typename _Up >
inline _Up*
__vector__::data_ptr__(_Up* ptr) _es_noexcept_ {
	return ptr;
}
__template__ template< typename _Up >
inline _Up*
__vector__::data_ptr__(_Up* ptr) const _es_noexcept_ {
	return ptr;
}
__template__ template< typename _Ptr >
inline typename __vector_base__::value_type*
__vector__::data_ptr__(_Ptr ptr) _es_noexcept_ {
	return empty() ? (value_type*)0 : ptr.operator->();
}
__template__ template< typename _Ptr >
inline const typename __vector_base__::value_type*
__vector__::data_ptr__(_Ptr ptr) const _es_noexcept_ {
	return empty() ? (const value_type*)0 : ptr.operator->();
}

/**
 * * [ internal workhorse ] ------------------------------------------------------------------------
 */
__template__ __template_input__
  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
							!ft::has_iterator_category_convertible_to< _Input, ft::forward_iterator_tag >::value,
						  _Input >::type
  __vector__::internal_iterator_construct__(_Input first, _Input last) {
	LOG_C_("internal_range constructor : input iterator", B_COLOR_YELLOW);
	internal_assign__(first, last);
}
__template__ __template_forward__
  typename ft::enable_if< ft::has_iterator_category_convertible_to< _Forward, ft::forward_iterator_tag >::value,
						  _Forward >::type
  __vector__::internal_iterator_construct__(_Forward first, _Forward last) {
	LOG_C_("internal_range constructor : forward iterator", B_COLOR_YELLOW);
	internal_assign__(first, last);
}
__template__ __template_input__
  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
							!ft::has_iterator_category_convertible_to< _Input, ft::forward_iterator_tag >::value,
						  _Input >::type
  __vector__::internal_assign__(_Input first, _Input last) {
	LOG_C_("internal_assign : input iterator", B_COLOR_YELLOW);
}
__template__ __template_forward__
  typename ft::enable_if< ft::has_iterator_category_convertible_to< _Forward, ft::forward_iterator_tag >::value,
						  _Forward >::type
  __vector__::internal_assign__(_Forward first, _Forward last) {
	LOG_C_("internal_assign : forward iterator", B_COLOR_YELLOW);
}

} /* namespace ft */

#undef __vector__
#undef __template_input__
#undef __template_forward__

#endif /* __VECTOR_HPP__ */
