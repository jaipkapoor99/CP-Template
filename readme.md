# Universal C++20 Competitive Programming Template

This template provides a robust starting point for C++20 competitive programming. It's modular, with core logic in `main.cpp`, general utilities in `cp_utils.hpp`, and debugging tools in `debug_utils.hpp`.

## Project Structure

- `main.cpp`: Contains your `main()` and `solve()` functions. This is the primary file you'll edit for each problem. It includes `cp_utils.hpp`.
- `cp_utils.hpp`: A comprehensive header with type aliases, constants, macros, modular arithmetic, timer, utility functions, number theory helpers, and generic I/O. It includes `debug_utils.hpp`.
- `debug_utils.hpp`: Provides debugging macros like `DEBUG(...)`, `ASSERT(...)`, and `TRACE(...)` with color-coded output and source location info.
- `test.sh`: Script for stress testing your solution in `main.cpp` against generated inputs or a brute-force solution (if implemented).
- `combine.sh`: Script to bundle `main.cpp`, `cp_utils.hpp`, and `debug_utils.hpp` into a single `submission_main.cpp` file, suitable for online judges.
- `generate_input.py` (Optional): Example Python script for generating test inputs for `test.sh`.
- `readme.md`: This file.

## Features

- **Modern C++20:** Leverages C++20 features.
- **Modular Design:** Clean separation of problem-specific code (`main.cpp`) from common utilities (`cp_utils.hpp`) and debugging tools (`debug_utils.hpp`).
- \*\*Build Modes & Debugging (via `cp_utils.hpp` & `debug_utils.hpp`):
  - `PRACTICE + LOCAL` (-DPRACTICE -DLOCAL flags): Enables `TRACE`, `DEBUG`, `ASSERT`, and brute-force checker integration.
  - `PRACTICE` only (-DPRACTICE flag): For stress testing with `ASSERT` and brute-force, no verbose `DEBUG`/`TRACE`.
  - Contest Mode (e.g., `-DONLINE_JUDGE` flag, no debug defines): Debug macros become no-ops for minimal overhead.
- **Comprehensive Utilities (in `cp_utils.hpp`):**
  - Type Aliases: `ll`, `vll`, `pii`, `Mint`, etc.
  - Constants: `MOD_CONST`, `INF`, `PI`, etc.
  - Macros: For loops, vector ops, I/O shortcuts (`YES`/`NO`).
  - Modular Arithmetic: `ModularOps` struct.
  - Timer: `Timer` class.
  - Utility Functions: `maximise`, `minimise`.
  - Number Theory: Miller-Rabin `isPrime`, `isDivisible`, `isOdd`, etc.
  - Generic I/O: Variadic `read` and `print`, `printv`.
  - Fast I/O: `FASTINOUT` macro.
- **Test Case Handling:** Standard `main` function reads `t` and calls `solve()` for each test case.
- **Brute-Force Checker Hook:** `solve_brute_example()` in `main.cpp` for use with `PRACTICE` mode.

## How to Use

1.  **Setup:** Ensure `main.cpp`, `cp_utils.hpp`, `debug_utils.hpp`, `test.sh`, and `combine.sh` are in your project directory. Make scripts executable (`chmod +x test.sh combine.sh`).
2.  **Implement Logic:** Write your solution in the `solve(int test_case_num)` function in `main.cpp`. If using brute-force checks, also implement `solve_brute_example(...)` in `main.cpp`.
3.  **Local Debugging & Testing:**
    ```bash
    # Compile for full debug features
    g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o my
    ./my < input.txt
    ```
4.  **Stress Testing:**
    ```bash
    # Compile for stress testing (asserts active, less spam)
    g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o my_solution # test.sh uses my_solution by default
    ./test.sh <num_tests_optional>
    ```
5.  **Prepare for Submission:**
    ```bash
    ./combine.sh main.cpp
    ```
    This creates `submission_main.cpp`.
6.  **Submit to Online Judge:** Upload the generated `submission_main.cpp`. The judge will compile it (usually with `-DONLINE_JUDGE` and no debug flags).
    Example contest compile command: `g++ -std=c++20 -O2 -Wall -DONLINE_JUDGE submission_main.cpp -o solution`

### Configuring Your Editor/IDE for Running (e.g., VS Code)

If you use a code runner extension (like "Code Runner" in VS Code), configure its C++ execution command for `main.cpp`:

**Example for VS Code's "Code Runner" extension (`settings.json`):**

```json
"code-runner.executorMap": {
    "cpp": "cd $dir && g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt && $dir/$fileNameWithoutExt < input.txt"
}
```

This command ensures `main.cpp` is compiled with debugging defines and linked with utilities from included headers, then runs it with input from `input.txt`.

## Customization

- Modify `solve_brute_example` in `main.cpp` for each problem.
- Adjust utilities in `cp_utils.hpp` or add new ones as needed.

This template aims to streamline the competitive programming workflow by providing a feature-rich, modular, and configurable base.
