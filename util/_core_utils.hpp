#pragma once
#ifndef __CORE_UTIL_HPP__
#define __CORE_UTIL_HPP__

#include <cassert>	 // assert
#include <limits>	 // numeric_limits
#include <memory>	 // alloc, auto_ptr
#include <stdexcept> // exception

/**
 * * [ color define ] ------------------------------------------------------------------------------
 */
#define COLOR_RED	   "\033[1;31m"
#define COLOR_GREEN	   "\033[1;32m"
#define COLOR_YELLOW   "\033[1;33m"
#define COLOR_BLUE	   "\033[1;34m"
#define COLOR_PURPLE   "\033[1;35m"
#define COLOR_CYAN	   "\033[1;36m"
#define COLOR_WHITE	   "\033[1;37m"
#define COLOR_RESET	   "\033[0m"
#define B_COLOR_RESET  "\033[0m"
#define B_COLOR_RED	   "\033[1;41m"
#define B_COLOR_GREEN  "\033[1;42m"
#define B_COLOR_YELLOW "\033[1;43m"
#define B_COLOR_BLUE   "\033[1;44m"
#define B_COLOR_PURPLE "\033[1;45m"
#define B_COLOR_CYAN   "\033[1;46m"
#define B_COLOR_WHITE  "\033[1;47m"

#define COLOR_MAP(XX)            \
	XX(0, RED, \033[1;31m)       \
	XX(1, GREEN, \033[1;32m)     \
	XX(2, YELLOW, \033[1;33m)    \
	XX(3, BLUE, \033[1;34m)      \
	XX(4, PURPLE, \033[1;35m)    \
	XX(5, CYAN, \033[1;36m)      \
	XX(6, WHITE, \033[1;37m)     \
	XX(7, RESET, \033[0m)        \
	XX(8, B_RED, \033[1;41m)     \
	XX(9, B_GREEN, \033[1;42m)   \
	XX(10, B_YELLOW, \033[1;43m) \
	XX(11, B_BLUE, \033[1;44m)   \
	XX(12, B_PURPLE, \033[1;45m) \
	XX(13, B_CYAN, \033[1;46m)   \
	XX(14, B_WHITE, \033[1;47m)  \
	XX(15, B_RESET, \033[0m)

typedef enum color_state {
#define XX(num, name, string) name = num,
	COLOR_MAP(XX)
#undef XX
	  LAST
} color_state_e;

#include <string>
inline std::string
color_(color_state_e s) {
	switch (s) {
#define XX(num, name, string) \
	case name:                \
		return #string;
		COLOR_MAP(XX)
#undef XX
		default:
			return "<unknown>";
	}
}
#undef COLOR_MAP

/**
 * * [ own assert ] --------------------------------------------------------------------------------
 */
template< bool >
struct yoma_assert {};
template<>
struct yoma_assert< true > {
	yoma_assert(const char*) {}
};
#ifdef LOG
#define static_assert_(expression, message) yoma_assert< (expression) >(message)
#else
#define static_assert_(expression, message)
#endif

#define assert_(expression, message) assert(expression&& message)

/**
 * * [ own log ] -----------------------------------------------------------------------------------
 */
#define LOG_(context)		   log_(__func__, context)
#define LOG_C_(context, color) log_(__func__, context, color)

inline void
log_(const std::string& title, const char* context, const char* c1 = B_COLOR_GREEN, const char* c2 = COLOR_YELLOW) {
#ifdef LOG
	std::cout << c1 << title << COLOR_RESET << ": " << c2 << context << COLOR_RESET << std::endl;
#else
	(void)title;
	(void)context;
	(void)c1;
	(void)c2;
#endif
}

/**
 * * [ own define ] --------------------------------------------------------------------------------
 */
#define __template__	  template< typename _Tp, typename _Alloc >
#define __template_iter__ template< typename _Iter >
#define __return__(type)  type

#define _es_no_safety_
#define _es_noexcept_ throw()
#define _es_basic_
#define _es_strong_
#define _ub_

#endif
