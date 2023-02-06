#pragma once
#ifndef __CORE_UTIL_HPP__
#define __CORE_UTIL_HPP__

#include <cassert>	 // assert
#include <limits>	 // numeric_limits
#include <memory>	 // alloc, auto_ptr
#include <stdexcept> // exception

#define Assert(expression, message) assert(expression&& message)

#endif
