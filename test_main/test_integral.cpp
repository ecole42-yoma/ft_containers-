#include <iomanip>
#include <iostream>
// #include <type_traits>
#include "../include/type_traits.hpp"

class A {};

struct B {
	int x : 4 { 2 };
};
using BF = decltype(B::x); // bit-field's type

enum E : int {};

template< class T >
T
f(T i) {
	static_assert(ft::is_integral< T >::value, "Integral required.");
	return i;
}

#define SHOW(...) std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

int
main() {
	std::cout << std::boolalpha;

	SHOW(ft::is_integral< A >::value);
	SHOW(ft::is_integral< int >::value);
	SHOW(ft::is_integral_v< E >);
	SHOW(ft::is_integral_v< float >);
	SHOW(ft::is_integral_v< int* >);
	SHOW(ft::is_integral_v< int >);
	SHOW(ft::is_integral_v< const int >);
	SHOW(ft::is_integral_v< bool >);
	SHOW(ft::is_integral_v< char >);
	SHOW(ft::is_integral_v< BF >);
	SHOW(f(123));
}
