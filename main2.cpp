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
#include "type/is_convertible.hpp"
#include "type/is_same.hpp"
#include "type/remove_cv.hpp"

void
test_throw() {
	throw "hi";
}

template< typename _T1, typename _T2 >
struct test_same : ft::is_same< _T2, _T1 > {};

template< typename _T1 >
struct test_conv : ft::is_convertible< typename _T1::iterator_category, ft::input_iterator_tag > {};

void
main2() {
	LOG_("test");

	if (test_conv< ft::vector< int >::iterator >::value) {
		std::cout << "conv" << std::endl;
	} else {
		std::cout << "not conv" << std::endl;
	}

	ft::vector< int >			temp(10, 2);
	ft::vector< int >::iterator it	= temp.begin();
	ft::vector< int >::iterator it2 = temp.end();
	ft::vector< int >			v(it, it2);

	if (test_same< ft::vector< int >::value_type, ft::vector< int >::iterator::value_type >::value) {
		std::cout << "same" << std::endl;
	} else {
		std::cout << "not same" << std::endl;
	}

	// ft::vector< int >::iterator::value_type temp;
	// std::vector< int >::iterator::value_type temp2;
	if (test_same< std::vector< int >::value_type, std::vector< int >::iterator::value_type >::value) {
		std::cout << "same" << std::endl;
	} else {
		std::cout << "not same" << std::endl;
	}
	if (test_same< std::vector< int >::iterator::value_type, int >::value) {
		std::cout << "same" << std::endl;
	} else {
		std::cout << "not same" << std::endl;
	}

	// if (ft::is_iterator< typename ft::iterator_traits< it >::iterator_category >::value) {
	// 	std::cout << "same" << std::endl;
	// } else {
	// 	std::cout << "not same" << std::endl;
	// }

	// ft::vector< int > v2(10);
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
