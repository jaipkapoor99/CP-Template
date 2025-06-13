# Universal C++20 Competitive Programming Template

A comprehensive, cross-platform competitive programming template with modular design and support for both Windows (PowerShell) and Unix-like systems (Bash).

## 📁 Project Structure

```
CP-Template/
├── main.cpp              # Main solution file (root level for easy access)
├── src/                  # Additional source files (if needed)
├── include/              # Header files
│   ├── cp_utils.hpp      # Core utilities and algorithms
│   └── debug_utils.hpp   # Debug macros and utilities
├── scripts/              # Automation scripts
│   ├── common/           # Cross-platform wrapper scripts
│   │   ├── attach        # Cross-platform attach wrapper
│   │   ├── detach        # Cross-platform detach wrapper
│   │   ├── cleanup       # Cross-platform cleanup wrapper
│   │   └── test          # Cross-platform test wrapper
│   ├── windows/          # Windows-specific scripts (PowerShell)
│   │   ├── attach.ps1    # Combine files for submission
│   │   ├── detach.ps1    # Separate combined files
│   │   ├── test.ps1      # Stress testing with brute force
│   │   └── cleanup.ps1   # Clean up generated/temporary files
│   ├── unix/             # Unix-specific scripts (Bash)
│   │   ├── attach.sh     # Combine files for submission
│   │   ├── detach.sh     # Separate combined files
│   │   ├── test.sh       # Stress testing with brute force
│   │   └── cleanup.sh    # Clean up generated/temporary files
│   └── generate_input.py # Test case generation
├── tests/                # Test files
│   └── test_components.cpp # Component testing
├── docs/                 # Documentation
│   └── readme.md         # Detailed documentation
└── .gitignore           # Git ignore rules
```

## 🚀 Quick Start

### 1. **Local Development & Testing**

```bash
# Navigate to scripts directory
cd scripts

# Compile and test (from project root)
g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o my_solution

# Create input.txt in root directory and run
echo "5" > input.txt
./my_solution < input.txt

# Run stress testing with brute force comparison (cross-platform)
./common/test 50
```

### 2. **For Submission/CPH Tools**

```bash
# From project root - modifies main.cpp in-place (cross-platform)
scripts/common/attach

# Or specify a different file
scripts/common/attach solution.cpp

# From scripts/ directory - specify target file
cd scripts
./common/attach ../main.cpp
```

### 3. **Return to Modular Structure**

```bash
# From project root - modifies main.cpp in-place (cross-platform)
scripts/common/detach

# Or specify a different file
scripts/common/detach solution.cpp

# From scripts/ directory - specify target file
cd scripts
./common/detach ../main.cpp
```

### 4. **Clean Up Generated Files**

```bash
# Remove all temporary/generated files (can run from anywhere, cross-platform)
scripts/common/cleanup

# Force cleanup without confirmations
scripts/common/cleanup --force

# Verbose output to see what's being cleaned
scripts/common/cleanup --verbose
```

## 🛠️ Key Features

- **🏗️ Organized Structure**: Clean separation of source, headers, scripts, tests, and docs
- **🔧 Modular Design**: Easy to maintain and extend
- **🧪 Comprehensive Testing**: Advanced stress testing with brute force comparison
- **🤖 Auto-Generated Templates**: Automatically creates brute force solution templates
- **📊 Smart Test Generation**: Inline and Python-based random test case generation
- **📝 Rich Documentation**: Detailed examples and usage guides
- **🌐 Cross-Platform**: Works on Windows (PowerShell), Linux, macOS, and WSL
- **🖥️ Smart Platform Detection**: Automatically uses the right scripts for your environment
- **⚡ Modern C++20**: Latest language features and optimizations

## 📖 Documentation

For detailed documentation, examples, and usage guides, see:

- **[Complete Documentation](docs/readme.md)** - Comprehensive guide with examples
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
