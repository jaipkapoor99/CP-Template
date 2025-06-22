# Universal C++20 Competitive Programming Template

This template provides a **professional-grade competitive programming environment** with an **enhanced colorful debug system**, **C++20 compatibility**, and **comprehensive utilities**. It features modular design with core logic in `main.cpp`, enhanced utilities in `cp_utils.hpp`, and a revolutionary debug system in `debug_utils.hpp`.

## 🌟 What's New in This Enhanced Version

- **🎨 Revolutionary Debug System**: Professional-grade colorful debugging with emojis, timing, and beautiful formatting
- **⚡ C++20 Compatibility**: Smart header inclusion with automatic fallbacks for maximum compatibility
- **🎯 Visual Development Experience**: Progress tracking, performance insights, and visual feedback
- **📊 Enhanced Data Visualization**: Beautiful formatting for all container types and complex structures
- **🚀 Zero-Overhead Design**: All debug features compile to no-ops in contest mode

## Project Structure

- **`main.cpp`**: Your primary solution file with enhanced debug integration. This is where you implement `solve()` functions with beautiful visual feedback.
- **`demo_colorful_debug.cpp`**: Comprehensive demonstration showcasing all debug system features with real examples.
- **`cp_utils.hpp`**: Enhanced utilities with C++20 compatibility, smart header inclusion, and integration with the debug system.
- **`debug_utils.hpp`**: Complete colorful debug system with professional formatting, timing, progress tracking, and visual organization.
- **`test.ps1`**: PowerShell script for comprehensive stress testing with visual feedback.
- **`attach.sh`/`detach.sh`**: Scripts for bundling/unbundling files for contest submission compatibility.
- **`generate_input.py`**: Python script for advanced test case generation.
- **`COLORFUL_DEBUG_FEATURES.md`**: Comprehensive guide to the enhanced debug system.

## Enhanced Features

### **🎨 Professional Debug System**

- **Visual Excellence**: Beautiful boxed output with Unicode characters, emojis, and professional formatting
- **Performance Insights**: Microsecond-precision timing with named timers for algorithm analysis
- **Progress Visualization**: Real-time progress bars for long-running operations
- **Enhanced Assertions**: Dramatic visual failure displays with detailed location information
- **Conditional Compilation**: Zero overhead in contest mode, full features in development

### **⚡ C++20 Compatibility & Smart Headers**

- **Intelligent Inclusion**: Prefers `bits/stdc++.h` when available, falls back to individual headers
- **C++20 Features**: Automatic inclusion of `<ranges>`, `<concepts>`, `<format>`, `<numbers>`, etc.
- **GNU PBDS Support**: Conditional inclusion of Policy-Based Data Structures
- **Compiler Warnings**: Helpful warnings for older compiler versions

### **🎯 Build Modes with Enhanced Functionality**

- **Full Debug Mode** (`-DPRACTICE -DLOCAL`): Complete visual debugging experience with all features
- **Practice Mode** (`-DPRACTICE`): Assertions and verification enabled, no visual output
- **Contest Mode** (no flags): Zero overhead, all debug macros become no-ops

### **📊 Rich Data Structures & Algorithms**

All existing data structures enhanced with debug integration and C++20 compatibility:

- **Enhanced DSU**: With visual debugging and comprehensive bounds checking
- **Segment Tree with Lazy Propagation**: Debug-friendly with operation tracing
- **Graph Algorithms**: Dijkstra, BFS, LCA with visual progress tracking
- **String Algorithms**: KMP, Hashing, Suffix Arrays with debug insights
- **Advanced Structures**: Convex Hull Trick, Mo's Algorithm, NTT, HLD

## How to Use

### **🎨 Enhanced Development Experience**

1. **Setup**: Ensure all files are in your project directory with proper structure.

2. **Development Mode** (Full Debug Features):

   ```bash
   g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o solution
   ./solution < input.txt
   ```

   **Experience:**

   - Beautiful colorful output with emojis and professional formatting
   - Real-time progress tracking and performance timing
   - Enhanced assertions with dramatic visual failure displays
   - Comprehensive data structure visualization

