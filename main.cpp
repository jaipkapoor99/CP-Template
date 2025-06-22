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

#include "include/cp_utils.hpp" // Core utilities, macros, and type aliases

// The main cp_utils.hpp includes <bits/stdc++.h>, debug_utils.hpp, and other necessary headers.
// It also brings in `using namespace std;` and `using namespace __gnu_pbds;`.

// ═══════════════════════ SOLVE FUNCTION ═══════════════════════
//  Your main code lives here.
//  This function handles a single test case: reads input, computes, and prints output
void solve(int test_case_num) // Added test_case_num parameter
{
    DEBUG_SECTION("🎯 SOLVING TEST CASE #" + to_string(test_case_num));
    DEBUG_FUNC();
    TIMER_START(solve_time);
    
    // --- Example: Read input for a single test case ---
    int n;
    read(n); // read is from cp_utils.hpp
    
    TRACE("Test Case #", test_case_num, "Input n:", n);
    DEBUG_VAR(n);
    
    // Input validation
    if (n <= 0) {
        WARNING("Invalid input: n should be positive");
        print(0);
        return;
    }
    
    if (n > 1000000) {
        INFO("Large input detected, using optimized calculation");
    }
    
    // --- Example: Compute answer for a single test case ---
    // Sum 1 to n using formula: n*(n+1)/2
    ll result = (ll)n * (n + 1) / 2;
    DEBUG("Formula calculation: n*(n+1)/2 =", n, "*", (n+1), "/ 2 =", result);
    
    // --- PRACTICE Block: Compare with brute-force solution ---
#ifdef PRACTICE
    DEBUG_SECTION("🔍 VERIFICATION PHASE");
    TIMER_START(brute_force);
    
    // Internal brute force check using the formula vs loop
    ll brute_result = 0;
    INFO("Running brute-force verification...");
    
    // Show progress for larger inputs
    int progress_step = max(1, n / 10);
    for (int i = 1; i <= n; i++) {
        brute_result += i;
        if (i % progress_step == 0 || i == n) {
            PROGRESS(i, n);
        }
    }
    
    TIMER_END(brute_force);
    
    DEBUG("Brute force result:", brute_result);
    DEBUG("Formula result:", result);
    
    if (result == brute_result) {
        SUCCESS("Formula matches brute force! ✓");
    } else {
        TEST_FAIL("Formula vs Brute Force");
    }
    
    ASSERT(result == brute_result, "Formula result doesn't match brute force loop!");
#endif

    // --- Example: Print output for a single test case ---
    DEBUG("Final answer:", result);
    TIMER_END(solve_time);
    print(result);
}

// ══════════════════════════ MAIN ══════════════════════════════════
int main()
{
    FASTINOUT; // From cp_utils.hpp
    
    // Colorful header for the program
    DEBUG_SECTION("🚀 COMPETITIVE PROGRAMMING SOLUTION RUNNER");
    INFO("Initializing solution execution environment...");
    TRACE("Program started with enhanced debug mode");
    
    TIMER_START(total_execution);
    
    int t;
    read(t);
    DEBUG_VAR(t);
    
    if (t <= 0) {
        WARNING("No test cases to process");
        return 0;
    }
    
    if (t > 100) {
        INFO("Large number of test cases detected");
    }
    
    SUCCESS("Successfully read " + to_string(t) + " test cases");
    
    // Process each test case with visual progress
    f(i, 0, t) {
        if (t > 1) {
            PROGRESS(i + 1, t);
        }
        solve(i + 1);
    }
    
    TIMER_END(total_execution);
    
    DEBUG_SECTION("🏁 EXECUTION SUMMARY");
    SUCCESS("All test cases processed successfully!");
    INFO("Program execution completed");
    
    return 0;
}

/*
══════════════════════════════════════════════════════════════════════════════
HOW TO USE THIS TEMPLATE
══════════════════════════════════════════════════════════════════════════════

**Project Structure:**
- `main.cpp`: Contains `main()` and `solve()` functions. Includes `cp_utils.hpp`.
- `cp_utils.hpp`: Contains core utilities, type aliases, macros, number theory, etc. Includes `debug_utils.hpp`.
- `debug_utils.hpp`: Contains `DEBUG`, `ASSERT`, `TRACE` macros and helpers.
- `combine.sh`: Script to generate a single `submission_main.cpp` file for online judges.
- `test.sh`: Script for stress testing `main.cpp`.

**For local debugging (full features with colorful output):**
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

**Using with CodeRunner (Windows/MinGW):**
    Configure CodeRunner with the following command:
    g++ -std=c++20 -Wall -O2 -DPRACTICE -DLOCAL $fileName -o $fileNameWithoutExt.exe; if ($?) { Get-Content input.txt | ./$fileNameWithoutExt.exe > output.txt }
    
    This will:
    - Compile with full debug/practice features enabled
    - Read test cases from input.txt 
    - Output results to output.txt
    - Show colorful debug messages in console

**Enhanced Debug Features:**
    - 🐛 DEBUG(): Beautiful formatted debug output with timestamps
    - 🔍 TRACE(): Lightweight tracing with timestamps
    - ✅ SUCCESS(): Green success messages
    - ⚠️  WARNING(): Yellow warning messages  
    - ℹ️  INFO(): Blue informational messages
    - 💥 ASSERT(): Enhanced assertion failures with visual impact
    - 📈 PROGRESS(): Progress tracking for loops
    - 🏷️  DEBUG_SECTION(): Visual section separators
    - ⏱️  TIMER_START/END(): Performance timing
    - 📊 DEBUG_VAR(): Variable name and value display
    - 🚀 DEBUG_FUNC(): Function entry logging

══════════════════════════════════════════════════════════════════════════════
Features:
- Modern C++20 with enhanced colorful debugging system.
- Modular Design: 
    - `main.cpp` for problem logic.
    - `cp_utils.hpp` for general CP utilities.
    - `debug_utils.hpp` for enhanced debugging tools.
- Comprehensive Macros, Type Aliases, Advanced Debugging, Utility Functions,
  Modular Arithmetic, Timer, Number Theory, Practice Mode, Build Profiles, CPH Compatibility
  (Most features are now in cp_utils.hpp and debug_utils.hpp).
- Beautiful terminal output with colors, emojis, progress bars, and timing information.
*/ 
