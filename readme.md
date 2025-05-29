# Universal C++20 Competitive Programming Template

This template provides a robust starting point for C++20 competitive programming. It's modular, with core logic in `main.cpp`, general utilities in `cp_utils.hpp`, and debugging tools in `debug_utils.hpp`.

## Project Structure

- `main.cpp`: Contains your `main()` and `solve()` functions. This is the primary file you'll edit for each problem. It includes `cp_utils.hpp`.
- `cp_utils.hpp`: A comprehensive header with type aliases, constants, macros, modular arithmetic, timer, utility functions (including `solve_brute_example`), number theory helpers, and generic I/O. It includes `debug_utils.hpp`.
- `debug_utils.hpp`: Provides debugging macros like `DEBUG(...)`, `ASSERT(...)`, and `TRACE(...)` with color-coded output and source location info.
- `test.sh`: Script for stress testing your solution in `main.cpp` against generated inputs or a brute-force solution.
- `attach.sh`: Script to bundle `cp_utils.hpp` (and `debug_utils.hpp`) directly into `main.cpp` by replacing the `#include "cp_utils.hpp"` line. The original `main.cpp` is overwritten. This is primarily for compatibility with tools like CPH (Competitive Programming Helper) that expect a single file.
- `detach.sh`: Script to reverse the `attach.sh` operation. It extracts `cp_utils.hpp` and `debug_utils.hpp` from the combined `main.cpp` using embedded markers, restoring the original modular structure.
- `generate_input.py` (Optional): Example Python script for generating test inputs for `test.sh`.
- `readme.md`: This file.

## Features

- **Modern C++20:** Leverages C++20 features.
- **Modular Design:** Clean separation of problem-specific code (`main.cpp`) from common utilities (`cp_utils.hpp`) and debugging tools (`debug_utils.hpp`). Can be combined into a single file for specific tools/judges and detached again.
- \*\*Build Modes & Debugging (via `cp_utils.hpp` & `debug_utils.hpp`):
  - `PRACTICE + LOCAL` (-DPRACTICE -DLOCAL flags): Enables `TRACE`, `DEBUG`, `ASSERT`, and brute-force checker integration (via `solve_brute_example` in `cp_utils.hpp`).
  - `PRACTICE` only (-DPRACTICE flag): For stress testing with `ASSERT` and brute-force, no verbose `DEBUG`/`TRACE`.
  - Contest Mode (e.g., `-DONLINE_JUDGE` flag, no debug defines): Debug macros become no-ops for minimal overhead.
- **Comprehensive Utilities (in `cp_utils.hpp`):**
  - Type Aliases: `ll`, `vll`, `pii`, `Mint`, etc.
  - Constants: `MOD_CONST`, `INF`, `PI`, etc.
  - Macros: For loops, vector ops, I/O shortcuts (`YES`/`NO`).
  - Modular Arithmetic: `ModularOps` struct.
  - Timer: `Timer` class.
  - Utility Functions: `maximise`, `minimise`.
  - Data Structures:
    - Disjoint Set Union (DSU) / Union-Find: `DSU` struct.
  - Example Brute-Force Solver: `solve_brute_example` (user must implement problem-specific logic).
  - Number Theory: Miller-Rabin `isPrime`, `isDivisible`, `isOdd`, etc.
  - Generic I/O: Variadic `read` and `print`, `printv`.
  - Fast I/O: `FASTINOUT` macro.
- **Test Case Handling:** Standard `main` function reads `t` and calls `solve()` for each test case.

## How to Use

1.  **Setup:** Ensure `main.cpp`, `cp_utils.hpp`, `debug_utils.hpp`, `test.sh`, `attach.sh`, and `detach.sh` are in your project directory. Make scripts executable (`chmod +x test.sh attach.sh detach.sh`).
2.  **Implement Logic:** Write your solution in the `solve(int test_case_num)` function in `main.cpp`. If using brute-force checks, implement the logic in `solve_brute_example(...)` within `cp_utils.hpp`.
3.  **Local Debugging & Testing (Modular Structure):**
    ```bash
    # Ensure files are detached if previously combined: ./detach.sh main.cpp
    # Compile for full debug features
    g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o my
    ./my < input.txt
    ```
4.  **Stress Testing (Modular Structure):**
    ```bash
    # Ensure files are detached: ./detach.sh main.cpp
    # Compile for stress testing (asserts active, less spam)
    g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o my_solution # test.sh uses my_solution by default
    ./test.sh <num_tests_optional>
    ```
5.  **Prepare for Submission / CPH Tool Usage (Attached File):**
    ```bash
    ./attach.sh main.cpp
    ```
    This modifies `main.cpp` in place, embedding `cp_utils.hpp` and `debug_utils.hpp`.
    The `main.cpp` file itself is now the single file for submission or for CPH-like tools.
