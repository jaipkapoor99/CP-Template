# Universal C++20 Competitive Programming Template

A comprehensive, cross-platform competitive programming template with **enhanced colorful debug system**, C++20 compatibility, and modular design supporting both Windows (PowerShell) and Unix-like systems (Bash).

## 🌟 What's New

- **🎨 Enhanced Colorful Debug System**: Beautiful terminal output with vibrant colors, emojis, and professional formatting
- **⚡ C++20 Compatibility**: Smart header inclusion with fallbacks for older compilers
- **🎯 Visual Debugging**: Progress tracking, performance timing, and enhanced assertions
- **📊 Rich Data Visualization**: Beautiful formatting for containers, pairs, and complex data structures
- **🧪 Enhanced Testing**: Comprehensive debug features for algorithm development and verification

## 📁 Project Structure

```
CP-Template/
├── main.cpp                      # Main solution file with colorful debug integration
├── demo_colorful_debug.cpp       # Comprehensive demonstration of debug features
├── src/                          # Additional source files (if needed)
├── include/                      # Header files
│   ├── cp_utils.hpp             # Core utilities with C++20 compatibility
│   └── debug_utils.hpp          # Enhanced colorful debug system
├── scripts/                     # Automation scripts
│   ├── common/                  # Cross-platform wrapper scripts
│   │   ├── attach               # Cross-platform attach wrapper
│   │   ├── detach               # Cross-platform detach wrapper
│   │   ├── cleanup              # Cross-platform cleanup wrapper
│   │   └── test                 # Cross-platform test wrapper
│   ├── windows/                 # Windows-specific scripts (PowerShell)
│   ├── unix/                    # Unix-specific scripts (Bash)
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
g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o solution

# Create input.txt and run with beautiful debug output
echo "5" > input.txt
./solution < input.txt
```

### 2. **Practice Mode** (Assertions Only)

```bash
# Practice mode with assertions but no visual debug output
g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o solution
./solution < input.txt
```

### 3. **Contest Mode** (Zero Overhead)

```bash
# Contest submission mode - all debug macros become no-ops
g++ -std=c++20 -O2 -Wall main.cpp -o solution
./solution < input.txt
```

### 4. **Try the Demo**

```bash
# Compile and run the comprehensive demo
g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL demo_colorful_debug.cpp -o demo
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

| Mode           | Flags                | Features                                    |
| -------------- | -------------------- | ------------------------------------------- |
| **Full Debug** | `-DPRACTICE -DLOCAL` | All debug features, colorful output, timing |
| **Practice**   | `-DPRACTICE`         | Assertions and checks, no visual output     |
| **Contest**    | No flags             | Zero overhead, all macros become no-ops     |

## 🛠️ Key Features

- **🏗️ C++20 Compatible**: Smart header inclusion with automatic fallbacks
- **🎨 Enhanced Debug System**: Professional-grade colorful debugging experience
- **🔧 Modular Design**: Clean separation with easy attach/detach for submissions
- **🧪 Comprehensive Testing**: Advanced stress testing with visual feedback
- **🌐 Cross-Platform**: Works on Windows, Linux, macOS, and WSL
- **📊 Rich Data Structures**: DSU, Segment Tree, Fenwick Tree, and more
- **⚡ Performance Optimized**: Zero overhead in contest mode
- **🎯 Algorithm Library**: Graph algorithms, string processing, geometry, number theory

## 📖 Documentation

For detailed information and examples:

- **[Enhanced Debug Features](COLORFUL_DEBUG_FEATURES.md)** - Complete guide to the colorful debug system
- **[Complete Documentation](docs/readme.md)** - Comprehensive usage guide
- **[Demo Program](demo_colorful_debug.cpp)** - Live demonstration of all features
- **[Component Tests](tests/test_components.cpp)** - Usage examples for all utilities

## 🎯 Usage Patterns

### **Development Workflow**

1. Edit `main.cpp` for your solution (now in root directory)
2. Use `scripts/common/test` for stress testing (cross-platform)
3. Use `scripts/common/attach` before submission
4. Use `scripts/common/detach` to return to modular structure
5. Use `scripts/common/cleanup` to clean up generated files

### **CodeRunner Configuration (Windows/MinGW)**

```json
{
  "code-runner.executorMap": {
    "cpp": "g++ -std=c++20 -Wall -O2 -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt.exe; if ($?) { Get-Content input.txt | ./$fileNameWithoutExt.exe > output.txt }"
  }
}
```

**Note**: When using CodeRunner with the organized structure:

- Place your `input.txt` in the project root directory
- The output will be written to `output.txt` in the same directory

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

### **Direct Platform-Specific Usage**

```bash
# Windows (PowerShell)
./scripts/windows/attach.ps1
./scripts/windows/detach.ps1

# Unix-like (Linux, macOS, WSL)
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
# Windows (PowerShell)
powershell -File scripts/windows/test.ps1 -NumTests 50 -NoBrute

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

**Happy Competitive Programming! 🏆**

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
    "cpp": "g++ -std=c++20 -Wall -O2 -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt.exe; if ($?) { Get-Content input.txt | ./$fileNameWithoutExt.exe > output.txt }"
  }
}
```

**Enhanced Features:**

- Beautiful colored debug output in terminal
- Professional formatting with timestamps and location info
- Visual progress tracking and performance timing
- Zero impact on contest submissions
