#include <cstdlib>
#include <deque>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./containers/vector.hpp"
#include "iterator/_iterator_traits.hpp"
#include "iterator/has_iterator_x.hpp"
#include "iterator/is_iterator_x.hpp"
#include "type/allocator_traits.hpp"
#include "type/is_convertible.hpp"
#include "type/is_same.hpp"
#include "type/remove_cv.hpp"
#include "util/_core_utils.hpp"
#include <string>

#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector< T >::size_type

// namespace TESTED_NAMESPACE = ft;
namespace TESTED_NAMESPACE = std;

template< typename T >
void
printSize(TESTED_NAMESPACE::vector< T > const& vct, bool print_content = true) {
	const T_SIZE_TYPE size		   = vct.size();
	const T_SIZE_TYPE capacity	   = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content) {
		typename TESTED_NAMESPACE::vector< T >::const_iterator it  = vct.begin();
		typename TESTED_NAMESPACE::vector< T >::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void
test_throw() {
	throw "hi";
}

template< typename T >
struct test_input_iterator {
	typedef std::forward_iterator_tag iterator_category;
	typedef T						  value_type;
	typedef ptrdiff_t				  difference_type;
	typedef T*						  pointer;
	typedef T&						  reference;
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

#define TESTED_TYPE int
#include <list>

void
checkErase(TESTED_NAMESPACE::vector< TESTED_TYPE > const&				  vct,
		   TESTED_NAMESPACE::vector< TESTED_TYPE >::const_iterator const& it) {
	static int i = 0;
	std::cout << "[" << i++ << "] "
			  << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

void
main2() {

	TESTED_NAMESPACE::vector< TESTED_TYPE > vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));

	//
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
