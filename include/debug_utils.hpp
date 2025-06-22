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
#include <chrono>          // For timestamps
#include <ctime>           // For std::strftime, std::localtime
#include <iomanip>         // For std::setprecision

// ══════════════════════ ENHANCED COLOR SYSTEM ══════════════════════
// Define colors as empty strings by default or if LOCAL is not defined.
// These will be overridden if LOCAL is defined with vibrant colors.

// Basic Colors
#ifndef RESET
#define RESET ""
#endif
#ifndef RED
#define RED ""
#endif
#ifndef GREEN
#define GREEN ""
#endif
#ifndef BLUE
#define BLUE ""
#endif
#ifndef YELLOW
#define YELLOW ""
#endif
#ifndef MAGENTA
#define MAGENTA ""
#endif
#ifndef CYAN
#define CYAN ""
#endif
#ifndef WHITE
#define WHITE ""
#endif
#ifndef BLACK
#define BLACK ""
#endif

// Bright/Bold Colors
#ifndef BRIGHT_RED
#define BRIGHT_RED ""
#endif
#ifndef BRIGHT_GREEN
#define BRIGHT_GREEN ""
#endif
#ifndef BRIGHT_BLUE
#define BRIGHT_BLUE ""
#endif
#ifndef BRIGHT_YELLOW
#define BRIGHT_YELLOW ""
#endif
#ifndef BRIGHT_MAGENTA
#define BRIGHT_MAGENTA ""
#endif
#ifndef BRIGHT_CYAN
#define BRIGHT_CYAN ""
#endif
#ifndef BRIGHT_WHITE
#define BRIGHT_WHITE ""
#endif

// Background Colors
#ifndef BG_RED
#define BG_RED ""
#endif
#ifndef BG_GREEN
#define BG_GREEN ""
#endif
#ifndef BG_BLUE
#define BG_BLUE ""
#endif
#ifndef BG_YELLOW
#define BG_YELLOW ""
#endif
#ifndef BG_MAGENTA
#define BG_MAGENTA ""
#endif
#ifndef BG_CYAN
#define BG_CYAN ""
#endif

// Text Styles
#ifndef BOLD
#define BOLD ""
#endif
#ifndef ITALIC
#define ITALIC ""
#endif
#ifndef UNDERLINE
#define UNDERLINE ""
#endif
#ifndef BLINK
#define BLINK ""
#endif

// ═══════════════════════ PRACTICE ASSERT/TRACE HOOKS ═══════════════════════
//  PRACTICE flag enables runtime asserts, tracing and brute solvers with enhanced visuals.

#ifdef PRACTICE
// Enhanced ASSERT with visual impact
#define ASSERT(cond, msg)                                                                       \
    if (!(cond))                                                                                \
    {                                                                                           \
        std::cerr << "\n" << BRIGHT_RED << BG_RED << "┌─────────────────────────────────────┐" << RESET << "\n"; \
        std::cerr << BRIGHT_RED << BG_RED << "│" << RESET << BRIGHT_WHITE << " 💥 ASSERTION FAILED! 💥" << RESET << BRIGHT_RED << BG_RED << "          │" << RESET << "\n"; \
        std::cerr << BRIGHT_RED << BG_RED << "└─────────────────────────────────────┘" << RESET << "\n"; \
        std::cerr << BRIGHT_RED << "🔍 Location: " << RESET << BRIGHT_CYAN                      \
                  << std::filesystem::path(std::source_location::current().file_name())         \
                         .filename()                                                            \
                         .string()                                                              \
                  << RESET << BRIGHT_YELLOW << ":" << std::source_location::current().line()    \
                  << RESET << "\n";                                                             \
        std::cerr << BRIGHT_RED << "🔧 Function: " << RESET << BRIGHT_MAGENTA                   \
                  << std::source_location::current().function_name() << RESET << "\n";         \
        std::cerr << BRIGHT_RED << "📝 Message: " << RESET << BRIGHT_WHITE << (msg) << RESET << "\n"; \
        std::cerr << BRIGHT_RED << "═══════════════════════════════════════════════════════════" << RESET << "\n"; \
        exit(42);                                                                               \
    }

// SUCCESS macro for positive feedback
#define SUCCESS(msg)                                                                            \
    do {                                                                                        \
        std::cerr << BRIGHT_GREEN << "✅ SUCCESS: " << RESET << GREEN << (msg) << RESET << "\n"; \
    } while(0)

// WARNING macro for non-fatal issues
#define WARNING(msg)                                                                            \
    do {                                                                                        \
        std::cerr << BRIGHT_YELLOW << "⚠️  WARNING: " << RESET << YELLOW << (msg) << RESET << "\n"; \
    } while(0)

