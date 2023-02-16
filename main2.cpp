#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
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
	std::pair< int, char > temp;
	std::make_pair(1, 'a');
	ft::vector< int > a;
	a.push_back(1);
	std::cout << a.size() << " / " << a.capacity() << std::endl;
	a.push_back(2);
	std::cout << a.size() << " / " << a.capacity() << std::endl;
	a.push_back(3);
	std::cout << a.size() << " / " << a.capacity() << std::endl;
	a.push_back(4);
	std::cout << a.size() << " / " << a.capacity() << std::endl;
	a.push_back(4);
	std::cout << a.size() << " / " << a.capacity() << std::endl;
	{
		ft::vector< int >::iterator it	= a.begin();
		ft::vector< int >::iterator ite = a.end();
		a.erase(it, ite);
	}

	ft::vector< int > three(33, 3);
	// std::vector< int > a(10, 2);

	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	std::cout << a.max_size() << std::endl;
	// std::cout << a[9] << std::endl;

	// a.reserve(20);
	a.assign(three.begin(), three.end());
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	std::cout << a.max_size() << std::endl;
	// std::cout << a[9] << std::endl;

	a.resize(50, 5);
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	std::cout << a.max_size() << std::endl;
	std::cout << a[9] << std::endl;

	a.resize(20);
	ft::vector< int >::iterator it	= a.begin();
	ft::vector< int >::iterator it2 = a.end();
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
	std::cout << a.max_size() << std::endl;
	std::cout << *a.erase(it, it2) << std::endl;
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;

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
