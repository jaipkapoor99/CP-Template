# Universal C++23 Competitive Programming Template

A comprehensive, cross-platform competitive programming template with **enhanced colorful debug system**, C++23 compatibility, and modular design supporting Unix-like systems (Bash).

## 🌟 What's New

- **🎨 Enhanced Colorful Debug System**: Beautiful terminal output with vibrant colors, emojis, and professional formatting
- **⚡ C++23 Compatibility**: Smart header inclusion with fallbacks for older compilers
- **🎯 Visual Debugging**: Progress tracking, performance timing, and enhanced assertions
- **📊 Rich Data Visualization**: Beautiful formatting for containers, pairs, and complex data structures
- **🧪 Enhanced Testing**: Comprehensive debug features for algorithm development and verification

## 📁 Project Structure

```txt
CP-Template/
├── main.cpp                      # Main solution file with colorful debug integration
├── demo_colorful_debug.cpp       # Comprehensive demonstration of debug features
├── src/                          # Additional source files (if needed)
├── include/                      # Header files
│   ├── cp_utils.hpp             # Core utilities with C++23 compatibility
│   └── debug_utils.hpp          # Enhanced colorful debug system
├── scripts/                     # Automation scripts
│   ├── common/                  # Cross-platform wrapper scripts
│   │   ├── attach               # Cross-platform attach wrapper
│   │   ├── detach               # Cross-platform detach wrapper
│   │   ├── cleanup              # Cross-platform cleanup wrapper
│   │   └── test                 # Cross-platform test wrapper
│   └── unix/                    # Unix-specific scripts (Bash)
│   └── generate_input.py        # Test case generation
├── tests/                       # Test files
│   └── test_components.cpp      # Component testing with colorful debug examples
├── docs/                        # Documentation
│   └── readme.md                # Detailed documentation
├── COLORFUL_DEBUG_FEATURES.md   # Enhanced debug system documentation
└── .gitignore                   # Git ignore rules
```

## 🚀 Quick Start

### 1. **Development & Testing** (Enhanced Debug Mode)

```bash
# Full debug mode with colorful output and all features
g++ -std=c++23 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o solution

# Create input.txt and run with beautiful debug output
echo "5" > input.txt
./solution < input.txt
```

### 2. **Practice Mode** (Assertions Only)

```bash
# Practice mode with assertions but no visual debug output
g++ -std=c++23 -O2 -Wall -DPRACTICE main.cpp -o solution
./solution < input.txt
```

### 3. **Contest Mode** (Zero Overhead)

```bash
# Contest submission mode - all debug macros become no-ops
g++ -std=c++23 -O2 -Wall main.cpp -o solution
./solution < input.txt
```

### 4. **Try the Demo**

```bash
# Compile and run the comprehensive demo
g++ -std=c++23 -O2 -Wall -DPRACTICE -DLOCAL demo_colorful_debug.cpp -o demo
./demo
```

## 🎨 Enhanced Debug Features

### **Visual Debug Output**

- 🐛 **DEBUG()**: Beautiful boxed output with timestamps and location info
- ✅ **SUCCESS()**: Green success messages with checkmarks
- ⚠️ **WARNING()**: Yellow warning messages
- ℹ️ **INFO()**: Blue informational messages
- 💥 **Enhanced ASSERT()**: Dramatic visual failure display

### **Performance & Progress**

- ⏱️ **TIMER_START/END()**: Microsecond precision timing
- 📈 **PROGRESS()**: Visual progress bars with percentages
- 🔍 **TRACE()**: Lightweight logging for algorithm flow

### **Visual Organization**

- 🏷️ **DEBUG_SECTION()**: Beautiful section separators
- 📊 **Container visualization**: Colorful formatting for vectors, maps, pairs
- 🎯 **Test framework**: TEST_PASS/FAIL with visual feedback

### **Build Modes**

| Mode | Flags | Features |
| -------------- | -------------------- | ------------------------------------------- |
| **Full Debug** | `-DPRACTICE -DLOCAL` | All debug features, colorful output, timing |
| **Practice** | `-DPRACTICE` | Assertions and checks, no visual output |
| **Contest** | No flags | Zero overhead, all macros become no-ops |

## 🛠️ Key Features