3. **Practice Mode** (Clean Testing):

   ```bash
   g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o solution
   ./solution < input.txt
   ```

   **Experience:**

   - Assertions and verification active for correctness checking
   - Clean output without visual debug information
   - Minimal overhead for performance testing

4. **Contest Mode** (Submission Ready):

   ```bash
   g++ -std=c++20 -O2 -Wall main.cpp -o solution
   ./solution < input.txt
   ```

   **Experience:**

   - Zero overhead - all debug macros become no-ops
   - Maximum performance for contest submission
   - Clean, optimized code execution

### **🚀 Try the Enhanced Demo**

Experience the full power of the debug system:

```bash
g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL demo_colorful_debug.cpp -o demo
./demo
```

This comprehensive demo showcases:

- All debug message types with beautiful formatting
- Performance timing and progress tracking
- Data structure visualization
- Algorithm tracing with step-by-step insights
- Test framework integration with visual feedback

### **🔧 Enhanced Usage Patterns**

#### **Modern Problem Solving Workflow**

```cpp
#include "cp_utils.hpp"

void solve(int test_case_num) {
    DEBUG_SECTION("🎯 SOLVING PROBLEM #" + to_string(test_case_num));
    DEBUG_FUNC();

    int n;
    read(n);
    DEBUG_VAR(n);

    if (n > 10000) {
        WARNING("Large input detected - optimized algorithm recommended");
    }

    vector<int> arr(n);
    read(arr);
    DEBUG("Input array:", arr);

    TIMER_START(main_algorithm);

    // Your algorithm implementation here
    vector<int> result = solve_problem(arr);

    TIMER_END(main_algorithm);

    DEBUG("Result:", result);
    print(result);
    SUCCESS("Problem solved successfully!");
}

int main() {
    FASTINOUT;
    int t;
    read(t);

    DEBUG_SECTION("🏁 STARTING PROBLEM SOLVING SESSION");
    INFO("Processing " + to_string(t) + " test cases");

    f(i, 0, t) {
        PROGRESS(i + 1, t);
        solve(i + 1);
    }

    SUCCESS("🎉 All test cases completed!");
    return 0;
}
```

#### **Algorithm Development with Visual Debugging**

```cpp
void enhanced_bubble_sort(vector<int>& arr) {
    DEBUG_SECTION("🔄 ENHANCED BUBBLE SORT ALGORITHM");
    DEBUG_FUNC();

    int n = arr.size();
    DEBUG("Starting sort with array size:", n);
    DEBUG("Initial array:", arr);

    TIMER_START(bubble_sort_total);

    for (int i = 0; i < n - 1; i++) {
        TRACE("Starting pass", i + 1, "of", n - 1);
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                DEBUG("Swapped positions", j, "and", j + 1, ":", arr);
            }
        }

        PROGRESS(i + 1, n - 1);

        if (!swapped) {
            INFO("Array is sorted - early termination at pass " + to_string(i + 1));
            break;
        }
    }

    TIMER_END(bubble_sort_total);
    DEBUG("Final sorted array:", arr);
    SUCCESS("Bubble sort completed!");
}
```

#### **Comprehensive Testing Framework**

```cpp
void run_comprehensive_tests() {
    DEBUG_SECTION("🧪 COMPREHENSIVE ALGORITHM TESTING");

    struct TestCase {
        string name;
        vector<int> input;
        vector<int> expected;
    };

    vector<TestCase> tests = {
        {"Small Array", {3, 1, 4, 1, 5}, {1, 1, 3, 4, 5}},
        {"Already Sorted", {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}},
        {"Reverse Order", {5, 4, 3, 2, 1}, {1, 2, 3, 4, 5}},
        {"Single Element", {42}, {42}},
        {"Duplicates", {3, 3, 3, 3}, {3, 3, 3, 3}}
    };

    int passed = 0;
    int total = tests.size();

    for (int i = 0; i < total; i++) {
        TIMER_START(test_execution);

        vector<int> result = tests[i].input;
        enhanced_bubble_sort(result);

        bool success = (result == tests[i].expected);

        TIMER_END(test_execution);

        if (success) {
            TEST_PASS(tests[i].name);
            passed++;
        } else {
            TEST_FAIL(tests[i].name);
            DEBUG("Expected:", tests[i].expected);
            DEBUG("Got:", result);
        }

        PROGRESS(i + 1, total);
    }

    DEBUG_SECTION("📊 TEST RESULTS SUMMARY");
    INFO("Tests passed: " + to_string(passed) + "/" + to_string(total));

    if (passed == total) {
        SUCCESS("🎉 All tests passed! Algorithm is working correctly!");
    } else {
        WARNING("⚠️ Some tests failed - please review the algorithm");
    }
}
```

