#pragma once
#ifndef __UTILITY__HPP__
#define __UTILITY__HPP__

#include <algorithm>

namespace ft {

template< typename _T1, typename _T2 >
struct pair {
	typedef _T1 first_type;
	typedef _T2 second_type;

	first_type	first;
	second_type second;

	pair()
	  : first()
	  , second() {}

	pair(_T1 const& t1, _T2 const& t2)
	  : first(t1)
	  , second(t2) {}

	template< typename _U1, typename _U2 >
	pair(const pair< _U1, _U2 >& p)
	  : first(p.first)
	  , second(p.second) {}

	pair& operator=(pair const& p) {
		if (this != &p) {
			first  = p.first;
			second = p.second;
		}
		return *this;
	}

	void swap(pair& p) {
		std::swap(first, p.first);
		std::swap(second, p.second);
	}
};

template< typename _T1, typename _T2 >
inline bool
operator==(const pair< _T1, _T2 >& lhs, const pair< _T1, _T2 >& rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template< typename _T1, typename _T2 >
inline bool
operator!=(const pair< _T1, _T2 >& lhs, const pair< _T1, _T2 >& rhs) {
	return !(lhs == rhs);
}

template< typename _T1, typename _T2 >
inline bool
operator<(const pair< _T1, _T2 >& lhs, const pair< _T1, _T2 >& rhs) {
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template< typename _T1, typename _T2 >
inline bool
operator>(const pair< _T1, _T2 >& lhs, const pair< _T1, _T2 >& rhs) {
	return rhs < lhs;
}

template< typename _T1, typename _T2 >
inline bool
operator<=(const pair< _T1, _T2 >& lhs, const pair< _T1, _T2 >& rhs) {
	return !(rhs < lhs);
}

template< typename _T1, typename _T2 >
inline bool
operator>=(const pair< _T1, _T2 >& lhs, const pair< _T1, _T2 >& rhs) {
	return !(lhs < rhs);
}

// template< typename _T1, typename _T2 >
// inline void
// swap(pair< _T1, _T2 >& x, pair< _T1, _T2 >& y) {
// 	x.swap(y);
// }

template< typename _T1, typename _T2 >
inline ft::pair< _T1, _T2 >
make_pair(_T1 x, _T2 y) {
	return ft::pair< _T1, _T2 >(x, y);
}

}
#endif