- **🏗️ C++23 Compatible**: Smart header inclusion with automatic fallbacks
- **🎨 Enhanced Debug System**: Professional-grade colorful debugging experience
- **🔧 Modular Design**: Clean separation with easy attach/detach for submissions
- **🧪 Comprehensive Testing**: Advanced stress testing with visual feedback
- **🌐 Cross-Platform**: Works on Linux, macOS, and WSL
- **📊 Rich Data Structures**: DSU, Segment Tree, Fenwick Tree, and more
- **⚡ Performance Optimized**: Zero overhead in contest mode
- **🎯 Algorithm Library**: Graph algorithms, string processing, geometry, number theory

## 📖 Documentation

For detailed information and examples:

- **[Enhanced Debug Features](COLORFUL_DEBUG_FEATURES.md)** - Complete guide to the colorful debug system
- **[Complete Documentation](#technical-documentation---enhanced-cp-template)** - Comprehensive usage guide
- **[Demo Program](demo_colorful_debug.cpp)** - Live demonstration of all features
- **[Component Tests](tests/test_components.cpp)** - Usage examples for all utilities

## 🎯 Usage Patterns

### **Development Workflow**

1. Edit `main.cpp` for your solution (now in root directory)
2. Use `scripts/common/test` for stress testing (cross-platform)
3. Use `scripts/common/attach` before submission
4. Use `scripts/common/detach` to return to modular structure
5. Use `scripts/common/cleanup` to clean up generated files

### **CPH (Competitive Programming Helper) Setup**

1. Run `scripts/common/attach` to create single-file version (cross-platform)
2. Configure CPH to use the combined `main.cpp`
3. Use `scripts/common/detach` when returning to development

## 🌐 Platform-Specific Usage

The template automatically detects your platform and uses the appropriate scripts:

### **Cross-Platform Wrappers** (Recommended)

```bash
# These work on all platforms
./scripts/common/attach
./scripts/common/detach
./scripts/common/cleanup
./scripts/common/test
```

### **WSL (Windows Subsystem for Linux) Usage**

When using WSL, you should use the Unix-like scripts. Ensure you are in the project root directory within your WSL terminal.

```bash
# Inside WSL terminal
./scripts/unix/attach.sh
./scripts/unix/detach.sh
```

## 🧪 Advanced Testing Features

### **Stress Testing with Brute Force Comparison**

The template includes comprehensive stress testing capabilities:

```bash
# Run 100 stress tests (default)
scripts/common/test

# Run custom number of tests
scripts/common/test -n 50

# Disable brute force comparison (use internal asserts only)
scripts/common/test --no-brute -n 200

# Use Python script for test generation
scripts/common/test --python-gen

# Keep test files on failure for debugging
scripts/common/test --keep-files

# Enable verbose output
scripts/common/test -v
```

### **How Stress Testing Works**

1. **Compiles your main solution** (`main.cpp`)
2. **Auto-generates brute force template** (`tests/brute.cpp`) if it doesn't exist
3. **Compiles brute force solution** with the same problem logic but simpler approach
4. **Generates random test cases** using inline generator or Python script
5. **Runs both solutions** on the same input
6. **Compares outputs** and reports any mismatches
7. **Shows detailed failure information** including input and both outputs

### **Brute Force Template Auto-Generation**

When you run stress testing for the first time, the script automatically creates a `brute.cpp` template:

```cpp
#include "../include/cp_utils.hpp"

// TODO: Implement your brute force solution here
void solve_brute(int test_case_num)
{
    int n;
    read(n);

    // Example: Simple O(n) loop instead of O(1) formula
    ll result = 0;
    for (int i = 1; i <= n; i++) {
        result += i;
    }

    print(result);
}

int main() {
    FASTINOUT;
    int t;
    read(t);

    f(i, 0, t)
        solve_brute(i + 1);

    return 0;
}
```

### **Test Case Generation**

**Inline Generator (Default):**

- Generates random test cases directly in the script
- Easily customizable for different problem types
- No external dependencies

**Python Generator:**

- Use `--python-gen` flag to enable
- Auto-creates `generate_input.py` template if not found
- More flexible for complex input patterns

### **Platform-Specific Testing**

```bash
# Unix-like (Bash)
scripts/unix/test.sh -n 50 --no-brute

# Cross-platform (Recommended)
scripts/common/test -n 50 --no-brute
```

## 🔧 Customization

- **Test Generation**: Modify `scripts/generate_input.py` for your problem's input format
- **Brute Force**: Edit the auto-generated `tests/brute.cpp` with your simpler solution logic
- **Build Flags**: Adjust compilation flags in both PowerShell and Bash scripts as needed
- **Test Parameters**: Customize number of tests, timeouts, and generator settings

## 📚 What's Included

- **Data Structures**: DSU, Segment Tree, Fenwick Tree, etc.
- **Algorithms**: Graph algorithms, string processing, number theory
- **Geometry**: 2D point operations, convex hull, line intersections
- **Advanced**: Matrix exponentiation, NTT, Mo's algorithm, HLD
- **Debugging**: Colored output, assertions, tracing macros

---

## **Happy Competitive Programming!** 🏆

### **Enhanced Debug Integration**

The template now includes a professional-grade debug system:

```cpp
void solve() {
    DEBUG_SECTION("🎯 SOLVING PROBLEM");
    DEBUG_FUNC();

    int n;
    read(n);
    DEBUG_VAR(n);

    if (n > 1000) {
        WARNING("Large input detected");
    }

    TIMER_START(algorithm);
    vector<int> result = calculate_answer(n);
    TIMER_END(algorithm);

    DEBUG("Computed result:", result);
    SUCCESS("Solution completed!");
}
```

### **CodeRunner Configuration (Enhanced)**

```json
{
  "code-runner.executorMap": {
    "cpp": "g++ -std=c++23 -Wall -O2 -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt.exe; if ($?) { Get-Content input.txt | ./$fileNameWithoutExt.exe > output.txt }"
  }
}
```

**Enhanced Features:**

- Beautiful colored debug output in terminal
- Professional formatting with timestamps and location info
- Visual progress tracking and performance timing
- Zero impact on contest submissions

---

## Technical Documentation - Enhanced CP Template

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
- **C++23 Compatibility**: Smart header inclusion with fallbacks
- **Comprehensive Utilities**: Data structures, algorithms, and helper functions
- **Zero-Overhead Design**: Debug features compile to no-ops in contest mode
- **Cross-Platform Support**: Works on Windows, Linux, and macOS

## Architecture

### File Structure

```txt
CP-Template/
├── include/                     # Core header files
│   ├── cp_utils.hpp            # Main utilities with C++23 compatibility
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
3. **Type Safety**: Extensive use of templates and C++23 concepts
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
g++ -std=c++23 -O2 -Wall -DPRACTICE -DLOCAL your_file.cpp -o solution

# Practice Mode - Clean testing with assertions
g++ -std=c++23 -O2 -Wall -DPRACTICE your_file.cpp -o solution

# Contest Mode - Zero overhead for submission
g++ -std=c++23 -O2 -Wall your_file.cpp -o solution
```

### Compiler Requirements

- **Minimum**: GCC 10+, Clang 12+, MSVC 19.29+
- **Recommended**: GCC 11+, Clang 13+
- **C++ Standard**: C++23 (with C++17 fallbacks)
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
  "C_Cpp.default.cppStandard": "c++23",
  "C_Cpp.default.defines": ["PRACTICE", "LOCAL"],
  "code-runner.executorMap": {
    "cpp": "g++ -std=c++23 -Wall -O2 -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt && ./$fileNameWithoutExt < input.txt"
  }
}
```

### Clang Format

The template includes a `.clang-format` file with optimized settings for competitive programming.

### WSL Configuration

When working within Windows Subsystem for Linux (WSL), you can use the template as if you were on a native Linux environment. The `scripts/unix/` directory contains Bash scripts that are compatible with WSL.

**Key Considerations:**

- **File Paths**: Ensure you are operating within the `/mnt/c/...` path if your project is on the Windows filesystem, or directly within the Linux filesystem if the project is cloned there.
- **Compiler**: Install a C++ compiler (e.g., `g++`) within your WSL distribution.
- **Script Execution**: Use the provided `scripts/common/` wrappers or directly call the `scripts/unix/` scripts.

**Example Usage in WSL:**

```bash
# Navigate to your project directory in WSL
cd /home/your_user/CP-Template

# Use the cross-platform attach script
./scripts/common/attach

# Or directly use the Unix-specific attach script
./scripts/unix/attach.sh

# Compile your solution
g++ -std=c++23 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o solution

# Run tests
./scripts/common/test
```

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
   - Ensure C++23 support: Use GCC 10+ or Clang 12+
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