// ... existing detailed documentation continues with enhanced examples ...

### **🎨 Enhanced VS Code Configuration**

For the best development experience with the enhanced debug system:

**Global `settings.json` Configuration:**

```json
{
  "C_Cpp.default.compilerPath": "C:/mingw64/bin/g++.exe",
  "C_Cpp.default.cppStandard": "c++20",
  "C_Cpp.default.cStandard": "c17",
  "C_Cpp.default.intelliSenseMode": "windows-gcc-x64",
  "C_Cpp.default.defines": [
    "_DEBUG",
    "UNICODE",
    "_UNICODE",
    "PRACTICE",
    "LOCAL"
  ],

  "code-runner.executorMap": {
    "cpp": "g++ -std=c++20 -Wall -O2 -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt.exe; if ($?) { Get-Content input.txt | ./$fileNameWithoutExt.exe > output.txt }"
  },

  "terminal.integrated.fontFamily": "Cascadia Code, Consolas, monospace",
  "terminal.integrated.fontSize": 14,
  "workbench.colorTheme": "Dark+ (default dark)",
  "editor.fontFamily": "Cascadia Code, Consolas, monospace"
}
```

**Enhanced Features with This Configuration:**

- Full C++20 IntelliSense support
- Automatic debug mode compilation
- Beautiful colorful output in integrated terminal
- Optimal font rendering for Unicode characters and emojis
- Input/output redirection for testing

## Enhanced Data Structure Examples

### **DSU with Visual Debugging**

```cpp
void demonstrate_enhanced_dsu() {
    DEBUG_SECTION("🔗 ENHANCED DISJOINT SET UNION");
    DEBUG_FUNC();

    int n = 6;
    DSU dsu(n);

    DEBUG("Initial DSU with", n, "elements");
    DEBUG_VAR(dsu.num_sets());

    // Perform unions with visual feedback
    vector<pair<int, int>> unions = {{0, 1}, {2, 3}, {0, 4}, {1, 5}};

    for (auto [u, v] : unions) {
        TIMER_START(union_operation);
        bool connected = dsu.unite(u, v);
        TIMER_END(union_operation);

        if (connected) {
            SUCCESS("Connected " + to_string(u) + " and " + to_string(v));
            DEBUG("Set size containing", u, ":", dsu.size(u));
            DEBUG("Total sets remaining:", dsu.num_sets());
        } else {
            INFO("Elements " + to_string(u) + " and " + to_string(v) + " already connected");
        }
    }

    // Test connectivity with visual output
    DEBUG_SECTION("🔍 CONNECTIVITY TESTING");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            bool connected = dsu.connected(i, j);
            if (connected) {
                DEBUG("✅", i, "and", j, "are connected");
            } else {
                DEBUG("❌", i, "and", j, "are not connected");
            }
        }
    }

    SUCCESS("DSU demonstration completed!");
}
```

### **Segment Tree with Enhanced Debugging**

