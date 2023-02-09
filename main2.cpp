#include <cstdlib>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "./containers/vector.hpp"

void
test_throw() {
	throw "hi";
}

void
main2() {
	LOG_("test");

	std::cout << "test init" << std::endl;
	ft::vector< int > v(10, 2);
	std::cout << "v.size() = " << v.size() << std::endl;
	std::cout << "v.capacity() = " << v.capacity() << std::endl;
	std::vector< int > v2;

	ft::vector< int >::iterator it = v.begin();
	(void)it;
	{
		// test_throw();
		try {
			// v2.reserve(0);
			// v2.reserve((v2.max_size() / sizeof(int)));
			std::cout << v2.max_size() << std::endl;
			std::cout << v2.max_size() / sizeof(int) << std::endl;
			int				   size = 10;
			std::vector< int > tt(size, 1, std::allocator< int >());
			ft::vector< int >  vv(size, 1, std::allocator< int >());

		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			std::cout << "error\n";
		} catch (...) {
			std::cout << "unknown exception" << std::endl;
		}
	}
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
