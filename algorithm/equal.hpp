#pragma once
#ifndef __EQUAL_HPP__
#define __EQUAL_HPP__

namespace ft {

template< typename _Tp1, typename _Tp2 >
inline bool
equal(_Tp1 first_1, _Tp1 last_1, _Tp2 first_2) {
	for (; first_1 != last_1; ++first_1, ++first_2) {
		if (!(*first_1 == *first_2)) {
			return false;
		}
	}
	return true;
}

}

#endif