// INFO macro for general information
#define INFO(msg)                                                                               \
    do {                                                                                        \
        std::cerr << BRIGHT_CYAN << "ℹ️  INFO: " << RESET << CYAN << (msg) << RESET << "\n";     \
    } while(0)

// TRACE: handy logging for PRACTICE builds, toggle with -DLOCAL
#ifdef LOCAL
// Forward declaration for dbg, which is defined further down within the #ifdef LOCAL block
template <typename... Args_dbg>
void dbg(const std::source_location loc, Args_dbg &&...args);

template <typename... Args_dbg>
void trace_colorful(const std::source_location loc, Args_dbg &&...args);

#define TRACE(...) trace_colorful(std::source_location::current(), __VA_ARGS__)
#else // LOCAL for TRACE
#define TRACE(...) ((void)0)
#endif // LOCAL for TRACE

#else // PRACTICE
#define ASSERT(cond, msg) ((void)0)
#define SUCCESS(msg) ((void)0)
#define WARNING(msg) ((void)0)
#define INFO(msg) ((void)0)
#define TRACE(...) ((void)0)
#endif // PRACTICE

// ═══════════════════════ ENHANCED DEBUGGING SYSTEM ═══════════════════════
//  Use DEBUG(a,b,v) to print state with file/line, colored, local only.

#ifdef LOCAL
// Override colors with vibrant escape codes if LOCAL is defined
#undef RESET
#undef RED
#undef GREEN
#undef BLUE
#undef YELLOW
#undef MAGENTA
#undef CYAN
#undef WHITE
#undef BLACK
#undef BRIGHT_RED
#undef BRIGHT_GREEN
#undef BRIGHT_BLUE
#undef BRIGHT_YELLOW
#undef BRIGHT_MAGENTA
#undef BRIGHT_CYAN
#undef BRIGHT_WHITE
#undef BG_RED
#undef BG_GREEN
#undef BG_BLUE
#undef BG_YELLOW
#undef BG_MAGENTA
#undef BG_CYAN
#undef BOLD
#undef ITALIC
#undef UNDERLINE
#undef BLINK

// Basic Colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BLACK "\033[30m"

// Bright/Bold Colors
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

// Background Colors
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"

// Text Styles
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"

// Enhanced helper for pairs with colors
template <typename A, typename B>
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &p)
{
    return os << BRIGHT_YELLOW << "(" << RESET << p.first << BRIGHT_YELLOW << ", " << RESET << p.second << BRIGHT_YELLOW << ")" << RESET;
}

// Enhanced helper for containers with beautiful formatting
template <typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value, typename T_container::value_type>::type>
std::ostream &operator<<(std::ostream &os, const T_container &v)
{
    os << BRIGHT_MAGENTA << "{" << RESET;
    std::string sep;
    for (const T &x : v) {
        os << sep << BRIGHT_CYAN << x << RESET;
        sep = BRIGHT_MAGENTA + std::string(", ") + RESET;
    }
    return os << BRIGHT_MAGENTA << "}" << RESET;
}

// Enhanced fold-expression helper with colors
template <typename T_arg, typename... Other_Args>
void _dbg_print_recursive(std::ostream &os, T_arg &&first, Other_Args &&...rest)
{
    os << BRIGHT_WHITE << std::forward<T_arg>(first) << RESET;
    if constexpr (sizeof...(rest) > 0) {
        os << BRIGHT_BLUE << " │ " << RESET;
        _dbg_print_recursive(os, std::forward<Other_Args>(rest)...);
    }
}

// Get current timestamp for debug output
inline std::string get_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", std::localtime(&time_t));
    return std::string(buffer) + "." + std::to_string(ms.count()).substr(0, 3);
}

// Enhanced DEBUG function with beautiful formatting
template <typename... Args_dbg>
void dbg(const std::source_location loc, Args_dbg &&...args)
{
    std::cerr << "\n" << BRIGHT_CYAN << "┌─" << RESET << BRIGHT_YELLOW << " 🐛 DEBUG " << RESET << BRIGHT_CYAN << "─" << RESET;
    std::cerr << BRIGHT_BLUE << " [" << get_timestamp() << "] " << RESET << BRIGHT_CYAN << "───────────────────────────────────────" << RESET << "\n";
    
    std::cerr << BRIGHT_CYAN << "│ " << RESET << BRIGHT_GREEN << "📁 File: " << RESET << BRIGHT_WHITE 
              << std::filesystem::path(loc.file_name()).filename().string() << RESET << "\n";
    std::cerr << BRIGHT_CYAN << "│ " << RESET << BRIGHT_GREEN << "📍 Line: " << RESET << BRIGHT_YELLOW 
              << loc.line() << RESET << "\n";
    std::cerr << BRIGHT_CYAN << "│ " << RESET << BRIGHT_GREEN << "🔧 Func: " << RESET << BRIGHT_MAGENTA 
              << loc.function_name() << RESET << "\n";
    std::cerr << BRIGHT_CYAN << "│ " << RESET << BRIGHT_GREEN << "📊 Data: " << RESET;
    
    if constexpr (sizeof...(args) > 0) {
        _dbg_print_recursive(std::cerr, std::forward<Args_dbg>(args)...);
    } else {
        std::cerr << BRIGHT_BLUE << "(no data)" << RESET;
    }
    
    std::cerr << "\n" << BRIGHT_CYAN << "└───────────────────────────────────────────────────────────────────────" << RESET << "\n";
}

