// C++20 CP Template

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

// ------------------------------------
// Type Aliases
// ------------------------------------
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
template<typename T> using pqg = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using pql = priority_queue<T>;
template<typename T> using os = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename K, typename V> using omap = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> using uset = unordered_set<T>;
template<typename K, typename V> using umap = unordered_map<K, V>;

// ------------------------------------
// Constants
// ------------------------------------
constexpr int MOD = 1'000'000'007;
constexpr int MOD1 = 998'244'353;
constexpr char SPACE = ' ';
constexpr char NL = '\n';
constexpr double EPS = 1e-9;
constexpr double PI = std::numbers::pi;
constexpr ll INF = 1e18;
constexpr int INF32 = 1e9;

// ------------------------------------
// Fast Input/Output
// ------------------------------------
#define FASTINOUT ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

// ------------------------------------
// Macros
// ------------------------------------
#define f(i, s, e)      for (ll i = (s); i < (e); ++i)
#define cf(i, s, e)     for (ll i = (s); i <= (e); ++i)
#define rf(i, e, s)     for (ll i = (e) - 1; i >= (s); --i)
#define all(v)          (v).begin(), (v).end()
#define rall(v)         (v).rbegin(), (v).rend()
#define sz(v)           ((ll)(v).size())
#define pb              push_back
#define eb              emplace_back
#define fi              first
#define se              second
#define YES             cout << "YES" << NL
#define NO              cout << "NO" << NL
#define endl            NL
#define UNIQUE(v)       sort(all(v)), v.erase(unique(all(v)), v.end())
#define forV(v)         for (auto& e : (v))
#define forM(m)         for (auto& [key, value] : (m))

// C++20 Ranges helpers
namespace ranges = std::ranges;
namespace views = std::views;
#define FORR(v)         for (auto&& e : (v | views::reverse))
#define TRANS(v, op)    for (auto&& e : (v | views::transform(op)))

// ------------------------------------
// Policy-based Data Structures (PBDS)
// ------------------------------------
// Usage: os<int> s; s.insert(5); s.order_of_key(5);
// *s.find_by_order(0);

// ------------------------------------
// Random Generator
// ------------------------------------
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand_ll(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }

// ------------------------------------
// Custom Hash for Unordered Containers
// ------------------------------------
struct custom_hash {
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(ull x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T>
using safe_unordered_set = unordered_set<T, custom_hash>;
template<typename K, typename V>
using safe_unordered_map = unordered_map<K, V, custom_hash>;

// ------------------------------------
// Bit Manipulation (C++20)
// ------------------------------------
template<typename T> constexpr bool is_pow2(T x) { return std::has_single_bit(x); }
template<typename T> constexpr int popcnt(T x) { return std::popcount(x); }
template<typename T> constexpr int lsb(T x) { return std::countr_zero(x); }
template<typename T> constexpr int msb(T x) { return std::bit_width(x) - 1; }

// ------------------------------------
// Debugging (source_location, colorized, powerful)
// ------------------------------------
#ifdef LOCAL
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
template<typename... Args>
void dbg(const std::source_location loc = std::source_location::current(), Args&&... args) {
    cerr << BLUE << "[" << loc.file_name() << ":" << loc.line() << " " << loc.function_name() << "] " << RESET;
    ((cerr << RED << args << RESET << " | "), ...);
    cerr << '\n';
}
#define DEBUG(...) dbg(std::source_location::current(), __VA_ARGS__)
#else
#define DEBUG(...)
#endif

// ------------------------------------
// Timer Utility
// ------------------------------------
class Timer {
    chrono::high_resolution_clock::time_point st;
public:
    Timer() : st(chrono::high_resolution_clock::now()) {}
    void reset() { st = chrono::high_resolution_clock::now(); }
    ll elapsed() const {
        return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - st).count();
    }
};

// ------------------------------------
// Input/Output Helpers (C++20 span/tuple, variadic)
// ------------------------------------
template<typename... Ts>
istream& operator>>(istream& is, tuple<Ts...>& t) {
    apply([&is](auto&... args){ ((is >> args), ...); }, t);
    return is;
}
template<typename... Ts>
ostream& operator<<(ostream& os, const tuple<Ts...>& t) {
    apply([&os](const auto&... args){ size_t n = 0; ((os << (n++ ? SPACE : "") << args), ...); }, t);
    return os;
}
template<typename T>
istream& operator>>(istream& is, span<T> v) { for (auto& x : v) is >> x; return is; }
template<typename T>
ostream& operator<<(ostream& os, span<const T> v) { for (size_t i = 0; i < v.size(); ++i) os << (i ? SPACE : "") << v[i]; return os; }

// ------------------------------------
// Modular Arithmetic (class for reusability)
// ------------------------------------
template<int MOD>
struct Mint {
    int v;
    Mint(ll _v = 0) : v(norm(_v)) {}
    static int norm(ll x) { x %= MOD; if (x < 0) x += MOD; return x; }
    Mint operator + (const Mint& b) const { return v + b.v; }
    Mint operator - (const Mint& b) const { return v - b.v + MOD; }
    Mint operator * (const Mint& b) const { return 1LL * v * b.v; }
    Mint pow(ll p) const {
        Mint a = *this, r = 1;
        while (p) { if (p & 1) r = r * a; a = a * a; p >>= 1; }
        return r;
    }
    Mint inv() const { return pow(MOD - 2); }
    Mint operator / (const Mint& b) const { return *this * b.inv(); }
    Mint& operator+=(const Mint& b) { v = norm(v + b.v); return *this; }
    Mint& operator-=(const Mint& b) { v = norm(v - b.v); return *this; }
    Mint& operator*=(const Mint& b) { v = norm(1LL * v * b.v); return *this; }
    Mint& operator/=(const Mint& b) { return *this *= b.inv(); }
    friend ostream& operator<<(ostream& os, const Mint& m) { return os << m.v; }
    friend istream& operator>>(istream& is, Mint& m) { ll x; is >> x; m = Mint(x); return is; }
};

// ------------------------------------
// Read/Print Helpers (Variadic)
// ------------------------------------
template<typename T>
void read(T& x) { cin >> x; }
template<typename T, typename... Args>
void read(T& x, Args&... args) { read(x); read(args...); }
template<typename T>
void print(const T& x) { cout << x << NL; }
template<typename T, typename... Args>
void print(const T& x, const Args&... args) { cout << x << SPACE; print(args...); }
template<typename T>
void printv(const vector<T>& v) { for (auto &x : v) cout << x << SPACE; cout << NL; }

// ------------------------------------
// Math Utilities (add your own as needed)
// ------------------------------------
template<typename T>
T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
template<typename T>
T lcm(T a, T b) { return a / gcd(a, b) * b; }
template<typename T>
T ceildiv(T a, T b) { return (a + b - 1) / b; }
template<typename T>
bool is_prime(T n) { if (n <= 1) return false; for (T i = 2; i * i <= n; ++i) if (n % i == 0) return false; return true; }
// ... (add more as you need)

// ------------------------------------
// Main Solve Function
// ------------------------------------
void solve() {
    // Example usage:
    // int n; read(n);
    // vi a(n); read(a);
    // DEBUG(n, a);
    // printv(a);
}

// ------------------------------------
// Main
// ------------------------------------
int main() {
    FASTINOUT;
    int t = 1;
    read(t);
    while (t--) solve();
    return 0;
}