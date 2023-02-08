#pragma once
#ifndef __REMOVE_CV_HPP__
#define __REMOVE_CV_HPP__

namespace ft {

template< class _Tp >
struct remove_const {
	typedef _Tp type;
};
template< class _Tp >
struct remove_const< const _Tp > {
	typedef _Tp type;
};

template< class _Tp >
struct remove_volatile {
	typedef _Tp type;
};
template< class _Tp >
struct remove_volatile< volatile _Tp > {
	typedef _Tp type;
};

template< class _Tp >
struct remove_cv {
	typedef typename remove_volatile< typename remove_const< _Tp >::type >::type type;
};

}
#endif
