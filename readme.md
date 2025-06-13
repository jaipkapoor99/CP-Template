# Universal C++20 Competitive Programming Template

A comprehensive, cross-platform competitive programming template with modular design and support for both Windows (PowerShell) and Unix-like systems (Bash).

## 📁 Project Structure

```
CP-Template/
├── src/                    # Source files
│   └── main.cpp           # Main solution template
├── include/               # Header files
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

# Compile and test (from scripts folder)
g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL ../src/main.cpp -o ../my_solution

# Create input.txt in root directory and run
echo "5" > ../input.txt
../my_solution < ../input.txt

# Run stress testing with brute force comparison (cross-platform)
./common/test 50
```

### 2. **For Submission/CPH Tools**

```bash
# From src/ directory - modifies main.cpp in-place (cross-platform)
cd src
../scripts/common/attach

# Or specify a different file
../scripts/common/attach solution.cpp

# From scripts/ directory - specify target file
cd scripts
./common/attach ../src/main.cpp
```

### 3. **Return to Modular Structure**

```bash
# From src/ directory - modifies main.cpp in-place (cross-platform)
cd src
../scripts/common/detach

# Or specify a different file
../scripts/common/detach solution.cpp

# From scripts/ directory - specify target file
cd scripts
./common/detach ../src/main.cpp
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
- **🧪 Comprehensive Testing**: Stress testing with brute force comparison
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

1. Edit `src/main.cpp` for your solution
2. Use `scripts/common/test` for stress testing (cross-platform)
3. Navigate to `src/` and use `../scripts/common/attach` before submission
4. Use `../scripts/common/detach` to return to modular structure
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

- Place your `input.txt` in the same directory as the file you're running
- For `src/main.cpp`, put `input.txt` in the `src/` folder
- The output will be written to `output.txt` in the same directory

### **CPH (Competitive Programming Helper) Setup**

1. Run `scripts/common/attach` to create single-file version (cross-platform)
2. Configure CPH to use the combined `src/main.cpp`
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

## 🔧 Customization

- **Test Generation**: Modify `scripts/generate_input.py` for your problem's input format
- **Brute Force**: The stress testing script auto-generates `brute.cpp` templates
- **Build Flags**: Adjust compilation flags in both PowerShell and Bash scripts as needed

## 📚 What's Included

- **Data Structures**: DSU, Segment Tree, Fenwick Tree, etc.
- **Algorithms**: Graph algorithms, string processing, number theory
- **Geometry**: 2D point operations, convex hull, line intersections
- **Advanced**: Matrix exponentiation, NTT, Mo's algorithm, HLD
- **Debugging**: Colored output, assertions, tracing macros

---

**Happy Competitive Programming! 🏆**
