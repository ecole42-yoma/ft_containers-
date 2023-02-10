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

void
main2() {

	ft::vector< int > v(10, 42);
	ft::vector< int > v2;

	v2 = v;
	for (ft::vector< int >::iterator it = v2.begin(); it != v2.end(); ++it)
		std::cout << *it << std::endl;

	ft::vector< int >::iterator it	= v.begin();
	ft::vector< int >::iterator it2 = v.end();

	ft::vector< int > v3(it, it2);
	for (ft::vector< int >::iterator it = v3.begin(); it != v3.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << color__(RED) << "hi" << color__(RESET) << std::endl;
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
