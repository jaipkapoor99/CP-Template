#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// Fast Input/Output
// -----------------------------------------------------------------------------
#define FASTINOUT ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)

// -----------------------------------------------------------------------------
// Type Aliases
// -----------------------------------------------------------------------------
using ll    = long long;
using ld    = long double;
using pii   = pair<int, int>;
using pll   = pair<ll, ll>;
using tll   = tuple<ll, ll, ll>;
using vi    = vector<int>;
using vll   = vector<ll>;
using vb    = vector<bool>;
using vvb   = vector<vb>;
using vpii  = vector<pii>;
using vpll  = vector<pll>;
using vtll  = vector<tll>;
using vvll  = vector<vll>;
using vvpii = vector<vpii>;
using vvpll = vector<vpll>;
using mii   = map<int, int>;
using mll   = map<ll, ll>;
using si    = set<int>;
using sll   = set<ll>;
using sc    = set<char>;

// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------
constexpr int  MOD  = 1'000'000'007;
constexpr int  MOD1 = 998'244'353;
constexpr char SPACE = ' ';
constexpr char NL    = '\n';

// -----------------------------------------------------------------------------
// Loop Macros
// -----------------------------------------------------------------------------
#define f(i, s, e)    for (ll i = (s); i < (e); ++i)
#define cf(i, s, e)   for (ll i = (s); i <= (e); ++i)
#define rf(i, e, s)   for (ll i = (e) - 1; i >= (s); --i)
#define all(v)        (v).begin(), (v).end()
#define rall(v)       (v).rbegin(), (v).rend()
#define forV(v)       for (auto& e : (v))
#define forM(m)       for (auto& [key, value] : (m))
#define newline       cout << NL
#define space         SPACE

// -----------------------------------------------------------------------------
// Debugging Helpers (prints to stderr if LOCAL is defined)
// -----------------------------------------------------------------------------
#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
template<typename T>
void __print(const T &x) { cerr << x; }
template<typename T, typename U>
void __print(const pair<T, U> &x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const vector<T> &x) { cerr << '{'; for (auto &i : x) { __print(i); cerr << ' '; } cerr << '}'; }
template<typename T>
void __print(const set<T> &x) { cerr << '{'; for (auto &i : x) { __print(i); cerr << ' '; } cerr << '}'; }
template<typename T, typename U>
void __print(const map<T, U> &x) { cerr << '{'; for (auto &i : x) { __print(i); cerr << ' '; } cerr << '}'; }
template<typename... Args>
void debug_out(Args... args) { int n = 0; (void)initializer_list<int>{(__print(args), cerr << (++n == sizeof...(args) ? '\n' : " | "), 0)...}; }
#else
#define dbg(...)
#endif

// -----------------------------------------------------------------------------
// Input Helpers (overloaded 'read')
// -----------------------------------------------------------------------------
template<typename T>
void read(T& x) { cin >> x; }
template<typename T, typename U>
void read(pair<T, U>& p) { cin >> p.first >> p.second; }
template<typename T>
void read(vector<T>& v) { for (auto& x : v) read(x); }
template<typename T, typename U>
void read(vector<pair<T, U>>& v) { for (auto& x : v) read(x); }

// -----------------------------------------------------------------------------
// Output Helpers (overloaded 'print')
// -----------------------------------------------------------------------------
template<typename T>
void print(const T& x, char endc = NL) { cout << x << endc; }
template<typename T, typename U>
void print(const pair<T, U>& p, char endc = NL) { cout << p.first << SPACE << p.second << endc; }
template<typename T>
void print(const vector<T>& v, char sep = SPACE, char endc = NL) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << sep;
        cout << v[i];
    }
    cout << endc;
}
template<typename T, typename U>
void print(const vector<pair<T, U>>& v, char sep = SPACE, char endc = NL) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << sep;
        print(v[i], '\0');
    }
    cout << endc;
}

// Convenience
inline void yes() { cout << "YES" << NL; }
inline void no()  { cout << "NO" << NL; }

// -----------------------------------------------------------------------------
// Math and Utilities
// -----------------------------------------------------------------------------
template<typename T>
T getMod(T a, T m = MOD) { T ans = a % m; return (ans < 0) ? ans + m : ans; }
template<typename T>
bool odd(T n) { return n & 1; }
template<typename T>
bool isDivisible(T n, T i) { return getMod(n, i) == 0; }
template<typename T>
T modMul(T a, T b, T mod = MOD) { return getMod(a * b, mod); }
template<typename T>
T modAdd(T a, T b, T mod = MOD) { return getMod(a + b, mod); }
template<typename T>
T modSub(T a, T b, T mod = MOD) { return getMod(a - b + mod, mod); }
template<typename T>
T ceilDiv(T a, T b) { return (a + b - 1) / b; }
template<typename T>
void toMax(T &a, T b) { a = max(a, b); }
template<typename T>
void toMin(T &a, T b) { a = min(a, b); }
template<typename T>
bool coPrime(T a, T b) { return gcd(a, b) == 1; }
template<typename T>
T gcdExtended(T a, T b, T &x, T &y) {
    if (!a) { x = 0, y = 1; return b; }
    T x1, y1;
    T g = gcdExtended(getMod(b, a), a, x1, y1);
    x = y1 - (b / a) * x1, y = x1;
    return g;
}
template<typename T>
T modInverse(T b, T m = MOD) {
    T x, y;
    T g = gcdExtended(b, m, x, y);
    return getMod(getMod(x, m) + m, m);
}
template<typename T>
T modDivide(T a, T b, T m = MOD) { return getMod(modInverse(b) * getMod(a, m), m); }
template<typename T>
T modPow(T a, T b, T m = MOD) {
    T res = 1; a %= m;
    while (b) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m; b >>= 1;
    }
    return res;
}
template<typename T>
bool prime(T a) {
    if (a == 1) return false;
    cf(i, 2, sqrtl(a)) if (isDivisible(a, i)) return false;
    return true;
}
template<typename T>
bool perfectSquare(T n) { return ceil((long double)sqrtl(n)) == floor((long double)sqrtl(n)); }
template<typename T>
T sumOfNNaturalNumbers(T n) { return n * (n + 1) / 2ll; }
template<typename T>
T lcm(T a, T b) { return (a * b) / gcd(a, b); }
template<typename T, typename U>
vector<pair<T, U>> mapToVecPair(const map<T, U>& m) {
    vector<pair<T, U>> v;
    for (auto& e : m) v.push_back(e);
    return v;
}

// -----------------------------------------------------------------------------
// Problem Solver
// -----------------------------------------------------------------------------
void solve() {
    // Example usage:
    // int n; read(n);
    // vi a(n); read(a);
    // dbg(n, a); // for local debugging
    // print(a);
}

// -----------------------------------------------------------------------------
// Main
// -----------------------------------------------------------------------------
int main() {
    FASTINOUT;
    int t = 1;
    read(t);
    while (t--) solve();
    return 0;
}