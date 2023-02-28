#pragma once

#include <memory>
#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#ifdef BASIC
#include "_core_utils.hpp"
#include "_iterator_traits.hpp"
#include "_type_traits.hpp"
#include "equal.hpp"
#include "iterator.hpp"
#include "lexicographical_compare.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#else
#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"

#include "../iterator/_iterator_traits.hpp"
#include "../iterator/distance.hpp"
#include "../iterator/iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../iterator/wrap_iterator.hpp"

#include "../type/_type_traits.hpp"
#include "../type/allocator_traits.hpp"

#include "../util/_core_utils.hpp"
#endif

#include <algorithm> // swap, max, min
#include <iterator>	 // advance

#define __vector__			 vector< _Tp, _Alloc >
#define __vector_base__		 in_vector_base< _Tp, _Alloc >
#define __template__		 template< typename _Tp, typename _Alloc >
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
	typedef _Alloc allocator_type;
	// typedef ft::allocator_traits< allocator_type > _allocator_traits;

	protected:
	typedef _Tp										 value_type;
	typedef value_type&								 reference;
	typedef const value_type&						 const_reference;
	typedef typename allocator_type::size_type		 size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::const_pointer	 const_pointer;
	// typedef pointer									 iterator;
	// typedef const_pointer							 const_iterator;

	pointer		   __begin;
	pointer		   __end;
	pointer		   __end_capacity;
	allocator_type __alloc;

	explicit in_vector_base(const allocator_type& alloc = allocator_type()) _es_noexcept_;
	explicit in_vector_base(size_type n) _es_strong_;
	explicit in_vector_base(size_type n, const allocator_type& alloc) _es_strong_;
	~in_vector_base() _es_noexcept_;

	void			 allocate_(size_type n) throw(std::length_error) _es_strong_;
	void			 reserve_(size_type n) _es_strong_;
	void			 deallocate_() _es_noexcept_;
	void			 destruct_at_end_(pointer new_last) _es_noexcept_;
	void			 construct_at_end_(size_type n, const_reference value = value_type()) _es_noexcept_;
	inline size_type size_() const _es_noexcept_ { return static_cast< size_type >(__end - __begin); }
	inline size_type capacity_() const _es_noexcept_ { return static_cast< size_type >(__end_capacity - __begin); }
	inline size_type remain_size_() const _es_noexcept_ { return static_cast< size_type >(__end_capacity - __end); }
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
	LOG_("constuctor in_vector_base (alloc))");
}

__template__
__vector_base__::in_vector_base(size_type n) _es_strong_
  : __begin(NULL)
  , __end(NULL)
  , __end_capacity(NULL)
  , __alloc(allocator_type()) {
	LOG_("constuctor in_vector_base (size)");
	allocate_(n);
}

__template__
__vector_base__::in_vector_base(size_type n, const allocator_type& alloc) _es_strong_
  : __begin(NULL)
  , __end(NULL)
  , __end_capacity(NULL)
  , __alloc(alloc) {
	LOG_("constuctor in_vector_base (size, alloc)");
	allocate_(n);
}

