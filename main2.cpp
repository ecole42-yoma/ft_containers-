#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "./containers/vector.hpp"
#include "iterator/_iterator_traits.hpp"
#include "iterator/has_iterator_x.hpp"
#include "iterator/is_iterator.hpp"
#include "type/is_convertible.hpp"
#include "type/remove_cv.hpp"

void
test_throw() {
	throw "hi";
}

void
main2() {
	LOG_("test");

	if (ft::is_same< ft::remove_cv< volatile const int >::type, int >::value) {
		std::cout << "same" << std::endl;
	} else {
		std::cout << "not same" << std::endl;
	}
	ft::vector< int >			temp(10, 2);
	ft::vector< int >::iterator it	= temp.begin();
	ft::vector< int >::iterator it2 = temp.end();
	ft::vector< int >			v(it, it2);

	ft::vector< int >::iterator::value_type temp;
	// std::vector< int >::iterator::value_type temp2;
	std::vector< int >::iterator temp2;

	if (ft::is_iterator< ft::iterator_traits< temp2 > >::value) {
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
main() {
	atexit(check_leaks);
	main2();
}
