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

/*



 */

std::string b_string[64] = {
	"uvg6KqtcgduR31n3ajsv", "wbiAcjgojb9JOagZwyMn", "ATZKCzaPOqgkhPjwuGlf", "MOhaJs56yjOw8f6nLPRA",
	"0gyB2Tr42v6awMw2nK7J", "e6GsiLFUuoDpVFEhJKZ1", "z0jXAhiV9keBsaLOY0Xf", "P68p2ZAosHJdmoZh1C7N",
	"Pu3EuZVeY0TCO3ojdK0t", "z7jCHMooHCS73M8GygKB", "uT4KoK83JrZxZjkul7ty", "g8gfrZoY5XwfzRusvHvv",
	"7PGmkM0OSRnYREt9mFIP", "q1od7mBIpPEsCtpF9kdw", "XQo0LWId5TdZnLnpUNOb", "U0m1R0kFFhAFyS6hmHHw",
	"K0lPKfxJxIOnE8QB90xn", "cZ5xyQifMJhrKxqBK9A7", "cFBiwjfYw7Js6qEGy5Kt", "1tW0KWfXxeFO69tByqcE",
	"3Fvq9NxBrhPXHe0IlIVx", "MSRDjdFRvHAhFGhiMtDe", "zGm2joMh71jQkYzg5L4V", "Mq4RRaeLvSAO0z2ibp8Q",
	"WnLFYnQKP8TNJkqVVbUg", "E98UphbbVSzrW5Mzurmg", "F8HRxeEcaTZDkFPkioij", "jmUVl4Q8X5BwVNzXN219",
	"n7Xp4w4FwzGKit7AI4SO", "4MxXYr6rKOcXLt9UkVd2", "4RVTDsADtRyboaai9d29", "XaSqsrrtdhAfFoJIc5KK",
	"9Z9jdVCrTT09bg348ceb", "I6uqLG9dO5mfNdSMwOYm", "UwMTzJPlbnhgwbHpDi6w", "DebjMP9afncYE6GhhO00",
	"YGPuscYDiGfAjY1UWST0", "K6gbvgGjVZgEFUDlkdSk", "8xCBPI0w6TpC0RA62c2W", "fYMxkNwmKg3moP8KvD9v",
	"QpPdhwhEYjIugg3OPcPH", "qQBXjSn43I3EMP54SyxZ", "7qvdKwoW1CQEZTWPvuSC", "rCT212rdYO0zTGHXesKg",
	"dBHvlHsBwcR9MkkenYYG", "NQiSlergqR8fVbOeivLj", "xYVqsV147UIe7jVBVwXo", "tcxayO4DdEJ885TbqUMy",
	"9TGSMTD8U8ksRpHqq0cL", "TIJ16jCv9BSUiWvhbF9T", "BM9GL2ig1hePkA6lM6Ck", "TfJTYB9JQMU6CGcYg20Q",
	"Fg6e5YT2FQbpTZNTDqdo", "LI5q6ml40MeE9H1dPb93", "OaxJUSm3nYN9Y8Ela7sS", "BgBeODAwXz7xJo50Rwqd",
	"xdkgKj1dEoJ6zuVhkvvo", "olIewtUEvXJgs1lB9bCn", "dTsPDS0x2uXtcgOIJHb8", "DYvJ2phLppGNZKboTBrd",
	"DjNFMtt9PxkzqvWBHI6j", "1Z3YkeTFlPniKnzFhzgu", "76XqQg6hqMf5IXxKPOEs", "gzaapTWW7i9EZjjzLeK6"
};
void
main2() {
	ft::vector< std::string > v;

	std::cout << "hi" << std::endl;
	ft::vector< std::string >::iterator it = v.insert(v.end(), b_string[54]);

	std::cout << "hi" << std::endl;
}

void
check_leaks() {
	system("leaks ft_containers");
	// std::less< int > cmp;
}

int
main(int argc, char** argv) {
	if (argc != 1)
		atexit(check_leaks);
	(void)argv;
	main2();
	std::distance();
	// std::make_pair(0, 0);
	// std::map< int, int > m;
	// std::pair< int, int >(0, 0)
}
