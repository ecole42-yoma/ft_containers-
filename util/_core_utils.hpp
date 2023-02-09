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

/**
 * * [ own assert ] --------------------------------------------------------------------------------
 */
template< bool >
struct yoma_assert {};
template<>
struct yoma_assert< true > {
	yoma_assert(const char*) {}
};
#define static_assert_(expression, message) yoma_assert< (expression) >(message)

/**
 * * [ own log ] -----------------------------------------------------------------------------------
 */
#define LOG_(context) log_(__func__, context)
inline void
log_(const std::string& title, const char* context, const char* c1 = B_COLOR_GREEN, const char* c2 = COLOR_YELLOW) {
#ifdef LOG
	std::cout << c1 << title << COLOR_RESET << ": " << c2 << context << COLOR_RESET << std::endl;
#else
	(void)title;
	(void)context;
#endif
}

#endif
