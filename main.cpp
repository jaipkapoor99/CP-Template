/*
  Jai Kapoor – Universal C++20 Competitive Programming Template
  Full support for PRACTICE mode, DEBUG color, brute-force helpers, and stress testing.

  ───── Build Modes ─────
  - PRACTICE + LOCAL: Full power (DEBUG/TRACE/ASSERT/brute)
      g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o my
      (Compiler implicitly finds cp_utils.hpp and debug_utils.hpp via includes)
  - PRACTICE only: Stress testing (brute, ASSERT, no debug spam)
      g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o my
  - Contest: Lean, safe for submission (use combined file from ./combine.sh)
      g++ -std=c++20 -O2 -Wall -DONLINE_JUDGE submission_main.cpp -o submit
*/

#include "cp_utils.hpp" // Core utilities, macros, and type aliases

// The main cp_utils.hpp includes <bits/stdc++.h>, debug_utils.hpp, and other necessary headers.
// It also brings in `using namespace std;` and `using namespace __gnu_pbds;`.

// ────────────── EXAMPLE BRUTE SOLVER (edit per task) ──────────────
//  Only enabled in PRACTICE builds, never contest.
#ifdef PRACTICE
ll solve_brute_example(int n_param /*, const vll& a_param if needed */) // Example signature
{
    // Replace with your own O(N^3)/brute solution.
    // TODO: Implement your brute-force logic here.
    ll ans = 0;
    // Example: cf(i, 1, n_param) ans += i;
    return ans;
}
#endif

// ───────────────── SOLVE FUNCTION ──────────────────────
//  Your main code lives here.
//  This function handles a single test case: reads input, computes, and prints output
void solve(int test_case_num) // Added test_case_num parameter
{
    // --- Example: Read input for a single test case ---
    int n;
    read(n); // read is from cp_utils.hpp
    // TRACE("Test Case #", test_case_num, "Input n:", n); // TRACE is from debug_utils.hpp (via cp_utils.hpp)
    // vll a(n); 
    // read(a);      

    // --- Example: Compute answer for a single test case ---
    // TODO: Replace this with actual problem logic.
    
    // --- PRACTICE Block: Compare with brute-force solution ---
#ifdef PRACTICE
    // TODO: Adjust the input to solve_brute_example if necessary
    // ll ref_ans = solve_brute_example(n /*, a if needed */);
    // ll actual_solution_ans = 0; // Replace with your actual solution variable
    // if (actual_solution_ans != ref_ans)
    // {
    //     TRACE("ASSERTION FAILED (Test Case #", test_case_num, "): Mismatch with brute force solution.");
    //     TRACE("Input (n):", n);
    //     // TRACE("Vector a:", a); 
    //     TRACE("Your Answer (actual_solution_ans):", actual_solution_ans);
    //     TRACE("Brute Force Answer (ref_ans):", ref_ans);
    //     ASSERT(actual_solution_ans == ref_ans, "Solution mismatch with brute force."); // ASSERT from debug_utils.hpp
    // }
    // else
    // {
    //     TRACE("PRACTICE (Test Case #", test_case_num, "): Brute force check passed for n: ", n, " ans: ", actual_solution_ans);
    // }
#endif

    // --- Example: Print output for a single test case ---
    // print(actual_solution_ans); // print is from cp_utils.hpp
    // TODO: Print the computed answer
}

// ────────────────────── MAIN ───────────────────────────
int main()
{
    FASTINOUT; // From cp_utils.hpp
    int t;
    read(t); 

    f(i, 0, t) // f is from cp_utils.hpp
        solve(i + 1);            
    return 0;
}

/*
─────────────────────────────────────────────────────────────
HOW TO USE THIS TEMPLATE
─────────────────────────────────────────────────────────────

**Project Structure:**
- `main.cpp`: Contains `main()` and `solve()` functions. Includes `cp_utils.hpp`.
- `cp_utils.hpp`: Contains core utilities, type aliases, macros, number theory, etc. Includes `debug_utils.hpp`.
- `debug_utils.hpp`: Contains `DEBUG`, `ASSERT`, `TRACE` macros and helpers.
- `combine.sh`: Script to generate a single `submission_main.cpp` file for online judges.
- `test.sh`: Script for stress testing `main.cpp`.

**For local debugging (full features):**
    g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o my 
    (Compiler implicitly finds cp_utils.hpp and debug_utils.hpp via includes in main.cpp)
    ./my < input.txt

**For stress testing (assert/brute only, no debug spam):**
    g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o my
    ./test.sh   # (or ./test.sh <num_tests>)

**To generate a single file for submission (e.g., submission_main.cpp):**
    ./combine.sh main.cpp 
    (This will use main.cpp as input. The combine.sh script is designed to inline the content
     of the primary header included by main.cpp, which is cp_utils.hpp. Since cp_utils.hpp
     includes debug_utils.hpp, all necessary code gets bundled.)

**For contest/online judge (using the combined submission_main.cpp):**
    g++ -std=c++20 -O2 -Wall -DONLINE_JUDGE submission_main.cpp -o submit

**Using with Competitive Programming Helper (CPH) like extensions:**
    Configure CPH to use `main.cpp` as the main file. 
    The `solve()` function is identified for test case execution.

─────────────────────────────────────────────────────────────
Features:
- Modern C++20.
- Modular Design: 
    - `main.cpp` for problem logic.
    - `cp_utils.hpp` for general CP utilities.
    - `debug_utils.hpp` for debugging tools.
- Comprehensive Macros, Type Aliases, Advanced Debugging, Utility Functions,
  Modular Arithmetic, Timer, Number Theory, Practice Mode, Build Profiles, CPH Compatibility
  (Most features are now in cp_utils.hpp and debug_utils.hpp).
*/ 