# CP-Template

A **grandmaster-level C++20 Competitive Programming Template** designed for speed, efficiency, and versatility. This template incorporates modern C++20 features, advanced debugging tools, fast I/O, randomization, modular arithmetic helpers, and much more.

---

## 🚀 Features

- **C++20 Ready:** Uses the latest language features for concise and powerful code.
- **Fast Input/Output:** Macros and settings for lightning-fast I/O.
- **Rich Type Aliases:** Shortcuts for common data structures (vectors, pairs, maps, etc.).
- **Advanced Macros:** For iteration, container manipulation, and readability.
- **Powerful Debugging:** Local-only, source-aware, colorized, and non-intrusive debug macros.
- **Modern STL Utilities:** Ranges, spans, bit-manipulation helpers, and more.
- **Random Number Generator:** Secure and fast for randomized algorithms.
- **Policy-Based Data Structures:** Order-statistics set/map via GNU PBDS.
- **Safe Hashing:** Custom hash for unordered containers to avoid collisions.
- **Modular Arithmetic Helpers:** Fast, reusable modint class for mod calculations.
- **Timer Utility:** For quick performance profiling.
- **Flexible Input/Output:** Variadic read/print, tuple and span support.
- **Ready for Expansion:** Easily add your own snippets and helpers.

---

## 🛠️ How to Use

1. **Copy** `template.cpp` into your contest workspace.
2. **Compile** with C++20 support (e.g. `g++ -std=c++20 -O2 template.cpp -o solution`).
3. **Enable Debugging (Optional):**  
   Locally debug with advanced output by compiling with `-DLOCAL`:
   ```
   g++ -std=c++20 -O2 -DLOCAL template.cpp -o solution
   ```
4. **Start Coding:**  
   Use the built-in aliases, macros, and helpers. See the template’s comments for usage examples.

---

## 📦 Main Components

| Feature            | Macro/Type/Alias         | Description                                  |
| ------------------ | ------------------------ | -------------------------------------------- |
| Fast I/O           | `FASTINOUT`              | Fast cin/cout setup                          |
| Type Aliases       | `ll`, `vll`, `pii`, etc. | Shortforms for common types                  |
| Ranges             | `all(v)`, `rall(v)`      | Easy container manipulation                  |
| Loop Macros        | `f(i,s,e)`, `cf(i,s,e)`  | Fast for-loop patterns                       |
| Debugging          | `DEBUG(...)`             | Advanced, local-only, colorized debug output |
| Random Generator   | `rand_ll(l, r)`          | Uniform random in [l, r]                     |
| PBDS               | `os<T>`                  | Ordered set with order-statistics            |
| Modular Arithmetic | `Mint<MOD>`              | Handy class for mod calculations             |
| Timer              | `Timer`                  | Profile code segments                        |
| Safe Hashing       | `custom_hash`            | For unordered containers                     |
| Math Utils         | `gcd`, `lcm`, `ceildiv`  | Common math tools                            |

---

## 📝 Example

```cpp
#include "template.cpp"

void solve() {
    int n; read(n);
    vi a(n); read(a);
    DEBUG(n, a);
    UNIQUE(a);
    print("Size after unique:", sz(a));
}

int main() {
    FASTINOUT;
    int t = 1;
    read(t);
    while (t--) solve();
    return 0;
}
```

---

## 🧑‍💻 For Beginners & Grandmasters

- **Beginners:**  
  Simple to use—just focus on writing your algorithm!
- **Grandmasters:**  
  All the power tools are here when you need them (PBDS, bit hacks, modular, advanced debug).

---

## 🏆 Credits

