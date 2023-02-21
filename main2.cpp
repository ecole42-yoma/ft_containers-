#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "./containers/stack.hpp"
#include "./containers/vector.hpp"
#include "iterator/_iterator_traits.hpp"
#include "iterator/has_iterator_x.hpp"
#include "iterator/is_iterator_x.hpp"
#include "type/allocator_traits.hpp"
#include "type/is_convertible.hpp"
#include "type/is_same.hpp"
#include "type/remove_cv.hpp"
#include "util/_core_utils.hpp"
#include <map>
#include <stack>
#include <string>

namespace TESTED_NAMESPACE = ft;
// namespace TESTED_NAMESPACE = std;

#include <iostream>
#include <string>

// --- Class foo
template< typename T >
class foo {
	public:
	typedef T value_type;

	foo(void)
	  : value()
	  , _verbose(false){};
	foo(value_type src, const bool verbose = false)
	  : value(src)
	  , _verbose(verbose){};
	foo(foo const& src, const bool verbose = false)
	  : value(src.value)
	  , _verbose(verbose){};
	~foo(void) {
		if (this->_verbose)
			std::cout << "~foo::foo()" << std::endl;
	};
	void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
	void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
	foo& operator=(value_type src) {
		this->value = src;
		return *this;
	};
	foo& operator=(foo const& src) {
		if (this->_verbose || src._verbose)
			std::cout << "foo::operator=(foo) CALLED" << std::endl;
		this->value = src.value;
		return *this;
	};
	value_type getValue(void) const { return this->value; };
	void	   switchVerbose(void) { this->_verbose = !(this->_verbose); };

	operator value_type(void) const { return value_type(this->value); }

	private:
	value_type value;
	bool	   _verbose;
};

template< typename T >
std::ostream&
operator<<(std::ostream& o, foo< T > const& bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template< typename T >
T
inc(T it, int n) {
	while (n-- > 0)
		++it;
	return (it);
}

template< typename T >
T
dec(T it, int n) {
	while (n-- > 0)
		--it;
	return (it);
}

template< typename T_STACK >
void
printSize(T_STACK& stck, bool print_content = 1) {
	std::cout << "size: " << stck.size() << std::endl;
	if (print_content) {
		std::cout << std::endl << "Content was:" << std::endl;
		while (stck.size() != 0) {
			std::cout << "- " << stck.top() << std::endl;
			stck.pop();
		}
	}
	std::cout << "###############################################" << std::endl;
}

#define TESTED_TYPE int
#define t_stack_	TESTED_NAMESPACE::stack< TESTED_TYPE >
typedef t_stack_::container_type container_type;

template< class T_STACK >
void
cmp(const T_STACK& lhs, const T_STACK& rhs) {
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############" << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs < rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs > rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}
void
main2() {

	container_type ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	t_stack_ stck(ctnr);
	t_stack_ stck2(ctnr);

	cmp(stck, stck);  // 0
	cmp(stck, stck2); // 1

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2); // 2
	cmp(stck2, stck); // 3

	stck.push(42);

	cmp(stck, stck2); // 4
	cmp(stck2, stck); // 5

	stck.push(100);

	cmp(stck, stck2); // 6
	cmp(stck2, stck); // 7
}

void
check_leaks() {
	system("leaks ft_containers");
	std::less< int > cmp;
}

int
main(int argc, char** argv) {
	if (argc != 1)
		atexit(check_leaks);
	(void)argv;
	main2();
	std::make_pair(0, 0);
	std::map< int, int > m;
	std::pair< int, int >(0, 0)
}