```cpp
void demonstrate_enhanced_segment_tree() {
    DEBUG_SECTION("🌳 ENHANCED SEGMENT TREE WITH LAZY PROPAGATION");
    DEBUG_FUNC();

    vector<ll> initial_array = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = initial_array.size();

    DEBUG("Building segment tree with initial array:", initial_array);

    TIMER_START(segtree_construction);
    SegTreeLazy<ll, ll> seg_tree(initial_array);
    TIMER_END(segtree_construction);

    SUCCESS("Segment tree constructed successfully!");

    // Range updates with visual feedback
    DEBUG_SECTION("📊 RANGE UPDATES");

    vector<tuple<int, int, ll>> updates = {
        {0, 2, 5},    // Add 5 to range [0, 2]
        {3, 5, -2},   // Add -2 to range [3, 5]
        {1, 6, 3}     // Add 3 to range [1, 6]
    };

    for (auto [l, r, val] : updates) {
        TIMER_START(range_update);
        seg_tree.update(l, r, val);
        TIMER_END(range_update);

        SUCCESS("Updated range [" + to_string(l) + ", " + to_string(r) + "] by " + to_string(val));

        // Query the updated range
        ll result = seg_tree.query(l, r);
        DEBUG("Sum of range [" + to_string(l) + ", " + to_string(r) + "] =", result);
    }

    // Range queries with performance tracking
    DEBUG_SECTION("🔍 RANGE QUERIES");

    vector<pair<int, int>> queries = {{0, 3}, {2, 5}, {1, 7}, {0, 7}};

    for (auto [l, r] : queries) {
        TIMER_START(range_query);
        ll result = seg_tree.query(l, r);
        TIMER_END(range_query);

        DEBUG("Query range [" + to_string(l) + ", " + to_string(r) + "] =", result);
    }

    SUCCESS("Segment tree demonstration completed!");
}
```

## Performance Analysis with Enhanced Metrics

The enhanced debug system provides detailed performance insights:

### **Timing Analysis**

```cpp
void performance_analysis_example() {
    DEBUG_SECTION("⚡ PERFORMANCE ANALYSIS");

    vector<int> sizes = {1000, 5000, 10000, 50000};

    for (int n : sizes) {
        vector<int> arr(n);
        // Fill with random data
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 1000;
        }

        INFO("Testing with array size: " + to_string(n));

        // Test different algorithms
        TIMER_START(bubble_sort);
        auto arr_copy1 = arr;
        bubble_sort(arr_copy1);
        TIMER_END(bubble_sort);

        TIMER_START(std_sort);
        auto arr_copy2 = arr;
        sort(arr_copy2.begin(), arr_copy2.end());
        TIMER_END(std_sort);

        // Verify results match
        ASSERT(arr_copy1 == arr_copy2, "Sorting algorithms produce different results!");
        SUCCESS("Both algorithms produced identical results");
    }
}
```

## Advanced Customization

### **Custom Debug Macros**

You can extend the debug system with custom macros:

```cpp
// Custom algorithm-specific debug macro
#ifdef LOCAL
#define GRAPH_DEBUG(msg, graph) \
    do { \
        DEBUG_SECTION("🔗 GRAPH ANALYSIS"); \
        DEBUG(msg); \
        for (int i = 0; i < graph.size(); i++) { \
            DEBUG("Node", i, "connections:", graph[i]); \
        } \
    } while(0)
#else
#define GRAPH_DEBUG(msg, graph) ((void)0)
#endif

// Usage in algorithms
void dijkstra_with_debug(vector<vector<pii>>& graph, int start) {
    GRAPH_DEBUG("Starting Dijkstra from node " + to_string(start), graph);
    // ... algorithm implementation with debug output ...
}
```

### **Color Customization**

Modify colors in `debug_utils.hpp` for personal preference:

```cpp
// Example: Custom color scheme
#ifdef LOCAL
#undef BRIGHT_BLUE
#define BRIGHT_BLUE "\033[94m"  // Custom blue shade
// ... other color modifications ...
#endif
```

## Conclusion

This enhanced competitive programming template transforms the development experience from basic text output to a **professional, visual, and efficient debugging environment**.

**Key Benefits:**

- 🎨 **Beautiful Visual Experience**: Makes debugging enjoyable and efficient
- 🚀 **Zero Contest Overhead**: No performance impact when it matters
- 🎯 **Professional Development**: Enterprise-grade debugging tools
- 📊 **Educational Value**: Learn algorithms through visual feedback
- 🔧 **Highly Customizable**: Adapt to your specific needs and preferences

**Perfect For:**

- 🏆 Competitive programming contests and practice
- 📚 Algorithm learning and computer science education
- 🧪 Code testing, verification, and development
- 🎯 Professional software development practices

The system seamlessly scales from zero overhead in contest submissions to rich, beautiful debugging during development and learning. Experience the future of competitive programming with this enhanced template!

---

**Start your enhanced competitive programming journey today!** 🚀

Try `demo_colorful_debug.cpp` to experience all features, then integrate the system into your problem-solving workflow for maximum productivity and enjoyment! 🎉
