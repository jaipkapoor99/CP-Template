#include <bits/stdc++.h>
using namespace std;

#define FASTINOUT                \
    ios::sync_with_stdio(false); \
    cin.tie(NULL);               \
    cout.tie(NULL);

/* TYPES  */
#define ll long long
#define ld long double
#define pll pair<ll, ll>
#define tll tuple<ll, ll, ll>
#define vll vector<ll>
#define vvll vector<vll>
#define vpll vector<pll>
#define vb vector<bool>
#define vvb vector<vb>
#define vtll vector<tll>
#define sll set<ll>
#define vi vector<int>
#define vvi vector<vi>
#define mii map<int, int>
#define mll map<ll, ll>
#define si set<int>
#define pii pair<int, int>
#define vpii vector<pii>
#define tii tuple<int, int, int>
#define vtii vector<tii>
#define vvpll vector<vpll>
#define vvi vector<vi>
#define sc set<char>
#define vvpii vector<vpii>

/* FUNCTIONS */
#define endl '\n'
#define f(i, s, e) for (ll i = s; i < e; i++)
#define cf(i, s, e) for (ll i = s; i <= e; i++)
#define rf(i, e, s) for (ll i = e - 1; i >= s; i--)
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define forV(v) for (auto &e : v)
#define forM(m) for (auto &[key, value] : m)
#define newline cout << '\n'
#define space ' '

#define MOD 1000000007
#define MOD1 998244353

void printLine(auto... args) { ((cout << args << space), ...) << endl; }
void read(auto &...args) { (cin >> ... >> args); }
template <typename T>
T getMod(T a, T m = MOD)
{
    T ans = a % m;
    if (ans < 0)
        ans += m;
    return ans;
}
template <typename T>
void print(T n, char ch = endl) { cout << n << ch; }
template <typename T>
void inpVec(vector<T> &v) { forV(v) read(e); }
template <typename T, typename U>
void inpPair(pair<T, U> &a) { read(a.first, a.second); }
template <typename T, typename U>
void inpPairVec(vector<pair<T, U>> &a) { forV(a) inpPair(e); }
template <typename T>
void printVec(vector<T> &v)
{
    forV(v) print(e, space);
    newline;
}
template <typename T, typename U>
void printPair(pair<T, U> &a) { printLine(a.first, a.second); }
template <typename T>
bool odd(T n) { return n & 1; }
template <typename T>
void toMax(T &a, T b) { a = max(a, b); }
template <typename T>
void toMin(T &a, T b) { a = min(a, b); }
template <typename T>
bool coPrime(T a, T b) { return gcd(a, b) == 1; }
template <typename T>
T ceilDiv(T a, T b) { return (a + b - 1) / b; }
void yes() { print("YES"); }
void no() { print("NO"); }

template <typename T>
bool isDivisible(T n, T i) { return not getMod(n, i); }
template <typename T>
T modMul(T a, T b, T mod = MOD) { return getMod(a * b, mod); }
template <typename T>
T modAdd(T a, T b, T mod = MOD) { return getMod(a + b, mod); }
template <typename T>
T modSub(T a, T b, T mod = MOD) { return getMod(a - b + mod, mod); }
template <typename T, typename U>
vector<pair<T, U>> mapToVecPair(const map<T, U> &m)
{
    vector<pair<T, U>> v;
    forV(m) v.push_back(e);
    return v;
}
template <typename T>
T gcdExtended(T a, T b, T &x, T &y)
{
    if (not a)
    {
        x = 0, y = 1;
        return b;
    }
    T x1, y1;
    T gcd = gcdExtended(getMod(b, a), a, x1, y1);
    x = y1 - (b / a) * x1, y = x1;
    return gcd;
}
template <typename T>
T modInverse(T b, T m = MOD)
{
    T x, y;
    T g = gcdExtended(b, m, x, y);
    return getMod(getMod(x, m) + m, m);
}
template <typename T>
T modDivide(T a, T b, T m = MOD) { return getMod(modInverse(b) * getMod(a, m), m); }
template <typename T>
bool prime(T a)
{
    if (a == 1)
        return false;
    cf(i, 2, sqrtl(a)) if (isDivisible(a, i)) return false;
    return true;
}
template <typename T>
bool perfectSquare(T n) { return ceil((long double)sqrtl(n)) == floor((long double)sqrtl(n)); }
template <typename T>
T sumOfNNaturalNumbers(T n) { return n * (n + 1) / 2ll; }
template <typename T>
T lcm(T a, T b) { return (a * b) / gcd(a, b); }

void solve()
{
}

int main()
{
    FASTINOUT
    int t{1};
    read(t);
    while (t--)
        solve();
}