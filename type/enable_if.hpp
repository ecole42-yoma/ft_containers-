#pragma once
#ifndef __ENABLE_IF_HPP__
#define __ENABLE_IF_HPP__

namespace ft {

template< bool, typename _Tp = void >
struct enable_if {};

template< class _Tp >
struct enable_if< true, _Tp > {
	typedef _Tp type;
};

template< bool _Bp, typename _Tp = void >
struct enable_if_t : public enable_if< _Bp, _Tp >::type {};

}

#endif