- Inspired by templates from "tourist", "Benq", and many top CPers.
- Maintained by [jaipkapoor99](https://github.com/jaipkapoor99).

---

## 📣 Contributions

Feel free to fork or suggest improvements!

---

## 🔗 License

MIT License

---

## 🤖 AI-Assisted Development

This competitive programming setup, including the C++20 template, testing scripts, and this documentation, was developed and refined with the assistance of AI tools like GitHub Copilot. You can leverage such AI assistants to:

- **Accelerate Coding**: Get suggestions for boilerplate code, algorithms, and complex logic within `template.cpp`.
- **Generate Test Cases**: Ask AI to help you write or modify `generate_input.py` for specific problem constraints.
- **Debug Issues**: Get insights into errors or unexpected behavior in your C++ code or shell scripts.
- **Understand Code**: Ask for explanations of parts of the template or helper scripts.
- **Improve Scripts**: Refine `test.sh` or other helper scripts for more advanced testing scenarios.

By combining this robust template with AI-powered tools, you can significantly enhance your competitive programming workflow.

# Competitive Programming Setup

This repository contains a C++ template for competitive programming, along with helper scripts for testing and input generation.

## Files

- **`template.cpp`**: The main C++ template file. It includes common headers, fast I/O, and various helper macros and functions.
- **`test.sh`**: A bash script for stress testing solutions. It compiles the C++ code, generates test cases (either inline or using a Python script), runs the solution against the test cases, and reports any discrepancies.
- **`generate_input.py`**: A Python script for generating test cases. It can be customized to produce various types of input data.
- **`input.txt`**: A file for providing manual input to the C++ program when not using the generator.
- **`my.exe` / `template.exe`**: Compiled executable of `template.cpp`. (The name might vary based on compilation commands).

## `template.cpp`

This is a **C++20** template designed for competitive programming.

### Key Features:

- Standard headers pre-included (`<bits/stdc++.h>`).
- Fast I/O setup.
- Common type aliases (`ll` for `long long`, `vi` for `vector<int>`, etc.).
- Debugging macros (`debug(...)`) that only print when `LOCAL` is defined.
- Helper functions for reading and printing various data types, including pairs and vectors.
- Variadic templates for `read` and `print` functions to handle multiple arguments.

### Compilation:

The `test.sh` script compiles this file using `g++`. The default flags are `-std=c++20 -O2 -Wall`. If you define `LOCAL` (e.g., `g++ -std=c++20 -O2 -Wall -DLOCAL template.cpp -o template.exe`), the `debug(...)` macros will be enabled.

## `test.sh`

This script automates the process of testing your C++ solution against multiple test cases.

### Usage:

```bash
./test.sh [NUM_TESTS] [GENERATOR_TYPE]
```

- `NUM_TESTS` (optional): The number of test cases to run. Defaults to 100.
- `GENERATOR_TYPE` (optional): Specifies the input generation method.
  - `inline` (default): Uses a basic inline generator within the script (currently generates a single number).
  - `python`: Uses the `generate_input.py` script to generate test cases.

### Configuration Variables (at the top of the script):

- `CPP_FILE`: Path to your C++ solution file (default: `template.cpp`).
- `EXECUTABLE_NAME`: Name for the compiled executable (default: `template.exe`).
- `INPUT_FILE`: Name of the file to store generated input (default: `input.txt`).
- `OUTPUT_FILE`: Name of the file to store your program's output (default: `output.txt`).
- `BRUTE_OUTPUT_FILE`: (If using a brute-force checker) Name of the file for brute-force output (default: `brute_output.txt`).
- `COMPILER`: C++ compiler (default: `g++`).
- `STD_VERSION`: C++ standard (default: `c++20`).
- `OPTIMIZATION_LEVEL`: Compiler optimization level (default: `-O2`).
- `EXTRA_FLAGS`: Additional compiler flags (default: `-Wall`).
- `LOCAL_DEBUG_FLAG`: Flag to enable local debugging macros (default: `-DLOCAL`). Set to empty string to disable.
- `PYTHON_GENERATOR_SCRIPT`: Path to the Python input generator (default: `generate_input.py`).
- `KEEP_FILES_ON_FAILURE`: Set to `true` to keep `input.txt` and `output.txt` if a test fails (default: `false`).

### Workflow:

1.  **Compilation**: Compiles the `CPP_FILE` into `EXECUTABLE_NAME`. If `LOCAL_DEBUG_FLAG` is set, it's included in compilation.
2.  **Test Loop**:
    - For each test case:
      - **Input Generation**:
        - If `GENERATOR_TYPE` is `python`, it runs `python3 ${PYTHON_GENERATOR_SCRIPT} > ${INPUT_FILE}`.
        - If `GENERATOR_TYPE` is `inline`, it runs an internal `generate_inline_input` function.
        - Otherwise, it attempts to use `input.txt` if it exists and is not empty, or defaults to inline generation.
      - **Execution**: Runs `./${EXECUTABLE_NAME} < ${INPUT_FILE} > ${OUTPUT_FILE}`.
      - **Verification**:
        - Currently, it checks if the program terminated with an error (`$? -ne 0`).
        - **(Placeholder for Brute-Force/Checker)**: The script includes commented-out sections for comparing against a brute-force solution or a dedicated checker. You would need to implement `brute.cpp` or a checker and uncomment/modify these parts.
      - **Output**: Prints "AC" (Accepted) or "WA" (Wrong Answer) with the test case number. If "WA", it prints the input and your program's output.
3.  **Cleanup**: Removes temporary files (`INPUT_FILE`, `OUTPUT_FILE`, `BRUTE_OUTPUT_FILE`) unless `KEEP_FILES_ON_FAILURE` is true and a test failed. The executable is always kept.

## `generate_input.py`

A Python script for generating test cases.

### Structure:

- `generate_case()`: This function is responsible for printing a single test case to standard output.
- The script currently contains commented-out examples for generating various types of inputs:
  - A single number.
  - An array of numbers.
  - A tree (edges).
  - A grid.
  - Multiple test cases (if your C++ program expects a `t` first).

### Customization:

Modify the `generate_case()` function to produce the specific input format required by your problem. Uncomment and adapt the examples as needed.

## `input.txt`

This file is used for manual input if you are not using the `test.sh` script's generation capabilities or if `test.sh` is configured to use it directly (e.g., if no generator is specified and `input.txt` exists).

When `test.sh` uses a generator (`inline` or `python`), it will overwrite this file with the generated input for each test case.

## Setup and Usage Flow

1.  **Write your solution** in `template.cpp` (or rename it and update `test.sh`).
2.  **Configure `test.sh`**:
    - Adjust `CPP_FILE`, `EXECUTABLE_NAME` if needed.
    - Set `LOCAL_DEBUG_FLAG` to `-DLOCAL` for debugging, or "" to disable.
3.  **Prepare Input Generation**:
    - **For Python generator**: Modify `generate_input.py`'s `generate_case()` function to match the problem's input constraints.
    - **For inline generator**: Modify the `generate_inline_input()` function within `test.sh`.
    - **For manual input**: Place your test case in `input.txt` and ensure `test.sh` is set to use it (e.g., by providing no generator type or an invalid one, and ensuring `input.txt` is present).
4.  **Run the test script**:
    ```bash
    ./test.sh [number_of_tests] [generator_type]
    ```
    For example:
    ```bash
    ./test.sh 50 python  # Run 50 tests using the Python generator
    ./test.sh 10 inline # Run 10 tests using the inline generator
    ./test.sh           # Run 100 tests using the default (inline) generator
    ```
5.  **Review results**: The script will indicate "AC" or "WA" for each test. If "WA", it will show the input that caused the failure and your program's output.

This setup provides a flexible and robust environment for developing and testing competitive programming solutions.