__template__ __vector_base__::~in_vector_base() _es_noexcept_ {
	if (std::uncaught_exceptions() == true) {
		LOG_C_("destructor ~in_vector_base - called during stack unwinding", B_COLOR_RED);
	} else {
		LOG_C_("destructor ~in_vector_base - called normally", B_COLOR_BLUE);
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
__return__(void) __vector_base__::reserve_(size_type n) _es_strong_ {
	LOG_("in_vector_base");
	__vector_base__ temp(n, __alloc);
	const size_type old_size = size_();
	for (size_type i = 0; i < old_size; ++i) {
		__alloc.construct(temp.__begin + i, __begin[i]);
	}
	temp.__end = temp.__begin + old_size;
	this->swap_data_(temp);
}

__template__
__return__(void) __vector_base__::deallocate_() _es_noexcept_ {
	LOG_C_("in_vector_base", B_COLOR_PURPLE);
	if (__begin != NULL) {
		clear_();
		__alloc.deallocate(__begin, capacity_());
		__begin = __end = __end_capacity = NULL;
	}
}

__template__
__return__(void) __vector_base__::construct_at_end_(size_type n, const_reference value) _es_noexcept_ {
	LOG_C_("in_vector_base", B_COLOR_WHITE);
	pointer expect_end = __end + n;
	while (__end != expect_end) {
		__alloc.construct(__end++, value);
	}
}

__template__
__return__(void) __vector_base__::destruct_at_end_(pointer new_last) _es_noexcept_ {
	LOG_C_("in_vector_base", B_COLOR_PURPLE);
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
	__alloc		   = from.__alloc;
}

__template__
__return__(void) __vector_base__::swap_data_(in_vector_base& from) _es_noexcept_ {
	LOG_("in_vector_base");
	pointer		   temp_begin		 = __begin;
	pointer		   temp_end			 = __end;
	pointer		   temp_end_capacity = __end_capacity;
	allocator_type temp_alloc		 = __alloc;
	__begin							 = from.__begin;
	__end							 = from.__end;
	__end_capacity					 = from.__end_capacity;
	__alloc							 = from.__alloc;
	from.__begin					 = temp_begin;
	from.__end						 = temp_end;
	from.__end_capacity				 = temp_end_capacity;
	from.__alloc					 = temp_alloc;
}

/**
 * * [ vector container ] --------------------------------------------------------------------------
 * ! []
 * TODO - todo list
 * ? blue color
 *  @param parameter-name description
 *  @param ss
 */
template< typename _Tp, typename _Alloc = std::allocator< _Tp > >
class vector : private in_vector_base< _Tp, _Alloc > {
	/**
	 * * [ default type] ---------------------------------------------------------------------------
	 */
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
	typedef ft::_wrap_iter< pointer >			   iterator;
	typedef ft::_wrap_iter< const_pointer >		   const_iterator;
	typedef ft::reverse_iterator< iterator >	   reverse_iterator;
	typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;

	/**
	 * * [ default form] ---------------------------------------------------------------------------
	 */
	public:
	explicit vector(const allocator_type& alloc = allocator_type()) _es_strong_ _ub_; // default
	explicit vector(size_type			  n,
					const_reference		  val	= value_type(),
					const allocator_type& alloc = allocator_type()) _es_strong_ _ub_; // fill
	__template_input__ vector(_Input																   first,
							  typename ft::enable_if< ft::is_iterator< _Input >::value, _Input >::type last,
							  const allocator_type& alloc = allocator_type()) _es_strong_ _ub_; // range
	vector(const vector& from) _es_strong_ _ub_;												// copy
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
	inline iterator		   begin() _es_noexcept_ { return iterator(this->__begin); }
	inline const_iterator  begin() const _es_noexcept_ { return const_iterator(this->__begin); }
	inline iterator		   end() _es_noexcept_ { return iterator(this->__end); }
	inline const_iterator  end() const _es_noexcept_ { return const_iterator(this->__end); }
	reverse_iterator	   rbegin() _es_noexcept_ { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const _es_noexcept_ { return const_reverse_iterator(end()); }
	reverse_iterator	   rend() _es_noexcept_ { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const _es_noexcept_ { return const_reverse_iterator(begin()); }

	/**
	 * * [ capacity ] ------------------------------------------------------------------------------
	 */
	inline size_type size() const _es_noexcept_ { return __base::size_(); }
	inline size_type max_size() const _es_noexcept_ {
		return std::min< size_type >(this->__alloc.max_size(), std::numeric_limits< difference_type >::max());
	}
	inline size_type capacity() const _es_noexcept_ { return __base::capacity_(); }
	inline bool		 empty() const _es_noexcept_ { return this->__begin == this->__end; };

	/**
	 * * [ modifiers ] -----------------------------------------------------------------------------
	 */
	__template_input__ __return__() typename ft::enable_if< ft::is_iterator< _Input >::value, void >::type
	  assign(_Input first, _Input last) _es_basic_ _ub_;
	void					   assign(size_type n, const_reference value) _es_basic_ _ub_;
	void					   push_back(const_reference x) _es_strong_ _ub_;
	void					   pop_back() _es_noexcept_ _ub_;
	iterator				   insert(iterator position, const_reference x) _es_strong_ _ub_;
	iterator				   insert(iterator position, size_type n, const_reference x) _es_strong_ _ub_;
	__template_iter__ iterator insert(iterator																 position,
									  typename ft::enable_if< ft::is_iterator< _Iter >::value, _Iter >::type first,
									  _Iter last) _es_strong_ _ub_;
	iterator				   erase(iterator position) _es_basic_ _ub_;
	iterator				   erase(iterator first, iterator last) _es_basic_ _ub_;
	void					   clear() _es_noexcept_ { __base::clear_(); }
	void					   swap(vector& x) _es_noexcept_ _ub_;
	void					   resize(size_type sz, value_type c = value_type()) _es_strong_;
	void					   reserve(size_type n) throw(std::length_error) _es_strong_;

	/**
	 * * [ private workhorse ] ---------------------------------------------------------------------
	 */
	private:
	inline bool invariants__() const _es_noexcept_;
	size_type	recommend_size__(size_type new_size) const throw(std::length_error) _es_basic_;

	__template_up__ inline _Up* data_ptr__(_Up* ptr) _es_noexcept_ { return ptr; }
	__template_up__ inline _Up* data_ptr__(_Up* ptr) const _es_noexcept_ { return ptr; }
	__template_ptr__ inline typename __vector_base__::value_type* data_ptr__(_Ptr ptr) _es_noexcept_ {
		return empty() ? (value_type*)0 : ptr.operator->();
	}
	__template_ptr__ inline const typename __vector_base__::value_type* data_ptr__(_Ptr ptr) const _es_noexcept_ {
		return empty() ? (const value_type*)0 : ptr.operator->();
	}

	inline iterator		  make_iter__(pointer ptr) _es_noexcept_ { return iterator(ptr); }
	inline const_iterator make_iter__(const_pointer ptr) const _es_noexcept_ { return const_iterator(ptr); }

	/**
	 * * [ internal workhorse ] --------------------------------------------------------------------
	 */
	private:
	__template_input__ typename ft::void_t<
	  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
								!ft::is_iterator_category_convertible_to< _Input, std::forward_iterator_tag >::value,
							  _Input >::type >::type
	internal_iterator_construct__(_Input first, _Input last, const allocator_type& alloc);
	__template_forward__ typename ft::void_t<
	  typename ft::enable_if< ft::is_iterator_category_convertible_to< _Forward, std::forward_iterator_tag >::value,
							  _Forward >::type >::type
	internal_iterator_construct__(_Forward first, _Forward last, const allocator_type& alloc);

	__template_input__ typename ft::void_t<
	  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
								!ft::is_iterator_category_convertible_to< _Input, std::forward_iterator_tag >::value,
							  _Input >::type >::type
	internal_assign__(_Input first, _Input last, const allocator_type& alloc);
	__template_forward__ typename ft::void_t<
	  typename ft::enable_if< ft::is_iterator_category_convertible_to< _Forward, std::forward_iterator_tag >::value,
							  _Forward >::type >::type
	internal_assign__(_Forward first, _Forward last, const allocator_type& alloc);

}; /* class vector */

/**
 * * [ default form] -------------------------------------------------------------------------------
 */
__template__
__vector__::vector(const allocator_type& alloc) _es_strong_ _ub_ // default
  try : __base(alloc) {
	LOG_("default constructor");
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
	throw;
} catch (...) {
	throw;
}

__template__
__vector__::vector(size_type			 n,
				   const_reference		 val,
				   const allocator_type& alloc) _es_strong_ _ub_ // fill
  try : __base(n, alloc) {
	LOG_("fill constructor");
	assign(n, val);
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
	throw;
} catch (...) {
	throw;
}

__template__ __template_input__
__vector__::vector(_Input																	first,
				   typename ft::enable_if< ft::is_iterator< _Input >::value, _Input >::type last,
				   const allocator_type& alloc) _es_strong_ _ub_ // range
  try : __base(alloc) {
	LOG_("range constructor : iterator");
	internal_iterator_construct__(first, last, alloc);
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
	throw;
} catch (...) {
	throw;
}

__template__
__vector__::vector(const vector& from) _es_strong_ _ub_ // copy
  try : __base(from.size(), from.__alloc) {
	LOG_("copy constructor");
	*this = from;
} catch (const std::exception& e) {
	std::cerr << e.what() << std::endl;
	throw;
} catch (...) {
	throw;
}

__template__
__return__(__vector__&) __vector__::operator=(const vector& from) _es_basic_ _ub_ {
	LOG_("copy assignment operator");
	if (this != &from) {
		internal_assign__(from.begin(), from.end(), from.__alloc);
	}
	return *this;
}

__template__
__return__() __vector__::~vector() _es_noexcept_ {
	if (std::uncaught_exceptions() == true) {
		LOG_C_("called during stack unwinding", B_COLOR_RED);
	} else {
		LOG_C_("called normally", B_COLOR_BLUE);
	}
}

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
 * * [ modifiers ] ---------------------------------------------------------------------------------
 */
__template__ __template_input__
__return__() typename ft::enable_if< ft::is_iterator< _Input >::value, void >::type
  __vector__::assign(_Input first, _Input last) _es_basic_ _ub_ {
	LOG_("vector: assign (range)");
	internal_assign__(first, last, this->__alloc);
}

__template__ void
__vector__::assign(size_type n, const_reference value) _es_basic_ _ub_ {
	LOG_("vector: assign (fill)");
	if (n > capacity()) {
		vector temp(n, value);
		this->swap(temp);
	} else if (n > size()) {
		std::fill(this->__begin, this->__end, value);
		const size_type remain = n - size();
		this->construct_at_end_(remain, value);
	} else {
		std::fill_n(this->__begin, n, value);
		const size_type remain = size() - n;
		this->destruct_at_end_(this->__end - remain);
	}
}

__template__
__return__(void) __vector__::push_back(const_reference x) _es_strong_ _ub_ {
	LOG_("vector: push_back");
	if (this->__end == this->__end_capacity) {
		this->reserve_(recommend_size__(size() + 1));
	}
	this->construct_at_end_(1, x);
}

__template__
__return__(void) __vector__::pop_back() _es_noexcept_ _ub_ {
	LOG_("vector: pop_back");
	assert_((!empty()), "vector : pop_back : called for empty vector");
	this->destruct_at_end_(this->__end - 1);
}

__template__
__return__() typename __vector__::iterator __vector__::insert(iterator position, const_reference x) _es_strong_ _ub_ {
	LOG_("vector: insert (value)");
	return (insert(position, size_type(1), x));
}

__template__
__return__()
  typename __vector__::iterator __vector__::insert(iterator position, size_type n, const_reference x) _es_strong_ _ub_ {
	LOG_("vector: insert (fill)");
	const difference_type offset = ft::distance(begin(), position);

	if (n > 0) {
		if (n > this->remain_size_()) {
			vector temp(size() + n);
			std::uninitialized_copy(this->__begin, this->__begin + offset, temp.begin());
			std::uninitialized_fill_n(temp.begin() + offset, n, x);
			std::uninitialized_copy(this->__begin + offset, this->__end, temp.begin() + offset + n);
			temp.__end = temp.__begin + size() + n;
			this->swap(temp);
		} else {
			this->construct_at_end_(n, x);
			std::copy_backward(this->__begin + offset, this->__end - n, this->__end);
			std::fill_n(this->__begin + offset, n, x);
		}
	}
	return make_iter__(this->__begin + offset);
}

__template__ __template_iter__
__return__() typename __vector__::iterator
  __vector__::insert(iterator																position,
					 typename ft::enable_if< ft::is_iterator< _Iter >::value, _Iter >::type first,
					 _Iter																	last) _es_strong_ _ub_ {
	LOG_("vector: insert (range)");
	const difference_type offset = ft::distance(begin(), position);
	const difference_type n		 = ft::distance(first, last);

	if (n > 0) {
		if (static_cast< size_type >(n) > this->remain_size_()) {
			__vector__ temp(size() + n);

			std::uninitialized_copy(this->__begin, this->__begin + offset, temp.begin());
			std::uninitialized_copy(first, last, temp.begin() + offset);
			std::uninitialized_copy(this->__begin + offset, this->__end, temp.begin() + offset + n);
			temp.__end = temp.__begin + size() + n;
			this->swap(temp);
		} else {
			this->construct_at_end_(n, value_type());
			std::copy_backward(this->__begin + offset, this->__end, this->__end + n);
			std::copy(first, last, this->__begin + offset);
		}
	}
	return make_iter__(this->__begin + offset);
}

__template__
__return__() typename __vector__::iterator __vector__::erase(iterator position) _es_basic_ _ub_ {
	LOG_("vector: erase (position)");
	assert_((position >= begin() && position < end()), "vector : erase [position] : invalid iterator");
	difference_type diff = ft::distance(begin(), position);
	pointer			pin	 = this->__begin + diff;
	this->destruct_at_end_(std::copy(pin + 1, this->__end, pin));
	return iterator(pin);
}

__template__
__return__() typename __vector__::iterator __vector__::erase(iterator first, iterator last) _es_basic_ _ub_ {
	LOG_("vector: erase (range)");
	assert_((first >= begin() && first < end() && first < last && last >= begin() && last <= end()),
			"vector : erase [range] : invalid iterator");
	difference_type diff = ft::distance(begin(), first);
	if (first != last) {
		pointer pin = this->__begin + diff;
		this->destruct_at_end_(std::copy(pin + ft::distance(first, last), this->__end, pin));
	}
	return iterator(begin() + diff);
}

__template__ void
__vector__::swap(vector& x) _es_noexcept_ _ub_ {
	LOG_("vector: swap");
	std::swap(this->__begin, x.__begin);
	std::swap(this->__end, x.__end);
	std::swap(this->__end_capacity, x.__end_capacity);
	std::swap(this->__alloc, x.__alloc);
}

__template__
__return__(void) __vector__::resize(size_type sz, value_type c) _es_strong_ {
	LOG_("vector: resize");
	size_type current_size = size();
	if (sz > current_size) {
		if (sz > capacity()) {
			this->reserve_(sz);
		}
		this->construct_at_end_(sz - current_size, c);
	} else if (sz < current_size) {
		this->destruct_at_end_(this->__begin + sz);
	}
}

__template__ void
__vector__::reserve(size_type n) throw(std::length_error) _es_strong_ {
	LOG_("vector: reserve");
	if (n > max_size()) {
		throw std::length_error("vector: reserve : length_error");
	}
	if (n > capacity()) {
		try {
			this->reserve_(n);
		} catch (...) {
			// TODO : handle exception
		}
	}
}

/**
 * * [ private workhorse ] -------------------------------------------------------------------------
 */
__template__
__return__(bool) __vector__::invariants__() const _es_noexcept_ {
	LOG_C_("vector: invariants", B_COLOR_YELLOW);
	if ((this->__begin == NULL && (this->__end != NULL || this->__end_capacity != NULL)) ||
		(this->__begin > this->__end) || (this->__begin == this->__end_capacity) ||
		(this->__end > this->__end_capacity)) {
		return false;
	}
	return true;
}

__template__
__return__() typename __vector__::size_type __vector__::recommend_size__(size_type new_size) const
  throw(std::length_error) _es_basic_ {
	if (new_size > max_size()) {
		throw std::length_error("vector: recommend_size__ : length_error");
	}
	if ((new_size * 2) > (max_size() * 0.5)) {
		return max_size();
	}
	return std::max< size_type >(2 * capacity(), new_size);
}

/**
 * * [ internal workhorse ] ------------------------------------------------------------------------
 */
__template__ __template_input__
__return__() typename ft::void_t<
  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
							!ft::is_iterator_category_convertible_to< _Input, std::forward_iterator_tag >::value,
						  _Input >::type >::type
  __vector__::internal_iterator_construct__(_Input first, _Input last, const allocator_type& alloc) {
	LOG_C_("internal_range constructor : input iterator", B_COLOR_YELLOW);
	internal_assign__(first, last, alloc);
}

__template__ __template_forward__
__return__() typename ft::void_t<
  typename ft::enable_if< ft::is_iterator_category_convertible_to< _Forward, std::forward_iterator_tag >::value,
						  _Forward >::type >::type
  __vector__::internal_iterator_construct__(_Forward first, _Forward last, const allocator_type& alloc) {
	LOG_C_("internal_range constructor : forward iterator", B_COLOR_YELLOW);
	const difference_type n = ft::distance(first, last);
	this->allocate_(n);
	internal_assign__(first, last, alloc);
}

__template__ __template_input__
__return__() typename ft::void_t<
  typename ft::enable_if< ft::is_iterator_of_input< _Input >::value &&
							!ft::is_iterator_category_convertible_to< _Input, std::forward_iterator_tag >::value,
						  _Input >::type >::type __vector__::internal_assign__(_Input				 first,
																			   _Input				 last,
																			   const allocator_type& alloc) {
	LOG_C_("internal_assign : input iterator", B_COLOR_YELLOW);
	this->__alloc	   = alloc;
	pointer copy_begin = this->__begin;

	for (; copy_begin != this->__end && first != last; ++copy_begin, ++first) {
		*copy_begin = *first;
	}
	if (first == last) {
		this->destruct_at_end_(copy_begin);
	} else {
		for (; first != last; ++first) {
			push_back(*first);
		}
	}
}

__template__ __template_forward__
__return__() typename ft::void_t<
  typename ft::enable_if< ft::is_iterator_category_convertible_to< _Forward, std::forward_iterator_tag >::value,
						  _Forward >::type >::type __vector__::internal_assign__(_Forward			   first,
																				 _Forward			   last,
																				 const allocator_type& alloc) {
	LOG_C_("internal_assign : forward iterator", B_COLOR_YELLOW);
	const difference_type n = ft::distance(first, last);

	if (n > static_cast< difference_type >(capacity())) {
		vector temp(first, last, alloc);

		this->swap(temp);
	} else {
		this->destruct_at_end_(this->__begin);
		// std::uninitialized_copy(first, last, this->__begin);
		for (difference_type i = 0; i < n; ++i, ++first) {
			this->__alloc.construct(this->__begin + i, *first);
		}
		this->__end = this->__begin + n;
	}
	this->__alloc = alloc;
}

/**
 * * [ non-member function overloads ] -------------------------------------------------------------
 */
__template__
__return__(bool)
operator==(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_ {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
__template__
__return__(bool)
operator!=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_ {
	return !(lhs == rhs);
}
__template__
__return__(bool)
operator<(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_ {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
__template__
__return__(bool)
operator<=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_ {
	return !(rhs < lhs);
}
__template__
__return__(bool)
operator>(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_ {
	return rhs < lhs;
}
__template__
__return__(bool)
operator>=(const ft::vector< _Tp, _Alloc >& lhs, const ft::vector< _Tp, _Alloc >& rhs) _es_noexcept_ {
	return !(lhs < rhs);
}

__template__
__return__() inline void swap(ft::__vector__& lhs, ft::__vector__& rhs) {
	lhs.swap(rhs);
}

} /* namespace ft */

#undef __vector__
#undef __vector_base__
#undef __template_input__
#undef __template_forward__
#undef __template_up__
#undef __template_ptr__
#undef __template__

#endif /* __VECTOR_HPP__ */
