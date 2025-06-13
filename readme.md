# Universal C++20 Competitive Programming Template

A comprehensive, organized competitive programming template with modular design and Windows/PowerShell support.

## 📁 Project Structure

```
CP-Template/
├── src/                    # Source files
│   └── main.cpp           # Main solution template
├── include/               # Header files
│   ├── cp_utils.hpp      # Core utilities and algorithms
│   └── debug_utils.hpp   # Debug macros and utilities
├── scripts/              # Automation scripts
│   ├── attach.ps1        # Combine files for submission
│   ├── detach.ps1        # Separate combined files
│   ├── test.ps1          # Stress testing with brute force
│   ├── cleanup.ps1       # Clean up generated/temporary files
│   └── generate_input.py # Test case generation
├── tests/                # Test files
│   └── test_components.cpp # Component testing
├── docs/                 # Documentation
│   └── readme.md         # Detailed documentation
└── .gitignore           # Git ignore rules
```

## 🚀 Quick Start

### 1. **Local Development & Testing**
```powershell
# Navigate to scripts directory
cd scripts

# Compile and test (from scripts folder)
g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL ../src/main.cpp -o ../my_solution

# Create input.txt in root directory and run
echo "5" > ../input.txt
../my_solution < ../input.txt

# Run stress testing with brute force comparison
.\test.ps1 50
```

### 2. **For Submission/CPH Tools**
```powershell
# From src/ directory - modifies main.cpp in-place
cd src
../scripts/attach.ps1

# Or specify a different file
../scripts/attach.ps1 solution.cpp

# From scripts/ directory - specify target file
cd scripts
.\attach.ps1 ../src/main.cpp
```

### 3. **Return to Modular Structure**
```powershell
# From src/ directory - modifies main.cpp in-place
cd src
../scripts/detach.ps1

# Or specify a different file
../scripts/detach.ps1 solution.cpp

# From scripts/ directory - specify target file
cd scripts
.\detach.ps1 ../src/main.cpp
```

### 4. **Clean Up Generated Files**
```powershell
# Remove all temporary/generated files (can run from anywhere)
scripts\cleanup.ps1

# Force cleanup without confirmations
scripts\cleanup.ps1 -Force

# Verbose output to see what's being cleaned
scripts\cleanup.ps1 -Verbose
```

## 🛠️ Key Features

- **🏗️ Organized Structure**: Clean separation of source, headers, scripts, tests, and docs
- **🔧 Modular Design**: Easy to maintain and extend
- **🧪 Comprehensive Testing**: Stress testing with brute force comparison
- **📝 Rich Documentation**: Detailed examples and usage guides
- **🖥️ Windows-First**: PowerShell scripts optimized for Windows development
- **⚡ Modern C++20**: Latest language features and optimizations

## 📖 Documentation

For detailed documentation, examples, and usage guides, see:
- **[Complete Documentation](docs/readme.md)** - Comprehensive guide with examples
- **[Component Tests](tests/test_components.cpp)** - Usage examples for all utilities

## 🎯 Usage Patterns

### **Development Workflow**
1. Edit `src/main.cpp` for your solution
2. Use `scripts/test.ps1` for stress testing
3. Navigate to `src/` and use `../scripts/attach.ps1` before submission
4. Use `../scripts/detach.ps1` to return to modular structure
5. Use `scripts/cleanup.ps1` to clean up generated files

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
1. Run `scripts/attach.ps1` to create single-file version
2. Configure CPH to use the combined `src/main.cpp`
3. Use `scripts/detach.ps1` when returning to development

## 🔧 Customization

- **Test Generation**: Modify `scripts/generate_input.py` for your problem's input format
- **Brute Force**: The stress testing script auto-generates `brute.cpp` templates
- **Build Flags**: Adjust compilation flags in the PowerShell scripts as needed

## 📚 What's Included

- **Data Structures**: DSU, Segment Tree, Fenwick Tree, etc.
- **Algorithms**: Graph algorithms, string processing, number theory
- **Geometry**: 2D point operations, convex hull, line intersections
- **Advanced**: Matrix exponentiation, NTT, Mo's algorithm, HLD
- **Debugging**: Colored output, assertions, tracing macros

---

**Happy Competitive Programming! 🏆** 