# Universal C++20 Competitive Programming Template: A Beginner's Guide

Welcome to the world of competitive programming (CP)! This guide will walk you through using this C++20 template, even if you're just starting out.

## What is Competitive Programming?

Competitive programming is a mind sport where participants solve algorithmic puzzles and coding problems within a time limit. Problems often require knowledge of data structures (like arrays, lists, trees) and algorithms (like sorting, searching, graph traversal).

## What is This Template For?

This `template.cpp` file is a starting point for your C++ solutions. It's packed with helpful tools and shortcuts commonly used in CP to help you code faster and more efficiently. Think of it as a well-equipped toolbox for a craftsman.

## Getting Started: Your First Problem

Let's imagine you're solving your first problem: "Read two numbers and print their sum."

### 1. Understanding the Files

- **`template.cpp`**: This is your main C++ code file. You'll write your solution here.
- **`input.txt`**: You can manually put test inputs here to run your code.
- **`readme.md`**: The file you're reading now!
- **Copies of `template.cpp` (e.g., `problem_name.cpp`)**: You'll typically copy `template.cpp` and rename it for each specific problem you solve.
- **`.exe` files (e.g., `template.exe`)**: These are the compiled, runnable versions of your C++ code. You don't edit these directly.
- **`test.sh` & `generate_input.py`**: Advanced tools for testing your code with many inputs. We'll cover these later.

### 2. Setting Up Your Environment (One-Time Setup)

To use this template, you need a C++ compiler. `g++` is a common one. If you're using VS Code, extensions like "C/C++" by Microsoft and "Code Runner" can help you compile and run code easily.

**Ensure `g++` is installed and in your system's PATH.** You can check by opening a terminal (PowerShell on Windows) and typing `g++ --version`.

### 3. Writing Your Solution in `template.cpp`

Open `template.cpp`. You'll see a lot of code. Don't be intimidated! Most of it is helper code. The most important part for you is the `solve()` function.

```cpp
// ───────────────── SOLVE FUNCTION ──────────────────────
//  Your main code lives here.
//  This function handles a single test case: reads input, computes, and prints output
void solve()
{
    // --- Example: Read input for a single test case ---
    // int n_val;
    // read(n_val);                                   // Read the actual 'n' for this test case
    // TRACE("Inside solve function, n_val:", n_val); // Added TRACE call

    // --- Example: Compute answer for a single test case ---
    // ll current_ans = 0;
    // TODO: Replace this with actual problem logic based on n_val and other inputs.

    // --- Example: Print output for a single test case ---
    // print(current_ans);
    // TODO: Print the computed answer, e.g., `print(result);`
}
```

For our "sum of two numbers" problem, you'll modify `solve()` like this:

```cpp
void solve()
{
    int a, b; // Declare two integer variables
    read(a, b); // Read two numbers from input and store them in 'a' and 'b'
                // 'read' is a helper function from the template

    int sum = a + b; // Calculate their sum

    print(sum); // Print the sum to the output
                // 'print' is another helper function
}
```

### 4. Understanding `main()`

The `main()` function is the entry point of your program. This template's `main()` is set up to handle multiple test cases, a common format in CP.

```cpp
int main()
{
    FASTINOUT; // Speeds up input/output
    int t;
    read(t); // Reads the number of test cases

    while (t--) // Loop 't' times
        solve(); // Call your solve() function for each test case
    return 0;
}
```

If a problem has only one test case, you can still use this structure. Just provide `1` as the first line of your input.

### 5. Compiling Your Code

"Compiling" means turning your human-readable C++ code into a machine-executable program (an `.exe` file on Windows).

Open a terminal in the `c:\Coding\CP-Template` directory.
Run the following command:

```powershell
g++ -std=c++20 -O2 -Wall template.cpp -o template.exe
```

- `g++`: The compiler.
- `-std=c++20`: Use the C++20 standard.
- `-O2 -Wall`: Optimization and warning flags (good practice).
- `template.cpp`: Your source code file.
- `-o template.exe`: Name the output executable `template.exe`.

If there are no errors, `template.exe` will be created.

### 6. Running Your Code

#### Method 1: Using `input.txt` (Recommended for Practice)

1.  Open `input.txt`.
2.  For our sum problem, if there's 1 test case and the numbers are 5 and 10:
    ```
    1
    5 10
    ```
    If there are 2 test cases, e.g., (5, 10) and (3, 7):
    ```
    2
    5 10
    3 7
    ```
3.  In the terminal, run:
    ```powershell
    .\template.exe < input.txt
    ```
    This command runs your program and tells it to read its input from `input.txt`.
    The output will be:
    ```
    15
    10
    ```

