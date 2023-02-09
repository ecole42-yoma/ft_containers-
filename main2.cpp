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

void
test_throw() {
	throw "hi";
}

void
main2() {

	ft::vector< int > v(10, 42);
	ft::vector< int > v2;

	v2 = v;
	for (ft::vector< int >::iterator it = v2.begin(); it != v2.end(); ++it)
		std::cout << *it << std::endl;
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
