/*
  Jai Kapoor – Universal C++20 Competitive Programming Template
  Full support for PRACTICE mode, DEBUG color, brute-force helpers, and stress testing.

  ───── Build Modes ─────
  - PRACTICE + LOCAL: Full power (DEBUG/TRACE/ASSERT/brute)
      g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o my
  - PRACTICE only: Stress testing (brute, ASSERT, no debug spam)
      g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o my
  - Contest: Lean, safe for submission
      g++ -std=c++20 -O2 -Wall main.cpp -o submit
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // For PBDS
#include <ext/pb_ds/tree_policy.hpp>     // For PBDS
#include <ranges>
#include <bit>
#include <span>
#include <chrono>
#include <random>
#include <source_location>
#include <filesystem> // Added for std::filesystem::path in DEBUG macro
using namespace std;
using namespace __gnu_pbds;

// ──────────────────── TYPE ALIASES ─────────────────────
//  Core types for rapid typing and template-based DS.
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vb = vector<bool>;
using vpii = vector<pii>;
using vpll = vector<pll>;
using vs = vector<string>;
using vd = vector<double>;
using vld = vector<long double>;
using dq = deque<int>;
template <typename T>
using pqg = std::priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using pql = std::priority_queue<T>;
template <typename T>
using os = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V>
using omap = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using uset = unordered_set<T>;
template <typename K, typename V>
using umap = unordered_map<K, V>;

// ──────────────────── CONSTANTS ────────────────────────
constexpr int MOD = 1'000'000'007;
constexpr int MOD1 = 998'244'353;
constexpr char SPACE = ' ';
constexpr char NL = '\n';
constexpr double EPS = 1e-9;

#if __cplusplus >= 202002L && defined(__cpp_lib_numbers)
#include <numbers> // Conditionally include <numbers>
constexpr double PI = std::numbers::pi;
#else
constexpr double PI = 3.14159265358979323846; // Fallback for PI with a literal
#endif

constexpr ll INF = 1e18;
constexpr int INF32 = 1e9;

// ────────────── MODULAR ARITHMETIC ─────────────────
//  Operations for modular arithmetic. Pass the modulus as a template parameter.
//  Assumes Modulus is a prime number for modular inverse.
template <ll Modulus>
struct ModularOps
{
    static_assert(Modulus > 0, "Modulus must be positive.");

    static ll add(ll a, ll b)
    {
        return (a + b) % Modulus;
    }

    static ll sub(ll a, ll b)
    {
        return (a - b % Modulus + Modulus) % Modulus;
    }

    static ll mul(ll a, ll b)
    {
        return (a * b) % Modulus;
    }

    static ll power(ll base, ll exp)
    {
        ll res = 1;
        base %= Modulus;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                res = mul(res, base);
            base = mul(base, base);
            exp /= 2;
        }
        return res;
    }

    static ll inv(ll n)
    {
        return power(n, Modulus - 2); // Fermat's Little Theorem
    }

    static ll div(ll a, ll b)
    {
        return mul(a, inv(b));
    }
};

// Example usage for the global MOD constant:
// using DefaultMint = ModularOps<MOD>;
// DefaultMint::add(a, b);

// Shorthand for common moduli
using Mint = ModularOps<MOD>;   // Default to MOD (10^9 + 7)
using Mint1 = ModularOps<MOD1>; // For 998244353
// Add more aliases as needed, e.g.:
// using Mint2 = ModularOps<1000000009>; // Another common prime

// ──────────────── FAST INPUT/OUTPUT ────────────────────
#define FASTINOUT                \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr)

// ───────────────────── MACROS ──────────────────────────
//  Most common CP patterns. Use sz(v), all(v), f(...) everywhere.
#define f(i, s, e) for (ll i = (s); i < (e); ++i)
#define cf(i, s, e) for (ll i = (s); i <= (e); ++i)
#define rf(i, e, s) for (ll i = (e) - 1; i >= (s); --i)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) ((ll)(v).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define YES cout << "YES" << NL
#define NO cout << "NO" << NL
#define UNIQUE(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define forV(v) for (auto &e : (v))
#define forM(m) for (auto &[key, value] : (m))

// ─────────── PRACTICE ASSERT/TRACE/BRUTE HOOKS ─────────
//  PRACTICE flag enables runtime asserts, tracing and brute solvers.
#ifdef PRACTICE
// ASSERT: crash-fast on invariants. Use e.g. ASSERT(x >= 0, "x nonnegative")
#define ASSERT(cond, msg)                                           \
    if (!(cond))                                                    \
    {                                                               \
        cerr << "ASSERT FAIL: " << (msg) << " @" << __LINE__ << NL; \
        exit(42);                                                   \
    }
// TRACE: handy logging for PRACTICE builds, toggle with -DLOCAL
#ifdef LOCAL
#define TRACE(...) dbg(std::source_location::current(), __VA_ARGS__)
#else
#define TRACE(...)
#endif
#else
#define ASSERT(cond, msg) ((void)0)
#define TRACE(...)
#endif

// ────────────── DEBUGGING (Color + Context) ────────────
//  Use DEBUG(a,b,v) to print state with file/line, colored, local only.
#ifdef LOCAL
#define RESET "\\033[0m"
#define RED "\\033[31m"
#define BLUE "\\033[34m"
#define GREEN "\\033[32m"
#else // LOCAL
#define RESET ""
#define RED ""
#define BLUE ""
#define GREEN ""
#endif // LOCAL

#ifdef LOCAL
// Helper for dbg to print pairs
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}

// Helper for dbg to print vectors
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}

// Recursive helper to print variadic arguments for dbg
template <typename T_arg, typename... Other_Args>
void _dbg_print_recursive(std::ostream &os, T_arg &&first, Other_Args &&...rest)
{
    os << std::forward<T_arg>(first);
    if constexpr (sizeof...(rest) > 0)
    {
        os << " "; // Add space before the next argument
        _dbg_print_recursive(os, std::forward<Other_Args>(rest)...);
    }
}

template <typename... Args>
void dbg(const std::source_location loc, Args &&...args)
{
    // Using std::filesystem::path for filename only.
    // Ensure <filesystem> is included (usually via <bits/stdc++.h> in C++20).
    // If this causes issues, it can be reverted to loc.file_name().
    std::cerr << RED << std::filesystem::path(loc.file_name()).filename().string()
              << ":" << loc.line()
              << " (" << loc.function_name() << ") "
              << BLUE << "DEBUG: " << RESET;
    if constexpr (sizeof...(args) > 0)
    {
        _dbg_print_recursive(std::cerr, std::forward<Args>(args)...);
    }
    std::cerr << RESET << std::endl; // Use std::endl for flushing and newline
}

#define DEBUG(...) dbg(std::source_location::current(), __VA_ARGS__)
#else // LOCAL
#define DEBUG(...)
#endif // LOCAL

// ───────────────── TIMER UTILITY ──────────────────────
//   For measuring time per phase (practice use).
class Timer
{
    chrono::high_resolution_clock::time_point st;

public:
    Timer() : st(chrono::high_resolution_clock::now()) {}
    void reset() { st = chrono::high_resolution_clock::now(); }
    ll elapsed() const
    {
        return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - st).count();
    }
};

// ──────────── GENERIC INPUT/OUTPUT HELPERS ─────────────
//  Rapid vector and variadic-style IO for hand-written and AI code.
template <typename T, typename... Args>
void read(T &first, Args &...args)
{
    cin >> first;
    if constexpr (sizeof...(args) > 0)
    {
        read(args...);
    }
} // Variadic read
template <typename T>
void read(vector<T> &v)
{
    for (T &x : v)
        cin >> x;
}

// Refactored variadic print function
template <typename T, typename... Args>
void print(const T &first, const Args &...args)
{
    cout << first;
    if constexpr (sizeof...(args) > 0)
    {
        cout << SPACE;
        print(args...); // Recursive call for remaining arguments
    }
    else
    {
        cout << NL; // Base case: last argument (or only argument), print newline
    }
}

template <typename T>
void printv(const vector<T> &v)
{
    for (const T &x : v)
        cout << x << SPACE;
    cout << NL;
}

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
    int n_val;
    read(n_val);
    // TRACE("Test Case #", test_case_num, "Input n_val:", n_val); // Example TRACE
    // vll a(n_val); // Example: if vector input is needed
    // read(a);      // Example: if vector input is needed

    // --- Example: Compute answer for a single test case ---
    ll current_ans = 0; // Placeholder for actual answer
    // TODO: Replace this with actual problem logic.
    // For example:
    // if (n_val > 0 && a[0] == 1) current_ans = 1; else current_ans = 0;

    // --- PRACTICE Block: Compare with brute-force solution ---
#ifdef PRACTICE
    // TODO: Adjust the input to solve_brute_example if necessary
    // ll ref_ans = solve_brute_example(n_val /*, a if needed */);
    // if (current_ans != ref_ans)
    // {
    //     TRACE("ASSERTION FAILED (Test Case #", test_case_num, "): Mismatch with brute force solution.");
    //     TRACE("Input (n_val):", n_val);
    //     // TRACE("Vector a:", a); // If using vector 'a'
    //     TRACE("Your Answer (current_ans):", current_ans);
    //     TRACE("Brute Force Answer (ref_ans):", ref_ans);
    //     ASSERT(current_ans == ref_ans, "Solution mismatch with brute force.");
    // }
    // else
    // {
    //     std::cerr << GREEN << std::filesystem::path(std::source_location::current().file_name()).filename().string()
    //               << ":" << std::source_location::current().line()
    //               << " (" << std::source_location::current().function_name() << ") "
    //               << BLUE << "DEBUG: " << RESET
    //               << GREEN << "PRACTICE (Test Case #" << test_case_num << "): Brute force check passed for n_val: " << n_val << " ans: " << current_ans << RESET << std::endl;
    // }
