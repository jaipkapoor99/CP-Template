#ifndef CP_UTILS_HPP
#define CP_UTILS_HPP

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // For PBDS
#include <ext/pb_ds/tree_policy.hpp>     // For PBDS
#include <ranges>
#include <bit>
#include <span>
#include <chrono>
#include <random>
#include <numbers> // For std::numbers::pi, ensure fallback if not C++20

#include "debug_utils.hpp" // Include the debug header

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
constexpr int MOD_CONST = 1'000'000'007; // Renamed to avoid conflict if MOD is a macro elsewhere
constexpr int MOD1_CONST = 998'244'353;  // Renamed
#define SPACE ' '
#define NL '\n' // Corrected from ' ' to '\n'
constexpr double EPS = 1e-9;

#if __cplusplus >= 202002L && defined(__cpp_lib_numbers)
constexpr double PI = std::numbers::pi;
#else
constexpr double PI = 3.14159265358979323846;
#endif

constexpr ll INF = 1e18;
constexpr int INF32 = 1e9;

// ────────────── MODULAR ARITHMETIC ─────────────────
template <ll Modulus>
struct ModularOps
{
    static_assert(Modulus > 0, "Modulus must be positive.");

    static ll normalize(ll a)
    {
        return (a % Modulus + Modulus) % Modulus;
    }

    static ll add(ll a, ll b)
    {
        return normalize(a + b);
    }

    static ll sub(ll a, ll b)
    {
        return normalize(a - b);
    }

    static ll mul(ll a, ll b)
    {
        return normalize(a * b);
    }

    static ll power(ll base, ll exp)
    {
        ll res = 1;
        base = normalize(base);
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
        return power(n, Modulus - 2);
    }

    static ll div(ll a, ll b)
    {
        return mul(a, inv(b));
    }
};

using Mint = ModularOps<MOD_CONST>;
using Mint1 = ModularOps<MOD1_CONST>;

// ──────────────── FAST INPUT/OUTPUT ────────────────────
#define FASTINOUT                     \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr)

// ───────────────────── MACROS ──────────────────────────
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

// ───────────────── TIMER UTILITY ──────────────────────
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

// ───────────────── UTILITY FUNCTIONS ────────────────────
template <typename T_ref, typename... T_vals>
void maximise(T_ref &target, const T_vals &...vals)
{
    ((void)(target = std::max(target, vals)), ...);
}

template <typename T_ref, typename... T_vals>
void minimise(T_ref &target, const T_vals &...vals)
{
    ((void)(target = std::min(target, vals)), ...);
}

// ───────────────── DATA STRUCTURES ────────────────────
// Disjoint Set Union (DSU) / Union-Find
struct DSU {
    vi parent;
    vi set_size;
    int _num_sets;

    DSU(int n = 0) : parent(n), set_size(n, 1), _num_sets(n) {
        iota(all(parent), 0);
    }

    // Find the representative of the set containing x (with path compression)
    int find(int x) {
        ASSERT(x >= 0 && x < sz(parent), "DSU::find: Index out of bounds.");
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    // Unite the sets containing x and y (union by size)
    // Returns true if x and y were in different sets, false otherwise.
    bool unite(int x, int y) {
        ASSERT(x >= 0 && x < sz(parent) && y >= 0 && y < sz(parent), "DSU::unite: Index out of bounds.");
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (set_size[rootX] < set_size[rootY])
                swap(rootX, rootY);
            parent[rootY] = rootX;
            set_size[rootX] += set_size[rootY];
            _num_sets--;
            return true;
        }
        return false;
    }

    // Check if x and y are in the same set
    bool connected(int x, int y) {
        ASSERT(x >= 0 && x < sz(parent) && y >= 0 && y < sz(parent), "DSU::connected: Index out of bounds.");
        return find(x) == find(y);
    }

    // Get the size of the set containing x
    int size(int x) {
        ASSERT(x >= 0 && x < sz(parent), "DSU::size: Index out of bounds.");
        return set_size[find(x)];
    }

