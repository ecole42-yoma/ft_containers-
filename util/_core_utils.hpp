#pragma once
#ifndef __CORE_UTIL_HPP__
#define __CORE_UTIL_HPP__

#include <cassert>	 // assert
#include <limits>	 // numeric_limits
#include <memory>	 // alloc, auto_ptr
#include <stdexcept> // exception

template< bool >
struct yoma_assert {};
template<>
struct yoma_assert< true > {
	yoma_assert(const char*) {}
};

#define static_assert_(expression, message) yoma_assert< (expression) >(message)

#endif
