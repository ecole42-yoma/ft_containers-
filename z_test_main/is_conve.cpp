#include <iostream>

struct S {};
struct T : public S {};

int
main() {
	S* s = new S;
	T* t = new T;
	s	 = t;
	if (__is_convertible_to(T, S)) {
		std::cout << "T is convertible to S" << std::endl;
	} else {
		std::cout << "T is not convertible to S" << std::endl;
	}
}
