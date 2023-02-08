#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

template< bool >
struct yoma_assert {};
template<>
struct yoma_assert< true > {
	yoma_assert(const char*) {}
};

#define static_assert_(expression, message) yoma_assert< (expression) >(message)

class yoma {

	public:
	yoma(int) { std::cout << "yoma() called" << std::endl; }

	~yoma() { std::cout << "~yoma() called" << std::endl; }
};

int
main(int argc, char** argv) {
	// std::allocator< int > alloc;
	static_assert(std::is_integral< int >::value, "hi");
	if (argc == 2) {
		std::vector< int > v;
		// std::vector< int > v = { 1, 2, 3, 4 };
		// v.reserve(std::atoi(argv[1]));
		for (int i = 0; i < std::atoi(argv[1]); ++i) {
			std::cout << "v.capacity() = " << v.capacity() << std::endl;
			v.push_back(i);
			std::cout << "v.[i] = " << v[i] << std::endl;
		}
		int i = 10;
		// static_assert((i > 10), "hi");
		static_assert_((std::is_same< int, int >::value), "hi");
		// static_assert_((std::is_same< int, char >::value), "hi");
		// yoma_assert< (std::is_same< int, float >::value) >("hi");
	}
	std::allocator< int > alloc_int;

	std::cout << std::numeric_limits< int >::min() << std::endl;
	std::cout << std::numeric_limits< int >::max() << std::endl;
	std::cout << std::numeric_limits< size_t >::max() << std::endl;
	std::cout << std::numeric_limits< long >::max() << std::endl;
	std::cout << std::numeric_limits< long long >::max() << std::endl;

	{
		yoma* y = new yoma(10);
		std::cout << std::endl;
		// yoma* y2 = ::operator new (yoma[10])(0);
	}
	return 0;
}