// Enhanced TRACE function with different styling
template <typename... Args_dbg>
void trace_colorful(const std::source_location loc, Args_dbg &&...args)
{
    std::cerr << BRIGHT_MAGENTA << "🔍 TRACE " << RESET << BRIGHT_BLUE << "[" << get_timestamp() << "] " << RESET
              << BRIGHT_CYAN << std::filesystem::path(loc.file_name()).filename().string() 
              << RESET << BRIGHT_YELLOW << ":" << loc.line() << RESET << BRIGHT_BLUE << " ➤ " << RESET;
    
    if constexpr (sizeof...(args) > 0) {
        _dbg_print_recursive(std::cerr, std::forward<Args_dbg>(args)...);
    }
    std::cerr << "\n";
}

// Convenience macros for different types of debug output
#define DEBUG(...) dbg(std::source_location::current(), __VA_ARGS__)
#define DEBUG_VAR(var) DEBUG(#var, "=", var)
#define DEBUG_FUNC() DEBUG("🚀 Entering function:", __func__)
#define DEBUG_LINE() DEBUG("📍 Reached line:", __LINE__)

// Progress tracking macros
#define PROGRESS(current, total) \
    do { \
        float percent = (float)(current) / (total) * 100.0f; \
        std::cerr << BRIGHT_GREEN << "📈 Progress: " << RESET << BRIGHT_CYAN << (current) << RESET \
                  << BRIGHT_BLUE << "/" << RESET << BRIGHT_CYAN << (total) << RESET \
                  << BRIGHT_YELLOW << " (" << std::fixed << std::setprecision(1) << percent << "%)" << RESET << "\n"; \
    } while(0)

// Section separators for better organization
#define DEBUG_SECTION(title) \
    do { \
        std::cerr << "\n" << BRIGHT_YELLOW << "══════════════════════════════════════════════════════════════════════════════" << RESET << "\n"; \
        std::cerr << BRIGHT_YELLOW << "║ " << RESET << BRIGHT_WHITE << "🏷️  " << (title) << RESET << BRIGHT_YELLOW << std::string(70 - std::string(title).length(), ' ') << "║" << RESET << "\n"; \
        std::cerr << BRIGHT_YELLOW << "══════════════════════════════════════════════════════════════════════════════" << RESET << "\n"; \
    } while(0)

// Test result macros
#define TEST_PASS(name) \
    do { \
        std::cerr << BRIGHT_GREEN << "✅ PASS: " << RESET << GREEN << (name) << RESET << "\n"; \
    } while(0)

#define TEST_FAIL(name) \
    do { \
        std::cerr << BRIGHT_RED << "❌ FAIL: " << RESET << RED << (name) << RESET << "\n"; \
    } while(0)

// Performance timing macros
#define TIMER_START(name) \
    auto timer_##name##_start = std::chrono::high_resolution_clock::now();

#define TIMER_END(name) \
    do { \
        auto timer_##name##_end = std::chrono::high_resolution_clock::now(); \
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timer_##name##_end - timer_##name##_start); \
        std::cerr << BRIGHT_CYAN << "⏱️  Timer [" << RESET << BRIGHT_YELLOW << #name << RESET << BRIGHT_CYAN << "]: " << RESET \
                  << BRIGHT_WHITE << duration.count() << RESET << BRIGHT_BLUE << " μs" << RESET << "\n"; \
    } while(0)

#else // LOCAL for DEBUG and actual color definitions

// Ensure all macros are no-ops if LOCAL is not defined
#define DEBUG(...) ((void)0)
#define DEBUG_VAR(var) ((void)0)
#define DEBUG_FUNC() ((void)0)
#define DEBUG_LINE() ((void)0)
#define PROGRESS(current, total) ((void)0)
#define DEBUG_SECTION(title) ((void)0)
#define TEST_PASS(name) ((void)0)
#define TEST_FAIL(name) ((void)0)
#define TIMER_START(name) ((void)0)
#define TIMER_END(name) ((void)0)

#endif // LOCAL for DEBUG and actual color definitions

#endif // DEBUG_UTILS_HPP