#### Method 2: Interactive Input (Less Common for CP)

You can also run it and type input directly:

```powershell
.\template.exe
```

The program will wait. Type:

```
1
5 10
```

And press Enter after each line. It will then print `15`.

### 7. Build Modes and Debugging

The template has different "modes":

- **Contest Mode (Default):** Lean and fast for submissions.
  ```powershell
  g++ -std=c++20 -O2 -Wall template.cpp -o template.exe
  ```
- **Practice/Local Debug Mode:** Enables helpful debugging messages.
  Compile with `-DPRACTICE -DLOCAL`:
  ```powershell
  g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL template.cpp -o template_debug.exe
  ```
  Now, if you use `TRACE(...)` or `DEBUG(...)` macros in your `solve()` function, they will print information to the error stream (usually your terminal, separate from the main output).
  Example:
  ```cpp
  void solve() {
      int a, b;
      read(a, b);
      TRACE("Read a:", a, "b:", b); // This will print if compiled with -DLOCAL -DPRACTICE
      int sum = a + b;
      DEBUG(sum); // So will this
      print(sum);
  }
  ```
  When you run `.\template_debug.exe < input.txt`, you'll see your `TRACE` and `DEBUG` messages in the terminal, which helps you understand what your code is doing. These messages are automatically disabled in contest mode.

### 8. Key Template Features (Brief Overview)

As you get more comfortable, explore these:

- **Type Aliases (Lines 25-47):**
  - `ll` for `long long`, `vi` for `vector<int>`, `pii` for `pair<int, int>`. These save typing.
- **Constants (Lines 50-57):**
  - `MOD` (for modular arithmetic), `INF` (infinity), `NL` (newline), `SPACE`.
- **Modular Arithmetic (`ModularOps` struct, Lines 61-99):**
  - For problems involving large numbers where you need results modulo a specific number (e.g., `10^9 + 7`).
  - Usage: `Mint::add(a,b)`, `Mint::power(base, exp)`. `Mint` uses the default `MOD`.
- **Macros (Lines 110-127):**
  - `f(i, s, e)`: for loop.
  - `all(v)`: gets iterators for a whole vector (e.g., `sort(all(my_vector))`).
  - `sz(v)`: size of a container.
  - `YES`, `NO`: print "YES" or "NO" with a newline.
- **Input/Output Helpers (Lines 220-248):**
  - `read(...)`: Reads various types, including multiple arguments (`read(a,b,c)`).
  - `print(...)`: Prints various types, with spaces between multiple arguments and a newline at the end for single arguments or the last in a variadic call.
  - `printv(vector)`: Prints elements of a vector separated by spaces, then a newline. (You can rename this to `print` too, C++ overloading handles it).

### 9. Solving a New Problem

1.  **Copy `template.cpp`** to a new file, e.g., `problem_X.cpp`.
2.  **Modify the `solve()` function** in `problem_X.cpp` with your logic.
3.  **Compile `problem_X.cpp`**:
    ```powershell
    g++ -std=c++20 -O2 -Wall problem_X.cpp -o problem_X.exe
    ```
4.  **Test** with `input.txt`:
    ```powershell
    .\problem_X.exe < input.txt
    ```

### 10. What About `test.sh` and `generate_input.py`? (Advanced)

These are for "stress testing." Sometimes your code works for simple cases but fails on tricky or large inputs.

- `generate_input.py`: A Python script you customize to create many random test inputs according to the problem's constraints.
- `test.sh`: A script (for Linux-like terminals, e.g., Git Bash on Windows, or WSL) that:
  1.  Compiles your C++ solution.
  2.  (Optionally) Compiles a "brute-force" solution (a simple, correct, but slow solution).
  3.  Runs your solution and the brute-force solution on many inputs generated by `generate_input.py`.
  4.  Compares their outputs. If they differ, it means your main solution has a bug, and it shows you the input that caused the issue.

This is a powerful technique for finding bugs. You'll learn to use this as you tackle harder problems. For now, focus on `template.cpp` and `input.txt`.

## Tips for Beginners

- **Start Simple:** Don't try to understand the whole template at once. Focus on `solve()`, `read()`, and `print()`.
- **Practice:** The more problems you solve, the more familiar you'll become.
- **Debug:** Use `TRACE` and `DEBUG` (compile with `-DPRACTICE -DLOCAL`) when your code doesn't work. Print variable values at different stages.
- **Read Problem Statements Carefully:** Misunderstanding the problem is a common mistake.
- **Ask for Help:** If you're stuck, online CP communities are great resources.

This template is a powerful tool. As you grow in CP, you'll appreciate more of its features. Good luck, and have fun coding!