6.  **Submit to Online Judge:** Upload the (attached) `main.cpp`. The judge will compile it (usually with `-DONLINE_JUDGE` and no debug flags).
    Example contest compile command: `g++ -std=c++20 -O2 -Wall -DONLINE_JUDGE main.cpp -o solution`
7.  **Revert to Modular Structure:**
    ```bash
    ./detach.sh main.cpp
    ```
    This restores `main.cpp`, `cp_utils.hpp`, and `debug_utils.hpp` to their separate states.

### Configuring Your Editor/IDE (e.g., VS Code Global Settings)

For an optimal development experience with linting, IntelliSense, and code execution, it is recommended to configure your VS Code **global user settings**. This template is designed to work seamlessly with these global settings, removing the need for workspace-specific `.vscode/settings.json` or `.vscode/c_cpp_properties.json` files for this project.

**1. C/C++ Extension Configuration (Global `settings.json`):**

To ensure correct C++20 IntelliSense, linting, and compilation, configure the Microsoft C/C++ extension by adding or updating the following in your global `settings.json` file (accessible via `Preferences: Open User Settings (JSON)` in the Command Palette):

```json
{
  // ... your other global settings ...

  "C_Cpp.default.compilerPath": "YOUR_PATH_TO_G++/MINGW/bin/g++.exe", // e.g., "C:/mingw64/bin/g++.exe"
  "C_Cpp.default.cppStandard": "c++20",
  "C_Cpp.default.cStandard": "c17",
  "C_Cpp.default.intelliSenseMode": "windows-gcc-x64", // Or your platform-specific mode e.g., "linux-gcc-x64", "macos-clang-x64"
  "C_Cpp.default.includePath": [
    // Add paths to your compiler's standard library includes if not found automatically
    // e.g., "C:/mingw64/include/c++/your_version",
    // "C:/mingw64/include/c++/your_version/x86_64-w64-mingw32",
    // "C:/mingw64/include"
  ],
  "C_Cpp.default.defines": [
    "_DEBUG",
    "UNICODE",
    "_UNICODE",
    "PRACTICE", // For enabling asserts and brute-force checks
    "LOCAL" // For enabling TRACE/DEBUG macros
  ]
}
```

_Replace `"YOUR_PATH_TO_G++/MINGW/bin/g++.exe"` and the example include paths with the actual paths for your MinGW (or other GCC-compatible) compiler installation. The `defines` for `PRACTICE` and `LOCAL` enable debugging features provided by this template._

**2. Code Runner Extension Configuration (Global `settings.json`):**

If you use the "Code Runner" extension, configure its C++ execution command in your global `settings.json` to match your environment (e.g., PowerShell on Windows, or bash on Linux/macOS). This command should compile `main.cpp` (which includes all necessary utilities) and run the executable with input from `input.txt`.

_Example for PowerShell on Windows:_

```json
{
  // ... your other global settings ...

  "code-runner.executorMap": {
    "cpp": "cd $dir; g++ -std=c++20 -Wall -O2 -DPRACTICE -DLOCAL '$fileName' -o '$fileNameWithoutExt.exe'; if ($?) { Get-Content ($dir + 'input.txt') | & ($dir + '$fileNameWithoutExt.exe') }"
  }
}
```

_Example for bash-like shells (Linux/macOS/WSL):_

```json
{
  // ... your other global settings ...

  "code-runner.executorMap": {
    "cpp": "cd $dir && g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt && ./$fileNameWithoutExt < input.txt"
  }
}
```

_These commands ensure `main.cpp` is compiled with debugging defines and then run with input from `input.txt`._

By setting these globally, any C++ project you open will benefit from a consistent environment without needing project-specific VS Code configuration files.

## Customization

- Modify `solve_brute_example` in `cp_utils.hpp` for each problem.
- Adjust utilities in `cp_utils.hpp` or add new ones as needed.

## DSU (Union-Find) Usage Example

```cpp
// In cp_utils.hpp, the DSU struct is available.
// To use it in main.cpp:

#include "cp_utils.hpp"

void solve(int test_case_num) {
    int n = 5; // Number of elements
    DSU dsu(n);

    dsu.unite(0, 1);
    dsu.unite(2, 3);
    dsu.unite(0, 4);

    DEBUG(dsu.connected(1, 4)); // true
    DEBUG(dsu.connected(0, 2)); // false
    DEBUG(dsu.size(0));         // 3 (elements 0, 1, 4 are in the same set)
    DEBUG(dsu.num_sets());      // 2 (sets are {0,1,4} and {2,3})

    dsu.add_element(); // Adds a 6th element (index 5)
    dsu.unite(2,5);
    DEBUG(dsu.num_sets()); // Still 2 sets, {0,1,4} and {2,3,5}
    DEBUG(dsu.size(5)); // 3
}

// ... rest of main.cpp ...
```

This template aims to streamline the competitive programming workflow by providing a feature-rich, modular, and configurable base, adaptable for various tools and submission systems.