    // Get the number of disjoint sets
    int num_sets() const {
        return _num_sets;
    }

    // Reset the DSU to n disjoint sets.
    void reset(int n) {
        parent.assign(n, 0);
        iota(all(parent), 0);
        set_size.assign(n, 1);
        _num_sets = n;
    }

    // Add a new element as a new disjoint set.
    // Useful if the number of elements is not known at construction.
    void add_element() {
        parent.pb(sz(parent));
        set_size.pb(1);
        _num_sets++;
    }
};

// ────────────── EXAMPLE BRUTE SOLVER (edit per task) ──────────────
//  Only enabled in PRACTICE builds, never contest.
#ifdef PRACTICE
// Note: This function is intended to be defined by the user for each problem.
// It's placed in cp_utils.hpp for organizational purposes and to be bundled by combine.sh.
// The actual implementation will typically be problem-specific.
// The solve() function in main.cpp can then call this (conditionally, under #ifdef PRACTICE)
// to compare results.

// Example signature, modify as needed for the specific problem's input variables.
inline ll solve_brute_example(int n_param /*, const vll& a_param if needed */)
{
    // Replace with your own O(N^3)/brute solution for the current problem.
    // This is just a placeholder.
    // TODO: Implement your problem-specific brute-force logic here.
    ll ans = 0;
    // Example: cf(i, 1, n_param) ans += i;
    // TRACE("Brute force called with n_param:", n_param);
    // ASSERT(n_param < 1000, "Brute force input too large, might be slow.");
    return ans;
}
#endif

// ───────────────── NUMBER THEORY UTILITIES ────────────────────
// Note: These `mul` and `power` are specific to Miller-Rabin and use dynamic modulus.
// They are distinct from ModularOps::mul and ModularOps::power.
inline ll nt_mul(ll a, ll b, ll m)
{ // nt_ for number theory
    if (b == 0)
        return 0;
    unsigned __int128 res = (unsigned __int128)a * b;
    if (m == 0)
    {
        if (res == 0)
            return 0;
        return -1;
    }
    return res % m;
}

inline ll nt_power(ll base, ll exp, ll mod)
{ // nt_ for number theory
    ll res = 1;
    base = (base % mod + mod) % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = nt_mul(res, base, mod);
        base = nt_mul(base, base, mod);
        exp /= 2;
    }
    return res;
}

inline bool check_composite(ll n, ll a, ll d, int s)
{
    ll x = nt_power(a, d, n);
    if (x == 1 || x == n - 1)
    {
        return false;
    }
    f(r, 1, s)
    {
        x = nt_mul(x, x, n);
        if (x == n - 1)
        {
            return false;
        }
    }
    return true;
}

inline bool isPrime(ll n)
{
    if (n < 2)
        return false;
    ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    forV(bases)
    {
        if (n == e)
            return true;
    }
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }
    forV(bases)
    {
        if (check_composite(n, e, d, s))
        {
            return false;
        }
    }
    return true;
}

template <typename T1, typename T2>
bool isDivisible(T1 n, T2 divisor)
{
    if (divisor == 0)
    {
        return false;
    }
    return (n % divisor == 0);
}

template <typename T>
bool isOdd(T n)
{
    return !isDivisible(n, 2);
}

// ──────────── GENERIC INPUT/OUTPUT HELPERS ─────────────
template <typename T, typename... Args>
void read(T &first, Args &...args)
{
    cin >> first;
    ((void)(cin >> args), ...);
}

template <typename T>
void read(vector<T> &v)
{
    forV(v)
            cin >>
        e;
}

template <typename T, typename... Args>
void print(const T &first, const Args &...args)
{
    cout << first;
    ((cout << SPACE << args), ...);
    cout << NL;
}

template <typename T>
void printv(const vector<T> &v)
{
    forV(v)
            cout
        << e << SPACE;
    cout << NL;
}

#endif // CP_UTILS_HPP