#endif

    // --- Example: Print output for a single test case ---
    // print(current_ans); // Or YES/NO based on current_ans
    // TODO: Print the computed answer, e.g., `print(result);` or `YES;`/`NO;`
}

// ────────────────────── MAIN ───────────────────────────
int main()
{
    FASTINOUT;
    int t;
    read(t); // Always read the number of test cases

    for (int i = 1; i <= t; ++i) // Loop from 1 to t to get test case number
        solve(i);                // Pass current test case number
    return 0;
}

/*
─────────────────────────────────────────────────────────────
HOW TO USE THIS TEMPLATE
─────────────────────────────────────────────────────────────

**For local debugging (full features):**
    g++ -std=c++20 -O2 -Wall -DPRACTICE -DLOCAL main.cpp -o my
    ./my < input.txt

**For stress testing (assert/brute only, no debug spam):**
    g++ -std=c++20 -O2 -Wall -DPRACTICE main.cpp -o my
    ./test.sh   # see shell script in prior messages

**For contest/online judge (clean, fast):**
    g++ -std=c++20 -O2 -Wall main.cpp -o submit

**Using with Competitive Programming Helper (CPH) like extensions:**
    This template is designed to be compatible with CPH. CPH typically
    identifies the `solve()` function and runs it for each test case.
    Ensure your logic within `solve()` handles a single test case
    (reads input, computes, prints output). The `main()` function in this
    template is for standalone execution or use with `test.sh`.

─────────────────────────────────────────────────────────────
Features:
- PRACTICE enables brute/ASSERT/TRACE blocks for bug-proofing
- DEBUG gives color, context, and file/line info on-demand
- Template aliases and macros match modern CP/DSA standards
- Timer utility for self-benchmarking
- All extras vanish in contest builds for safety

Edit `solve_brute_example()` per problem to check tricky cases!
*/