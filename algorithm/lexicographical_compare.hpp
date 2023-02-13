#pragma once
#ifndef __LEXICOGRAPHICAL_COMPARE_HPP__
#define __LEXICOGRAPHICAL_COMPARE_HPP__

namespace ft {

template< typename _Tp1, typename _Tp2 >
inline bool
lexicographical_compare(_Tp1 first_1, _Tp1 last_1, _Tp2 first_2, _Tp2 last_2) {
	for (; first_1 != last_1 && first_2 != last_2; ++first_1, ++first_2) {
		if (*first_1 < *first_2) {
			return true;
		}
		if (*first_2 < *first_1) {
			return false;
		}
	}
	return first_1 == last_1 && first_2 != last_2;
}

template< typename _Tp1, typename _Tp2, typename _Compare >
inline bool
lexicographical_compare(_Tp1 first_1, _Tp1 last_1, _Tp2 first_2, _Tp2 last_2, _Compare comp) {
	for (; first_1 != last_1 && first_2 != last_2; ++first_1, ++first_2) {
		if (comp(*first_1, *first_2)) {
			return true;
		}
		if (comp(*first_2, *first_1)) {
			return false;
		}
	}
	return first_1 == last_1 && first_2 != last_2;
}

}
#endif
