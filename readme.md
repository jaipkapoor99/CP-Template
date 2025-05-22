# Universal C++20 Competitive Programming Template

This template provides a robust starting point for C++20 competitive programming, incorporating best practices and utilities for efficient problem-solving and debugging.

## Features

-   **C++20 Standard:** Leverages modern C++ features.
-   **Build Modes:**
    -   `PRACTICE + LOCAL`: Enables full debugging capabilities including `TRACE`, `DEBUG`, `ASSERT`, and brute-force checker. Compile with:
        ```bash
        g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o my
        ```
    -   `PRACTICE` (only): For stress testing with `ASSERT` and brute-force, but without verbose `DEBUG` or `TRACE` outputs. Compile with:
        ```bash
        g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o my
        ```
    -   Contest Mode: Optimized for submission (no debug symbols or macros). Compile with:
        ```bash
        g++ -std=c++20 -O2 -Wall main.cpp -o submit
        ```
-   **Debugging Utilities:**
    -   `DEBUG(...)`: Variadic macro for printing debug information with source location (file, line, function) and ANSI colors. Enabled by `-DLOCAL`.
    -   `TRACE(...)`: Similar to `DEBUG`, intended for tracing execution flow. Enabled by `-DLOCAL` and `-DPRACTICE`.
    -   `ASSERT(condition, message)`: Halts execution if a condition is false, printing a message. Enabled by `-DPRACTICE`.
    -   ANSI Color Codes: `RED`, `BLUE`, `GREEN`, `RESET` for enhanced `std::cerr` output.
-   **Brute-Force Checker:**
    -   `solve_brute_example(...)`: A placeholder function to implement a naive or brute-force solution.
    -   The `solve()` function includes a `#ifdef PRACTICE` block to compare the main solution's output with the brute-force solution's output for each test case.
    -   Logs include test case numbers for easier identification of failures.
-   **Standard Headers:** Includes `<bits/stdc++.h>` and common PBDS headers.
-   **Type Aliases:** Common type aliases like `ll` (long long), `vll` (vector<long long>), `pii` (pair<int, int>), etc.
-   **Constants:** Predefined constants like `MOD`, `INF`, `PI`.
-   **Modular Arithmetic:** `ModularOps` struct for operations under a modulus.
-   **Macros:** Shortcuts for common loops (`f`, `cf`, `rf`), vector operations (`all`, `sz`), and I/O (`YES`, `NO`).
-   **Fast I/O:** `FASTINOUT` macro.
-   **Generic I/O Helpers:** `read(...)` and `print(...)` variadic templates for easy input and output.
-   **Timer Utility:** `Timer` class for measuring execution time.
-   **Test Case Handling:** `main` function reads the number of test cases (`t`) and calls `solve(test_case_num)` for each.

## How to Use

1.  **Copy `template.cpp`** to your problem file (e.g., `main.cpp`).
2.  **Implement Logic:**
    -   Fill in the problem-specific logic within the `solve(int test_case_num)` function.
    -   If using the brute-force checker, implement `solve_brute_example(...)` with the naive approach.
3.  **Compile:** Use the appropriate g++ flags based on your needs (see Build Modes).
4.  **Run:**
    -   For local testing with input redirection: `./my < input.txt`
    -   For CPH-like extensions, ensure the extension is configured to call `solve()` for each test case.

## Customization

-   Modify `solve_brute_example` for each problem.
-   Adjust constants, type aliases, or add new helper functions as needed.
-   The `TRACE` and `DEBUG` macros output to `std::cerr`.

This template aims to streamline the competitive programming workflow by providing a feature-rich and configurable base.
