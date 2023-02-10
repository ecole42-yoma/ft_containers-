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

#include <iostream>

#define __vector__			 vector< _Tp, _Alloc >
#define __vector_base__		 in_vector_base< _Tp, _Alloc >
#define __template_input__	 template< typename _Input >
#define __template_forward__ template< typename _Forward >

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

	explicit in_vector_base() _es_noexcept_;
	explicit in_vector_base(const size_type& n) _es_noexcept_;
	~in_vector_base() _es_noexcept_;

	void	  clear_() _es_noexcept_ { destruct_at_end_(__begin); }
	size_type capacity_() const _es_noexcept_ { return static_cast< size_type >(__end_capacity - __begin); }
	void	  destruct_at_end_(pointer new_last) _es_noexcept_;

	void copy_data_(const in_vector_base& from) _es_noexcept_;
	void swap_data_(in_vector_base& from) _es_noexcept_;

	private:
};

__template__
__vector_base__::in_vector_base() _es_noexcept_
  : __begin(NULL)
  , __end(NULL)
  , __end_capacity(NULL) {
	LOG_("constuctor in_vector_base");
}

__template__ __vector_base__::~in_vector_base() _es_noexcept_ {
	if (std::uncaught_exceptions() == true) {
		LOG_("destructor ~in_vector_base - called during stack unwinding");
	} else {
		LOG_("destructor ~in_vector_base - called normally");
	}
	if (__begin != NULL) {
		clear_();
		__alloc.deallocate(__begin, capacity_());
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
	 */
	public:
	explicit vector(const allocator_type& alloc = allocator_type()) _es_strong_ _ub_; // default
	explicit vector(size_type			  n,
					const value_type&	  val	= value_type(),
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
	iterator			   end() _es_noexcept_ { return iterator(this->__end); }
	const_iterator		   begin() const _es_noexcept_ { return const_iterator(this->__begin); }
	const_iterator		   end() const _es_noexcept_ { return const_iterator(this->__end); }
	reverse_iterator	   rbegin() _es_noexcept_;
	reverse_iterator	   rend() _es_noexcept_;
	const_reverse_iterator rbegin() const _es_noexcept_;
	const_reverse_iterator rend() const _es_noexcept_;

	/**
	 * * [ capacity ] ------------------------------------------------------------------------------
	 */
	size_type size() const _es_noexcept_ { return this->__end - this->__begin; }
	size_type max_size() const _es_noexcept_ { return this->__alloc.max_size() / sizeof(value_type); }
	size_type capacity() const _es_noexcept_ { return __base::capacity_(); }
	bool	  empty() const _es_noexcept_ { return this->__begin == this->__end; };
	void	  reserve(size_type n) throw(std::length_error) _es_strong_;

	/**
	 * * [ modifiers ] -----------------------------------------------------------------------------
	 */
	__template_input__ void	   assign(_Input first, _Input last) _es_basic_ _ub_;
	void					   assign(size_type n, const value_type& u) _es_basic_ _ub_;
	void					   push_back(const value_type& x) _es_strong_ _ub_;
	void					   pop_back() _es_noexcept_ _ub_;
	iterator				   insert(const_iterator position, const value_type& x) _es_strong_ _ub_;
	iterator				   insert(const_iterator position, size_type n, const value_type& x) _es_strong_ _ub_;
	__template_iter__ iterator insert(const_iterator position, _Iter first, _Iter last) _es_strong_ _ub_;
	iterator				   erase(iterator position) _es_basic_ _ub_;
	iterator				   erase(iterator first, iterator last) _es_basic_ _ub_;
	void					   clear() _es_noexcept_;
	void					   swap(vector& x) _es_noexcept_ _ub_;
	void					   resize(size_type sz, value_type c = value_type()) _es_strong_;

	/**
	 * * [ private workhorse ] ---------------------------------------------------------------------
	 */
	private:
	inline bool invariants_size__() const;
	inline bool invariants_capacity__() const;

	/**
	 * * [ internal workhorse ] --------------------------------------------------------------------
	 */
	private:
	__template_input__ void internal_iterator_construct__(
	  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
								!ft::has_iterator_category_convertible_to< _Input, ft::forward_iterator_tag >::value,
							  _Input >::type first,
	  _Input								 last);
	__template_forward__ void internal_iterator_construct__(
	  typename ft::enable_if< ft::has_iterator_category_convertible_to< _Forward, ft::forward_iterator_tag >::value,
							  _Forward >::type first,
	  _Forward								   last);

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
				   const value_type&	 val,
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
	if (__data) {
		clear();
		__alloc.deallocate(__data, __capacity * sizeof(value_type));
	}
}

/**
 * * [ allocator ] ---------------------------------------------------------------------------------
 */

/**
 * * [ element access ] ----------------------------------------------------------------------------
 */
__template__
__return__() typename __vector__::reference __vector__::operator[](size_type n) _es_noexcept_ _ub_ {
	LOG_("vector: operator[]");
	static_assert_(n < size(), "vector: operator[] basic version: index out of bounds");
	return this->__begin[n];
}

__template__
__return__() typename __vector__::const_reference __vector__::operator[](size_type n) const _es_noexcept_ _ub_ {
	LOG_("vector: operator[] const version");
	static_assert_(n < size(), "vector: operator[] const version: index out of bounds");
	return this->__begin[n];
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
__template__
__return__(void) __vector__::clear() _es_noexcept_ {
	while (__size--) {
		__alloc.destroy(&__data[__size]);
	}
}

/**
 * * [ private workhorse ] -------------------------------------------------------------------------
 */

/**
 * * [ internal workhorse ] ------------------------------------------------------------------------
 */
__template__ __template_input__
__return__(void) __vector__::internal_iterator_construct__(
  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
							!ft::has_iterator_category_convertible_to< _Input, ft::forward_iterator_tag >::value,
						  _Input >::type first,
  _Input								 last) {
	LOG_C_("range constructor : input iterator", B_COLOR_YELLOW);
	for (; first != last; ++first) {
		push_back(*first);
	}
}
__template__ __template_forward__
__return__(void) __vector__::internal_iterator_construct__(
  typename ft::enable_if< ft::has_iterator_category_convertible_to< _Forward, ft::forward_iterator_tag >::value,
						  _Forward >::type first,
  _Forward								   last) {
	LOG_C_("range constructor : forward iterator", B_COLOR_YELLOW);
	(void)first;
	(void)last;
}

} /* namespace ft */

#undef __vector__
#undef __template_input__
#undef __template_forward__

#endif /* __VECTOR_HPP__ */
