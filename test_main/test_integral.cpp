#include <iomanip>
#include <iostream>
// #include <type_traits>
#include "../include/type_traits.hpp"
#include <cassert>

class A {};

// struct B {
// 	int x : 1;
// };
// using BF = decltype(B::x); // bit-field's type

enum E : int {};

template< class T >
T
f(T i) {
	static_assert(ft::is_integral< T >::value, "Integral required.");
	return i;
}

#define SHOW(...) std::cout << std::setw(33) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

int
main() {
	std::cout << std::boolalpha;
	assert((ft::is_same< ft::is_integral_t< int >, ft::is_integral_t< int > >::value));
	// assert((ft::is_same< ft::is_integral_t< int >, ft::is_integral_t< unsigned int > >::value));
	bool temp = ft::is_same< ft::is_integral_t< int >, ft::is_integral_t< int > >::value;
	std::cout << temp << " next" << std::endl;
	temp = ft::is_same< ft::is_integral_t< long >, ft::is_integral_t< long > >::value;
	std::cout << temp << " next" << std::endl;
	SHOW(ft::is_same< int, int >::value);
	SHOW(ft::is_same< int, char >::value);
	SHOW(ft::is_same< char, char >::value);
	SHOW(ft::is_integral< A >::value);
	SHOW(ft::is_integral< int >::value);
	SHOW(ft::is_integral< E >());
	SHOW(ft::is_integral< float >());
	SHOW(ft::is_integral< int >());
	// assert(ft::is_integral_t< A >() == ft::true_type());

	if (ft::is_integral< int >() == ft::is_integral< A >()) {
		std::cout << "true" << std::endl;
	} else {
		std::cout << "false" << std::endl;
	}
	// SHOW(ft::is_integral_v< E >);
	// SHOW(ft::is_integral_v< float >);
	// SHOW(ft::is_integral_v< int* >);
	// SHOW(ft::is_integral_v< int >);
	// SHOW(ft::is_integral_v< const int >);
	// SHOW(ft::is_integral_v< bool >);
	// SHOW(ft::is_integral_v< char >);
	// SHOW(ft::is_integral_v< BF >);
	SHOW(f(123));
}
