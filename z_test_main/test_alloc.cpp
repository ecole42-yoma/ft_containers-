#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

int
main(int argc, char** argv) {
	// std::allocator< int > alloc;
	if (argc == 2) {
		std::vector< int > v;
		v.reserve(std::atoi(argv[1]));

		std::cout << "v.capacity() = " << v.capacity() << std::endl;
	}

	std::cout << std::numeric_limits< int >::min() << std::endl;
	std::cout << std::numeric_limits< int >::max() << std::endl;
	std::cout << std::numeric_limits< size_t >::max() << std::endl;
	std::cout << std::numeric_limits< long >::max() << std::endl;
	std::cout << std::numeric_limits< long long >::max() << std::endl;
	return 0;
}
