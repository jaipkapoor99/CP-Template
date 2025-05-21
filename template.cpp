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
#include <bits/extc++.h>
#include <ranges>
#include <bit>
#include <numbers>
#include <span>
#include <chrono>
#include <random>
#include <source_location>
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
constexpr double PI = std::numbers::pi;
constexpr ll INF = 1e18;
constexpr int INF32 = 1e9;

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
#define endl NL
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
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
template <typename... Args>
void dbg(const std::source_location loc, Args &&...args)
{
    cerr << BLUE << "[" << loc.file_name() << ':' << loc.line() << "] " << RESET;
    ((cerr << RED << args << RESET << " | "), ...);
    cerr << NL;
}
#define DEBUG(...) dbg(std::source_location::current(), __VA_ARGS__)
#else
#define DEBUG(...)
#endif

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
template <typename T>
void read(T &x) { cin >> x; }
template <typename T, typename... Args>
void read(T &first, Args &...args)
{
    cin >> first;
    read(args...);
} // Variadic read
template <typename T>
void read(vector<T> &v)
{
    for (T &x : v)
        cin >> x;
}
template <typename T>
void print(const T &x) { cout << x << NL; } // Added generic print
template <typename T, typename... Args>
void print(const T &first, const Args &...args)
{
    cout << first << SPACE;
    print(args...);
} // Variadic print
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
ll solve_brute_example(int n)
{
    // Replace with your own O(N^3)/brute solution.
    ll ans = 0;
    cf(i, 1, n) ans += i;
    return ans;
}
#endif

// ───────────────── SOLVE FUNCTION ──────────────────────
//  Your main code lives here. Insert brute/ASSERT/TRACE as needed.
//  For contest problems, write clean solution, then wrap brute checks in PRACTICE blocks.
void solve()
{

#ifdef PRACTICE
    ll ref = solve_brute_example(n);
    ASSERT(ans == ref, "mismatch with brute");
#endif
}

// ────────────────────── MAIN ───────────────────────────
int main()
{
    FASTINOUT;
    int t = 1;
#ifndef PRACTICE
    read(t); // For stress-test, t=1 by default
#endif
    while (t--)
        solve();
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

─────────────────────────────────────────────────────────────
Features:
- PRACTICE enables brute/ASSERT/TRACE blocks for bug-proofing
- DEBUG gives color, context, and file/line info on-demand
- Template aliases and macros match modern CP/DSA standards
- Timer utility for self-benchmarking
- All extras vanish in contest builds for safety

Edit `solve_brute_example()` per problem to check tricky cases!
*/