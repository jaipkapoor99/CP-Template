# Technical Documentation - Enhanced CP Template

## Table of Contents

1. [Overview](#overview)
2. [Architecture](#architecture)
3. [Build System](#build-system)
4. [Debug System](#debug-system)
5. [Data Structures](#data-structures)
6. [Algorithms](#algorithms)
7. [Configuration](#configuration)
8. [Development Workflow](#development-workflow)
9. [API Reference](#api-reference)
10. [Troubleshooting](#troubleshooting)

## Overview

This is a professional-grade competitive programming template featuring:

- **Enhanced Debug System**: Beautiful colorful output with professional formatting
- **C++20 Compatibility**: Smart header inclusion with fallbacks
- **Comprehensive Utilities**: Data structures, algorithms, and helper functions
- **Zero-Overhead Design**: Debug features compile to no-ops in contest mode
- **Cross-Platform Support**: Works on Windows, Linux, and macOS

## Architecture

### File Structure

```
CP-Template/
├── include/                     # Core header files
│   ├── cp_utils.hpp            # Main utilities with C++20 compatibility
│   └── debug_utils.hpp         # Enhanced debug system
├── tests/                      # Test files and examples
│   └── test_components.cpp     # Component testing with debug examples
├── scripts/                    # Cross-platform automation scripts
├── docs/                       # Technical documentation
├── src/                        # Additional source files (optional)
├── *.md                        # Documentation files
└── Configuration files         # .clang-format, .gitignore, etc.
```

### Design Principles

1. **Modular Architecture**: Clean separation between utilities and debug system
2. **Conditional Compilation**: Zero overhead in production builds
3. **Type Safety**: Extensive use of templates and C++20 concepts
4. **Performance First**: Optimized algorithms and data structures
5. **Developer Experience**: Beautiful visual feedback during development

## Build System

### Compilation Modes

| Mode | Flags | Purpose | Features |
|------|-------|---------|----------|
| **Development** | `-DPRACTICE -DLOCAL` | Full debugging | All visual features, timing, progress |
| **Practice** | `-DPRACTICE` | Clean testing | Assertions only, no visual output |
| **Contest** | None | Submission | Zero overhead, maximum performance |

### Compilation Commands

```bash
# Development Mode - Full debug experience
g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL your_file.cpp -o solution

# Practice Mode - Clean testing with assertions
g++ -std=c++20 -O2 -Wall -DPRACTICE your_file.cpp -o solution

# Contest Mode - Zero overhead for submission
g++ -std=c++20 -O2 -Wall your_file.cpp -o solution
```

### Compiler Requirements

- **Minimum**: GCC 10+, Clang 12+, MSVC 19.29+
- **Recommended**: GCC 11+, Clang 13+
- **C++ Standard**: C++20 (with C++17 fallbacks)
- **Optional**: GNU PBDS support for advanced data structures

## Debug System

### Core Components

#### Visual Debug Output
```cpp
DEBUG("Processing:", data);              // Beautiful boxed output
DEBUG_VAR(variable);                     // Variable inspection
TRACE("Algorithm step completed");       // Lightweight logging
```

#### Message Types
```cpp
SUCCESS("Operation completed!");         // ✅ Success messages
WARNING("Performance warning");          // ⚠️  Warnings
INFO("Processing information");          // ℹ️  Information
ASSERT(condition, "Error details");      // 💥 Enhanced assertions
```

#### Organization Tools
```cpp
DEBUG_SECTION("🎯 ALGORITHM PHASE");    // Section headers
DEBUG_FUNC();                           // Function entry logging
```

#### Performance Analysis
```cpp
TIMER_START(operation_name);            // Start timing
// ... code to measure ...
TIMER_END(operation_name);              // End timing (shows μs)

PROGRESS(current, total);               // Progress tracking
```

### Color System

The debug system uses a comprehensive color palette:

- **Primary Colors**: RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE
- **Enhanced Variants**: BRIGHT_* versions for emphasis
- **Background Colors**: For critical alerts and sections
- **Text Styles**: BOLD, ITALIC, UNDERLINE, BLINK

### Conditional Compilation

```cpp
#ifdef LOCAL
    // Rich debug code only in development
    DEBUG("Expensive computation:", complex_analysis());
#endif

#ifdef PRACTICE
    // Assertions and verification
    ASSERT(invariant_check(), "Invariant violated");
#endif

// Contest mode: All macros become ((void)0)
```

## Data Structures

### Disjoint Set Union (DSU)
```cpp
DSU dsu(n);                             // Create DSU with n elements
dsu.unite(u, v);                        // Union sets containing u and v
bool connected = dsu.connected(u, v);   // Check connectivity
int size = dsu.size(u);                 // Get set size
int sets = dsu.num_sets();              // Get number of sets
```

### Segment Tree with Lazy Propagation
```cpp
SegTreeLazy<ll, ll> seg(arr);           // Build from array
seg.update(l, r, val);                  // Range update
ll result = seg.query(l, r);            // Range query
```

### Fenwick Tree (Binary Indexed Tree)
```cpp
FenwickTree<ll> bit(n);                 // Create BIT of size n
bit.update(idx, delta);                 // Point update
ll sum = bit.query(idx);                // Prefix sum
ll range_sum = bit.query_range(l, r);   // Range sum
```

### Policy-Based Data Structures (GNU PBDS)
```cpp
os<int> ordered_set;                    // Order statistic tree
ordered_set.insert(x);                 // Insert element
int kth = *ordered_set.find_by_order(k); // k-th smallest
int rank = ordered_set.order_of_key(x); // Number of elements < x
```

## Algorithms

### Graph Algorithms

#### Dijkstra's Algorithm
```cpp
vector<ll> dist = dijkstra(start, n, adj);
// Returns shortest distances from start to all nodes
```

#### 0-1 BFS
```cpp
vector<ll> dist = bfs01(start, n, adj);
// For graphs with edge weights 0 or 1
```

#### Lowest Common Ancestor (LCA)
```cpp
LCA lca(n);
lca.add_edge(u, v);                     // Add tree edge
lca.build(root);                        // Build LCA structure
int ancestor = lca.get_lca(u, v);       // Get LCA
int distance = lca.get_dist(u, v);      // Get distance
```

### String Algorithms

#### KMP String Matching
```cpp
vi lps = compute_lps_array(pattern);
vi matches = kmp_search(text, pattern);
```

#### Polynomial String Hashing
```cpp
StringHashing hasher(text);
pll hash_val = hasher.get_hash(l, r);   // Hash of substring [l, r]
```

#### Suffix Array
```cpp
vi sa = build_suffix_array(text);
vi lcp = build_lcp_array(text, sa);
```

### Number Theory

#### Primality Testing
```cpp
bool is_prime = isPrime(n);             // Miller-Rabin test
```

#### Sieve of Eratosthenes
```cpp
Sieve sieve(max_val);
bool prime = sieve.is_prime[n];
vi primes = sieve.primes;
vpll factors = sieve.get_prime_factorization(n);
```

#### Modular Arithmetic
```cpp
using Mint = ModularOps<MOD_CONST>;
ll result = Mint::add(a, b);
ll power = Mint::power(base, exp);
ll inverse = Mint::inv(x);
```

### Advanced Data Structures

#### Convex Hull Trick
```cpp
ConvexHullTrickMinMono cht;
cht.add_line(m, c);                     // Add line y = mx + c
ll min_val = cht.query(x);              // Query minimum at x
```

#### Mo's Algorithm
```cpp
vector<ResultType> answers = mos_algorithm(
    arr, queries, add_fn, remove_fn, get_ans_fn
);
```

#### Heavy-Light Decomposition
```cpp
HLD hld(n);
hld.add_edge(u, v);
hld.build(root);
hld.process_path(u, v, [&](int l, int r) {
    // Process path segment [l, r]
});
```

## Configuration

### VS Code Setup

**settings.json** (Global):
```json
{
  "C_Cpp.default.compilerPath": "path/to/g++",
  "C_Cpp.default.cppStandard": "c++20",
  "C_Cpp.default.defines": ["PRACTICE", "LOCAL"],
  "code-runner.executorMap": {
    "cpp": "g++ -std=c++20 -Wall -O2 -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt && ./$fileNameWithoutExt < input.txt"
  }
}
```

### Clang Format

The template includes a `.clang-format` file with optimized settings for competitive programming.

## Development Workflow

### 1. Problem Setup
```cpp
#include "include/cp_utils.hpp"

void solve(int test_case) {
    DEBUG_SECTION("🎯 PROBLEM #" + to_string(test_case));
    DEBUG_FUNC();
    
    // Read input with debug output
    int n;
    read(n);
    DEBUG_VAR(n);
    
    // Your algorithm here
}
```

### 2. Algorithm Development
- Use `DEBUG()` for step-by-step algorithm tracing
- Use `TIMER_START/END()` for performance analysis
- Use `PROGRESS()` for long-running operations
- Use `ASSERT()` for correctness checking

### 3. Testing
- Compile with `-DPRACTICE -DLOCAL` for full debugging
- Use stress testing scripts in `scripts/` directory
- Verify with practice mode (`-DPRACTICE` only)

### 4. Submission
- Compile with no debug flags for zero overhead
- Use attach scripts if single-file submission required

## API Reference

### Core Macros

| Macro | Purpose | Example |
|-------|---------|---------|
| `DEBUG(...)` | Visual debug output | `DEBUG("Value:", x)` |
| `DEBUG_VAR(x)` | Variable inspection | `DEBUG_VAR(array)` |
| `TRACE(...)` | Lightweight logging | `TRACE("Step completed")` |
| `SUCCESS(msg)` | Success message | `SUCCESS("Done!")` |
| `WARNING(msg)` | Warning message | `WARNING("Large input")` |
| `INFO(msg)` | Information message | `INFO("Processing...")` |
| `ASSERT(cond, msg)` | Enhanced assertion | `ASSERT(x > 0, "Invalid")` |
| `DEBUG_SECTION(title)` | Section header | `DEBUG_SECTION("🎯 PHASE 1")` |
| `DEBUG_FUNC()` | Function entry | `DEBUG_FUNC()` |
| `TIMER_START(name)` | Start timer | `TIMER_START(algorithm)` |
| `TIMER_END(name)` | End timer | `TIMER_END(algorithm)` |
| `PROGRESS(cur, total)` | Progress tracking | `PROGRESS(i, n)` |
| `TEST_PASS(name)` | Test success | `TEST_PASS("Test 1")` |
| `TEST_FAIL(name)` | Test failure | `TEST_FAIL("Test 2")` |

### Utility Functions

| Function | Purpose | Example |
|----------|---------|---------|
| `read(...)` | Variadic input | `read(n, k, arr)` |
| `print(...)` | Variadic output | `print(result, answer)` |
| `maximise(target, vals...)` | Update maximum | `maximise(max_val, a, b, c)` |
| `minimise(target, vals...)` | Update minimum | `minimise(min_val, x, y)` |

### Type Aliases

| Alias | Type | Purpose |
|-------|------|---------|
| `ll` | `long long` | Large integers |
| `pii` | `pair<int, int>` | Integer pairs |
| `pll` | `pair<ll, ll>` | Long long pairs |
| `vi` | `vector<int>` | Integer vectors |
| `vll` | `vector<ll>` | Long long vectors |
| `vpii` | `vector<pii>` | Vector of integer pairs |
| `os<T>` | Order statistic tree | PBDS ordered set |

## Troubleshooting

### Common Issues

1. **Compilation Errors**
   - Ensure C++20 support: Use GCC 10+ or Clang 12+
   - Missing headers: Check if `bits/stdc++.h` is available
   - PBDS errors: Verify GNU compiler with PBDS support

2. **Debug Output Not Showing**
   - Ensure `-DLOCAL` flag is used for visual output
   - Check if `-DPRACTICE` is used for assertions
   - Verify terminal supports Unicode and colors

3. **Performance Issues**
   - Remove debug flags for contest submission
   - Use practice mode for clean performance testing
   - Profile with timing macros to identify bottlenecks

4. **Template Integration**
   - Include `cp_utils.hpp` which automatically includes debug system
   - Use attach/detach scripts for single-file requirements
   - Ensure proper file structure and paths

### Debug System Troubleshooting

1. **Colors Not Displaying**
   - Terminal may not support ANSI colors
   - Try different terminal emulator
   - Colors automatically disabled in non-LOCAL builds

2. **Unicode Characters Issues**
   - Set terminal font to support Unicode
   - Use Cascadia Code or similar programming fonts
   - Ensure UTF-8 encoding in terminal

3. **Performance Impact**
   - Debug features only active with proper flags
   - Zero overhead in contest mode (no flags)
   - Use practice mode for clean performance testing

---

**For more information, see:**
- [Main README](../readme.md) - Project overview
- [Debug Features Guide](../COLORFUL_DEBUG_FEATURES.md) - Complete debug system documentation
- [Quick Reference](../QUICK_REFERENCE.md) - Quick start guide
- [Changelog](../CHANGELOG.md) - Version history and updates 