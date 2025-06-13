#ifndef DEBUG_UTILS_HPP
#define DEBUG_UTILS_HPP

#include <iostream>        // For std::cerr, std::ostream, std::endl
#include <string>          // For std::string
#include <vector>          // For std::vector (used in container output helper)
#include <utility>         // For std::pair, std::forward
#include <source_location> // For std::source_location
#include <filesystem>      // For std::filesystem::path
#include <algorithm>       // For std::max/min (not directly used here, but often useful), std::forward
#include <type_traits>     // For std::enable_if, std::is_same

// Define colors as empty strings by default or if LOCAL is not defined.
// These will be overridden if LOCAL is defined.
#ifndef RESET
#define RESET ""
#endif
#ifndef RED
#define RED ""
#endif
#ifndef BLUE
#define BLUE ""
#endif
#ifndef GREEN
#define GREEN ""
#endif

// ─────────── PRACTICE ASSERT/TRACE HOOKS ─────────
//  PRACTICE flag enables runtime asserts, tracing and brute solvers.
#ifdef PRACTICE
// ASSERT: crash-fast on invariants.
#define ASSERT(cond, msg)                                                                 \
    if (!(cond))                                                                          \
    {                                                                                     \
        std::cerr << RED << "ASSERT FAIL @ "                                              \
                  << std::filesystem::path(std::source_location::current().file_name())   \
                         .filename()                                                      \
                         .string()                                                        \
                  << ":" << std::source_location::current().line()                        \
                  << " (\"" << std::source_location::current().function_name() << "\"): " \
                  << RESET << (msg) << RESET << std::endl;                                \
        exit(42);                                                                         \
    }

// TRACE: handy logging for PRACTICE builds, toggle with -DLOCAL
#ifdef LOCAL
// Forward declaration for dbg, which is defined further down within the #ifdef LOCAL block
template <typename... Args_dbg>
void dbg(const std::source_location loc, Args_dbg &&...args);

#define TRACE(...) dbg(std::source_location::current(), __VA_ARGS__)
#else // LOCAL for TRACE
#define TRACE(...) ((void)0)
#endif // LOCAL for TRACE

#else // PRACTICE
#define ASSERT(cond, msg) ((void)0)
#define TRACE(...) ((void)0)
#endif // PRACTICE

// ────────────── DEBUGGING (Color + Context) ────────────
//  Use DEBUG(a,b,v) to print state with file/line, colored, local only.
#ifdef LOCAL
// Override colors with actual escape codes if LOCAL is defined.
#undef RESET
#undef RED
#undef BLUE
#undef GREEN
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"

// Helper for dbg to print pairs
template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}

// Helper for dbg to print vectors and other compatible containers
template <typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value, typename T_container::value_type>::type>
std::ostream &operator<<(std::ostream &os, const T_container &v)
{
    os << '{';
    std::string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}

// Fold-expression based helper to print variadic arguments for dbg
template <typename T_arg, typename... Other_Args>
void _dbg_print_recursive(std::ostream &os, T_arg &&first, Other_Args &&...rest)
{
    os << std::forward<T_arg>(first);
    ((os << " " << std::forward<Other_Args>(rest)), ...);
}

// The main dbg function, which defines the DEBUG macro
template <typename... Args_dbg>
void dbg(const std::source_location loc, Args_dbg &&...args)
{
    std::cerr << RED << std::filesystem::path(loc.file_name()).filename().string()
              << ":" << loc.line()
              << " (" << loc.function_name() << ") "
              << BLUE << "DEBUG: " << RESET;
    if constexpr (sizeof...(args) > 0)
    {
        _dbg_print_recursive(std::cerr, std::forward<Args_dbg>(args)...);
    }
    std::cerr << RESET << std::endl;
}

#define DEBUG(...) dbg(std::source_location::current(), __VA_ARGS__)

#else // LOCAL for DEBUG and actual color definitions

// Ensure DEBUG is a no-op if LOCAL is not defined (colors remain empty strings from above)
#define DEBUG(...) ((void)0)

#endif // LOCAL for DEBUG and actual color definitions

#endif // DEBUG_UTILS_HPP