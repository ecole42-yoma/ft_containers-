#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "./containers/vector.hpp"
#include "iterator/_iterator_traits.hpp"
#include "iterator/has_iterator_x.hpp"
#include "iterator/is_iterator_x.hpp"
#include "iterator/iterator_tag.hpp"
#include "type/allocator_traits.hpp"
#include "type/is_convertible.hpp"
#include "type/is_same.hpp"
#include "type/remove_cv.hpp"
#include "util/_core_utils.hpp"

void
test_throw() {
	throw "hi";
}

template< typename T >
struct test_input_iterator {
	typedef ft::forward_iterator_tag iterator_category;
	typedef T						 value_type;
	typedef ptrdiff_t				 difference_type;
	typedef T*						 pointer;
	typedef T&						 reference;
};
template< typename T >
struct test_allocator {
	typedef T value_type;

	typedef size_t	  size_type;
	typedef ptrdiff_t difference_type;
	typedef T*		  pointer;
	typedef const T*  const_pointer;
	typedef T&		  reference;
	typedef const T&  const_reference;
};

int
f(int n = 2) try {
	++n; // increments the function parameter
	throw n;
} catch (...) {
	++n; // n is in scope and still refers to the function parameter
	assert(n == 4);
	return n;
}

void
main2() {
	std::cout << f(2) << std::endl;
	// std::distance(std::vector< int >::iterator(), std::vector< int >::iterator());
	try {
		std::vector< int > v(10, 1);

		std::cout << v.at(9) << std::endl;
		std::cout << v.at(10) << std::endl;
	} catch (const char* e) {
		std::cout << e << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	} catch (...) {
		std::cout << "unknown error" << std::endl;
	}

	std::vector< int >	  vvvv;
	std::allocator< int > temppppp;
	ft::vector< int >	  v(10, 42);
	ft::vector< int >	  v2;
	if (ft::is_allocator< std::allocator< int > >::value) {
		std::cout << "is allocator" << std::endl;
	} else {
		std::cout << "is not allocator" << std::endl;
	}

	v2 = v;
	for (ft::vector< int >::iterator it = v2.begin(); it != v2.end(); ++it)
		std::cout << *it << std::endl;

	ft::vector< int >::iterator it	= v.begin();
	ft::vector< int >::iterator it2 = v.end();

	ft::vector< int > v3(it, it2);
	for (ft::vector< int >::iterator it = v3.begin(); it != v3.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << color_(RED) << "hi" << color_(RESET) << std::endl;
}

void
check_leaks() {
	system("leaks ft_containers");
}

int
main(int argc, char** argv) {
	if (argc != 1)
		atexit(check_leaks);
	(void)argv;
	main2();
}
