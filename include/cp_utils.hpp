#ifndef CP_UTILS_HPP
#define CP_UTILS_HPP

// ──────────────────── C++23 COMPATIBILITY CHECK ─────────────────────
#if __cplusplus < 202302L
#warning "This code is designed for C++23. Some features may not work correctly with older standards."
#endif

// ──────────────────── HEADER INCLUDES ─────────────────────
// Use bits/stdc++.h for competitive programming if available (GCC/Clang with libstdc++)
// Otherwise fall back to individual standard library includes
#if __has_include(<bits/stdc++.h>) && !defined(NO_BITS_STDC)
#include <bits/stdc++.h>
#else
// Individual includes for portability
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>
#endif

// C++23 specific headers (always try to include if available)
#if __cplusplus >= 202002L
#if __has_include(<ranges>)
#include <ranges>
#endif
#if __has_include(<bit>)
#include <bit>
#endif
#if __has_include(<span>)
#include <span>
#endif
#if __has_include(<concepts>)
#include <concepts>
#endif
#if __has_include(<compare>)
#include <compare>
#endif
#if __has_include(<format>)
#include <format>
#define HAS_FORMAT_LIB
#endif
#if __has_include(<numbers>)
#include <numbers>
#endif
#endif

// Always include these for competitive programming
#include <chrono>
#include <random>

// GNU PBDS (Policy-Based Data Structures) - only include if available
#if __has_include(<ext/pb_ds/assoc_container.hpp>)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define HAS_GNU_PBDS
#endif

#include "debug_utils.hpp" // Include the debug header

using namespace std;
#ifdef HAS_GNU_PBDS
using namespace __gnu_pbds;
#endif

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
#ifdef HAS_GNU_PBDS
template <typename T>
using os = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V>
using omap = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
#endif
template <typename T>
using uset = std::unordered_set<T>;
template <typename K, typename V>
using umap = std::unordered_map<K, V>;

// ──────────────────── CONSTANTS ────────────────────────
constexpr int MOD_CONST = 1'000'000'007; // Renamed to avoid conflict if MOD is a macro elsewhere
constexpr int MOD1_CONST = 998'244'353;  // Renamed
#define SPACE ' '
#define NL '\n' // Corrected from ' ' to '\n'
constexpr double EPS = 1e-9;

#if __cplusplus >= 202002L && __has_include(<numbers>)
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
#define pb emplace_back
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
#if __cplusplus >= 202002L
template <typename T_ref, typename... T_vals>
    requires (std::same_as<T_ref, T_vals> && ...)
void maximise(T_ref &target, const T_vals &...vals)
{
    ((void)(target = std::max(target, vals)), ...);
}

template <typename T_ref, typename... T_vals>
    requires (std::same_as<T_ref, T_vals> && ...)
void minimise(T_ref &target, const T_vals &...vals)
{
    ((void)(target = std::min(target, vals)), ...);
}
#else
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
#endif

// ───────────────── DATA STRUCTURES ────────────────────
// Disjoint Set Union (DSU) / Union-Find
struct DSU
{
    vi parent;
    vi set_size;
    int _num_sets;

    DSU(int n = 0) : parent(n), set_size(n, 1), _num_sets(n)
    {
        iota(all(parent), 0);
    }

    // Find the representative of the set containing x (with path compression)
    int find(int x)
    {
        ASSERT(x >= 0 && x < sz(parent), "DSU::find: Index out of bounds.");
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    // Unite the sets containing x and y (union by size)
    // Returns true if x and y were in different sets, false otherwise.
    bool unite(int x, int y)
    {
        ASSERT(x >= 0 && x < sz(parent) && y >= 0 && y < sz(parent), "DSU::unite: Index out of bounds.");
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
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
    bool connected(int x, int y)
    {
        ASSERT(x >= 0 && x < sz(parent) && y >= 0 && y < sz(parent), "DSU::connected: Index out of bounds.");
        return find(x) == find(y);
    }

    // Get the size of the set containing x
    int size(int x)
    {
        ASSERT(x >= 0 && x < sz(parent), "DSU::size: Index out of bounds.");
        return set_size[find(x)];
    }

    // Get the number of disjoint sets
    int num_sets() const
    {
        return _num_sets;
    }

    // Reset the DSU to n disjoint sets.
    void reset(int n)
    {
        parent.assign(n, 0);
        iota(all(parent), 0);
        set_size.assign(n, 1);
        _num_sets = n;
    }

    // Add a new element as a new disjoint set.
    // Useful if the number of elements is not known at construction.
    void add_element()
    {
        parent.pb(sz(parent));
        set_size.pb(1);
        _num_sets++;
    }
};

// Segment Tree with Lazy Propagation
// Default: Range Sum Query, Range Add Update
// To customize:
//    - T_val: data type for array elements and query results
//    - T_lazy: data type for lazy updates
//    - merge_op: how to combine results from child nodes (e.g., for sum, min, max)
//    - apply_lazy_to_node_op: how a lazy value affects a node's actual value (e.g., for range add sum: node_val += lazy_val * range_length)
//    - combine_lazy_op: how to combine new lazy update with existing lazy update on a node (e.g., for range add: existing_lazy += new_lazy)
//    - neutral_val: identity for merge_op (e.g., 0 for sum, INF for min)
//    - neutral_lazy: identity for lazy values (e.g., 0 for range add, or a special no-op marker)

template <typename T_val = ll, typename T_lazy = ll>
struct SegTreeLazy
{
    int n;                 // Size of the original array, leaves of the tree are at [n, 2n-1]
    vector<T_val> t;       // Segment tree values
    vector<T_lazy> lazy;   // Lazy propagation array
    T_val neutral_val;     // Neutral element for query merge operation
    T_lazy neutral_lazy;   // Neutral element for lazy updates (means no lazy update pending)
    vector<int> range_len; // Stores length of segment covered by each node, useful for range sum with range add

    // Modify these for different operations
    T_val merge_op(T_val a, T_val b)
    {
        return a + b; // Default: sum
    }

    // How a lazy update value affects a node's actual stored value.
    // For range add and range sum: node_value += lazy_value * length_of_segment_covered_by_node
    T_val apply_lazy_to_node_op(T_val current_node_val, T_lazy lazy_val, int node_idx)
    {
        return current_node_val + lazy_val * range_len[node_idx];
    }

    // How a new lazy update combines with an existing lazy value on a node.
    // For range add: existing_lazy += new_lazy_value
    T_lazy combine_lazy_op(T_lazy existing_lazy_val, T_lazy new_lazy_val)
    {
        return existing_lazy_val + new_lazy_val;
    }

    SegTreeLazy(int n_val = 0, T_val default_val = 0, T_val neutral_v = 0, T_lazy neutral_l = 0)
        : n(n_val), neutral_val(neutral_v), neutral_lazy(neutral_l)
    {
        if (n > 0)
        {
            t.assign(2 * n, default_val);
            lazy.assign(2 * n, neutral_lazy);
            range_len.assign(2 * n, 0);
            _build_range_len(1, 0, n - 1);
        }
        else
        {
            t.clear();
            lazy.clear();
            range_len.clear();
        }
    }

    SegTreeLazy(const vector<T_val> &arr, T_val neutral_v = 0, T_lazy neutral_l = 0)
        : n(sz(arr)), neutral_val(neutral_v), neutral_lazy(neutral_l)
    { // Used sz
        ASSERT(n > 0, "Cannot build SegTreeLazy from an empty array.");
        t.assign(2 * n, neutral_val);
        lazy.assign(2 * n, neutral_lazy);
        range_len.assign(2 * n, 0);
        _build_range_len(1, 0, n - 1);
        _build_from_array(arr, 1, 0, n - 1);
    }

    void _build_range_len(int node_idx, int seg_l, int seg_r)
    {
        range_len[node_idx] = seg_r - seg_l + 1;
        if (seg_l == seg_r)
            return;
        int mid = seg_l + (seg_r - seg_l) / 2;
        _build_range_len(node_idx << 1, seg_l, mid);
        _build_range_len(node_idx << 1 | 1, mid + 1, seg_r);
    }

    void _build_from_array(const vector<T_val> &arr, int node_idx, int seg_l, int seg_r)
    {
        if (seg_l == seg_r)
        {
            if (seg_l < sz(arr))
                t[node_idx] = arr[seg_l]; // Used sz
            return;
        }
        int mid = seg_l + (seg_r - seg_l) / 2;
        _build_from_array(arr, node_idx << 1, seg_l, mid);
        _build_from_array(arr, node_idx << 1 | 1, mid + 1, seg_r);
        t[node_idx] = merge_op(t[node_idx << 1], t[node_idx << 1 | 1]);
    }

    void _push(int node_idx)
    { // Push lazy value from node_idx to its children
        if (lazy[node_idx] != neutral_lazy)
        {
            // Apply lazy to children's actual values
            t[node_idx << 1] = apply_lazy_to_node_op(t[node_idx << 1], lazy[node_idx], node_idx << 1);
            t[node_idx << 1 | 1] = apply_lazy_to_node_op(t[node_idx << 1 | 1], lazy[node_idx], node_idx << 1 | 1);

            // Combine with children's existing lazy values
            lazy[node_idx << 1] = combine_lazy_op(lazy[node_idx << 1], lazy[node_idx]);
            lazy[node_idx << 1 | 1] = combine_lazy_op(lazy[node_idx << 1 | 1], lazy[node_idx]);

            lazy[node_idx] = neutral_lazy; // Clear lazy from current node
        }
    }

    // Update range [qL, qR] (inclusive) with value `val`
    void _update_range(int node_idx, int seg_l, int seg_r, int qL, int qR, T_lazy val)
    {
        if (seg_l > qR || seg_r < qL)
            return; // Current segment out of query range
        if (qL <= seg_l && seg_r <= qR)
        { // Current segment completely within query range
            t[node_idx] = apply_lazy_to_node_op(t[node_idx], val, node_idx);
            lazy[node_idx] = combine_lazy_op(lazy[node_idx], val);
            return;
        }
        _push(node_idx); // Push lazy values down before splitting segment
        int mid = seg_l + (seg_r - seg_l) / 2;
        _update_range(node_idx << 1, seg_l, mid, qL, qR, val);
        _update_range(node_idx << 1 | 1, mid + 1, seg_r, qL, qR, val);
        t[node_idx] = merge_op(t[node_idx << 1], t[node_idx << 1 | 1]);
    }

    void update(int qL, int qR, T_lazy val)
    { // Public interface for 0-indexed [qL, qR]
        ASSERT(qL >= 0 && qL < n && qR >= 0 && qR < n && qL <= qR, "SegTreeLazy::update: Invalid range.");
        _update_range(1, 0, n - 1, qL, qR, val);
    }

    // Point update: update element at 0-indexed position `idx` by adding `val`
    // This is a special case of range update [idx, idx]
    void update_point(int idx, T_lazy val)
    {
        update(idx, idx, val);
    }

    T_val _query_range(int node_idx, int seg_l, int seg_r, int qL, int qR)
    {
        if (seg_l > qR || seg_r < qL)
            return neutral_val; // Current segment out of query range
        if (qL <= seg_l && seg_r <= qR)
        { // Current segment completely within query range
            return t[node_idx];
        }
        _push(node_idx); // Push lazy values down
        int mid = seg_l + (seg_r - seg_l) / 2;
        T_val left_res = _query_range(node_idx << 1, seg_l, mid, qL, qR);
        T_val right_res = _query_range(node_idx << 1 | 1, mid + 1, seg_r, qL, qR);
        return merge_op(left_res, right_res);
    }

    T_val query(int qL, int qR)
    { // Public interface for 0-indexed [qL, qR]
        ASSERT(qL >= 0 && qL < n && qR >= 0 && qR < n && qL <= qR, "SegTreeLazy::query: Invalid range.");
        return _query_range(1, 0, n - 1, qL, qR);
    }

    void reset(int new_n, T_val default_val = 0)
    {
        n = new_n;
        if (n > 0)
        {
            t.assign(2 * n, default_val);
            lazy.assign(2 * n, neutral_lazy);
            range_len.assign(2 * n, 0);
            _build_range_len(1, 0, n - 1);
        }
        else
        {
            t.clear();
            lazy.clear();
            range_len.clear();
        }
    }
};

// Fenwick Tree (Binary Indexed Tree - BIT)
// Default: Prefix Sum Query, Point Update (add value)
// To customize T (data type) if needed (e.g. for non-integer sums)
// Operations are 1-indexed internally for easier BIT logic,
// but public interface can be 0-indexed for consistency with other structures.
template <typename T = ll>
struct FenwickTree
{
    int n;
    vector<T> bit; // Stores the BIT

    FenwickTree(int n_val = 0) : n(n_val)
    {
        if (n > 0)
        {
            bit.assign(n + 1, 0); // 1-indexed, so size n+1
        }
        else
        {
            bit.clear();
        }
    }

    FenwickTree(const vector<T> &arr) : n(sz(arr))
    { // Used sz
        ASSERT(n > 0, "Cannot build Fenwick Tree from an empty array.");
        bit.assign(n + 1, 0);
        f(i, 0, n)
        {                      // Used f macro
            update(i, arr[i]); // Use 0-indexed public update
        }
    }

    // Add 'delta' to element at 0-indexed position 'idx'
    void update(int idx, T delta)
    {
        ASSERT(idx >= 0 && idx < n, "FenwickTree::update: Index out of bounds.");
        for (++idx; idx <= n; idx += idx & -idx)
        { // Convert to 1-indexed for BIT logic
            bit[idx] += delta;
        }
    }

    // Query sum from index 0 to 'idx' (inclusive, 0-indexed)
    T query(int idx)
    {
        ASSERT(idx >= 0 && idx < n, "FenwickTree::query: Index out of bounds for prefix sum.");
        T sum = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
        { // Convert to 1-indexed for BIT logic
            sum += bit[idx];
        }
        return sum;
    }

    // Query sum of range [l, r] (inclusive, 0-indexed)
    T query_range(int l, int r)
    {
        ASSERT(l >= 0 && l <= r && r < n, "FenwickTree::query_range: Invalid range.");
        if (l == 0)
            return query(r);
        return query(r) - query(l - 1);
    }

    void reset(int new_n)
    {
        n = new_n;
        if (n > 0)
        {
            bit.assign(n + 1, 0);
        }
        else
        {
            bit.clear();
        }
    }
};

// ───────────────── GRAPH ALGORITHMS ───────────────────

// Dijkstra's Algorithm for Shortest Paths
// Graph represented as an adjacency list: vector<vector<pair<int, ll>>> adj
// adj[u] = vector of pairs {v, weight} for edges from u to v
// Returns a vector of shortest distances from source `s` to all other nodes.
// Distances are ll, INF if not reachable.

inline vector<ll> dijkstra(int s, int n, const vector<vector<pii>> &adj)
{
    vector<ll> dist(n, INF);
    dist[s] = 0;
    pqg<pll> pq; // Min-priority queue: {distance, node_index}
    pq.emplace(0, s);

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
        { // Already found a shorter path
            continue;
        }

        forV(adj[u])
        { // Used forV macro, and edge.fi, edge.se implicitly use fi, se
            int v = e.fi;
            ll weight = e.se;
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

// 0-1 BFS for Shortest Paths (edge weights are 0 or 1)
// Graph represented as an adjacency list: vector<vector<pair<int, int>>> adj
// adj[u] = vector of pairs {v, weight} where weight is 0 or 1.
// Returns a vector of shortest distances (ll) from source `s`.
inline vector<ll> bfs01(int s, int n, const vector<vector<pii>> &adj)
{
    vector<ll> dist(n, INF);
    dist[s] = 0;
    deque<int> q_bfs; // Renamed to avoid conflict with `dq` type alias if it were used locally for `std::deque`.
    q_bfs.emplace_front(s);

    while (!q_bfs.empty())
    {
        int u = q_bfs.front();
        q_bfs.pop_front();

        forV(adj[u])
        { // Used forV macro, and e.fi, e.se implicitly use fi, se
            int v = e.fi;
            int weight = e.se;
            ASSERT(weight == 0 || weight == 1, "0-1 BFS expects edge weights to be 0 or 1.");

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                if (weight == 1)
                {
                    q_bfs.emplace_back(v);
                }
                else
                { // weight == 0
                    q_bfs.emplace_front(v);
                }
            }
        }
    }
    return dist;
}

// Lowest Common Ancestor (LCA) using Binary Lifting
// Assumes tree is 0-indexed. MAX_NODES can be adjusted.
const int MAX_LCA_NODES = 200005; // Max number of nodes for LCA
const int MAX_LCA_LG = 20;        // Max log for binary lifting (ceil(log2(MAX_LCA_NODES)))

struct LCA
{
    int n_nodes;
    vector<vi> adj;
    vi depth;
    vector<vi> up; // up[v][j] is the 2^j-th ancestor of v
    int timer;
    vi tin, tout; // For subtree checks, if needed (optional here, focus on LCA/dist)

    LCA(int n = 0) : n_nodes(n)
    {
        if (n > 0)
        {
            adj.assign(n, vi());
            depth.assign(n, 0);
            up.assign(n, vi(MAX_LCA_LG));
            tin.assign(n, 0);
            tout.assign(n, 0);
            timer = 0;
        }
    }

    void add_edge(int u, int v)
    {
        ASSERT(u >= 0 && u < n_nodes && v >= 0 && v < n_nodes, "LCA::add_edge: Node index out of bounds.");
        adj[u].pb(v); // Used pb
        adj[v].pb(u); // Used pb. Corrected: should be adj[v].pb(u)
    }

    void _dfs_lca(int v, int p, int d)
    {
        depth[v] = d;
        up[v][0] = p;
        tin[v] = ++timer;

        f(j, 1, MAX_LCA_LG)
        { // Used f macro
            up[v][j] = up[up[v][j - 1]][j - 1];
        }

        forV(adj[v])
        { // Used forV macro
            if (e != p)
            {
                _dfs_lca(e, v, d + 1);
            }
        }
        tout[v] = ++timer;
    }

    // Call after adding all edges. Root is typically 0.
    void build(int root = 0)
    {
        if (n_nodes == 0)
            return;
        ASSERT(root >= 0 && root < n_nodes, "LCA::build: Root index out of bounds.");
        timer = 0;
        _dfs_lca(root, root, 0); // Parent of root is root itself, depth 0
    }

    // Get k-th ancestor of node u (0-th ancestor is u itself)
    int get_kth_ancestor(int u, int k)
    {
        ASSERT(u >= 0 && u < n_nodes, "LCA::get_kth_ancestor: Node index out of bounds.");
        if (k < 0 || k > depth[u])
            return -1; // Or handle as error/specific value

        rf(j, MAX_LCA_LG, 0)
        { // Used rf macro
            if ((k >> j) & 1)
            {
                u = up[u][j];
            }
        }
        return u;
    }

    int get_lca(int u, int v)
    {
        ASSERT(u >= 0 && u < n_nodes && v >= 0 && v < n_nodes, "LCA::get_lca: Node index out of bounds.");
        if (depth[u] < depth[v])
            swap(u, v);

        u = get_kth_ancestor(u, depth[u] - depth[v]);

        if (u == v)
            return u;

        rf(j, MAX_LCA_LG, 0)
        { // Used rf macro
            if (up[u][j] != up[v][j])
            {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

    int get_dist(int u, int v)
    {
        ASSERT(u >= 0 && u < n_nodes && v >= 0 && v < n_nodes, "LCA::get_dist: Node index out of bounds.");
        int lca_node = get_lca(u, v);
        return depth[u] + depth[v] - 2 * depth[lca_node];
    }

    // Optional: Check if u is an ancestor of v
    bool is_ancestor(int u, int v)
    {
        ASSERT(u >= 0 && u < n_nodes && v >= 0 && v < n_nodes, "LCA::is_ancestor: Node index out of bounds.");
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
};

// ───────────────── STRING ALGORITHMS ──────────────────

// KMP (Knuth-Morris-Pratt) String Searching Algorithm

// Computes the LPS (Longest Proper Prefix which is also Suffix) array for KMP.
// lps[i] = length of the longest proper prefix of pattern[0...i] that is also a suffix of pattern[0...i].
inline vi compute_lps_array(const string &pattern)
{
    int m = sz(pattern); // Used sz
    vi lps(m, 0);
    int length = 0; // Length of the previous longest prefix suffix
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// KMP search function: Finds all occurrences of `pattern` in `text`.
// Returns a vector of 0-indexed starting positions of occurrences.
inline vi kmp_search(const string &text, const string &pattern)
{
    int n = sz(text);    // Used sz
    int m = sz(pattern); // Used sz
    if (m == 0)
        return {}; // Empty pattern
    if (m > n)
        return {}; // Pattern longer than text

    vi lps = compute_lps_array(pattern);
    vi occurrences;

    int i = 0; // Index for text[]
    int j = 0; // Index for pattern[]
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            occurrences.pb(i - j); // Used pb
            j = lps[j - 1];        // Continue searching for more occurrences
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
    return occurrences;
}

// Polynomial String Hashing with two hash functions for robustness
struct StringHashing
{
    string s_hashed;
    int n;
    ll M1 = MOD_CONST;  // Primary modulus
    ll M2 = MOD1_CONST; // Secondary modulus (must be different from M1)
    ll B1, B2;          // Bases for hashing, should be > alphabet size & random

    vll h1, h2; // Prefix hashes: h1[i] = hash of s[0...i-1] mod M1
    vll p1, p2; // Powers of B1 mod M1, B2 mod M2: p1[i] = B1^i mod M1
    // vll inv_p1, inv_p2; // Inverse powers (optional, if using division method for substring hash)

    // For generating random bases
    mt19937 rng_engine{(unsigned int)chrono::steady_clock::now().time_since_epoch().count()};

    ll generate_random_base(ll lower_bound, ll upper_bound)
    {
        uniform_int_distribution<ll> dist(lower_bound, upper_bound);
        return dist(rng_engine);
    }

    StringHashing(const string &s, ll b1 = 0, ll b2 = 0) : s_hashed(s), n(sz(s))
    { // Used sz
        if (n == 0)
            return;

        // Reserve space for vectors to avoid reallocations
        h1.reserve(n + 1);
        h2.reserve(n + 1);
        p1.reserve(n + 1);
        p2.reserve(n + 1);

        // Generate random bases if not provided, ensuring they are > typical char values (e.g., > 256 for ASCII)
        // And preferably < Moduli. Using fixed good primes is also an option.
        const int MIN_BASE = 300; // Should be greater than any character value

        B1 = (b1 == 0) ? generate_random_base(MIN_BASE, M1 - 1) : b1;
        B2 = (b2 == 0) ? generate_random_base(MIN_BASE, M2 - 1) : b2;

        // Ensure B1 and B2 are different, especially if M1 or M2 could be the same (though we use different M1, M2 here)
        // or if one was user-provided and the other generated.
        while (B1 == B2)
        {
            B2 = generate_random_base(MIN_BASE, M2 - 1);
        }

        h1.resize(n + 1, 0);
        p1.resize(n + 1, 1);
        h2.resize(n + 1, 0);
        p2.resize(n + 1, 1);
        // inv_p1.resize(n + 1, 1); inv_p2.resize(n + 1, 1); // If using division method

        ModularOps<MOD_CONST> Ops1;  // Use MOD_CONST for M1 related ops
        ModularOps<MOD1_CONST> Ops2; // Use MOD1_CONST for M2 related ops

        f(i, 0, n)
        { // Used f macro
            p1[i + 1] = Ops1.mul(p1[i], B1);
            p2[i + 1] = Ops2.mul(p2[i], B2);
            // For ASCII, s[i] is char. For 0-indexed 'a'-'z', use (s[i] - 'a' + 1)
            // Assuming s[i] gives small integer values (e.g., chars, or 1-indexed values)
            h1[i + 1] = Ops1.add(Ops1.mul(h1[i], B1), (s[i] - ' ' + 1)); // Shift ' ' to 1 for safety, or use s[i] if it's already int > 0
            h2[i + 1] = Ops2.add(Ops2.mul(h2[i], B2), (s[i] - ' ' + 1));
        }

        // If using division method for substring hash, precompute inverse powers:
        // inv_p1[n] = Ops1.inv(p1[n]);
        // inv_p2[n] = Ops2.inv(p2[n]);
        // rf(i, n, 0) { // Example if using rf
        //     inv_p1[i] = Ops1.mul(inv_p1[i+1], B1);
        //     inv_p2[i] = Ops2.mul(inv_p2[i+1], B2);
        // }
    }

    // Get hash of substring s[l..r] (0-indexed, inclusive)
    // Returns a pair {hash_val_1, hash_val_2}
    pll get_hash(int l, int r)
    {
        if (l > r || l < 0 || r >= n)
            return {0, 0}; // Invalid range
        if (n == 0)
            return {0, 0};

        ModularOps<MOD_CONST> Ops1;
        ModularOps<MOD1_CONST> Ops2;

        ll sub_hash1 = Ops1.sub(h1[r + 1], Ops1.mul(h1[l], p1[r - l + 1]));
        ll sub_hash2 = Ops2.sub(h2[r + 1], Ops2.mul(h2[l], p2[r - l + 1]));

        return {sub_hash1, sub_hash2};
    }

    // Get hash of the entire string
    pll get_full_hash()
    {
        if (n == 0)
            return {0, 0};
        return {h1[n], h2[n]};
    }
};

// ────────────────── COMBINATORICS ─────────────────────
// Requires ModularOps (Mint) to be defined.
// Default MAX_N_COMB for precomputation can be adjusted.
const int MAX_N_COMB = 2000005; // Max N for which factorials are precomputed (e.g., 2e6+5)
inline vll fact(MAX_N_COMB);    // C++17 inline variable, sized at construction
inline vll invFact(MAX_N_COMB); // C++17 inline variable, sized at construction

// Call this once (e.g., at the beginning of main or solve if TCs are independent)
// if using nCr_mod or nPr_mod. Default Modulus is MOD_CONST.
template <ll Mod = MOD_CONST>
inline void precompute_factorials()
{ // Explicitly inline, though templates in headers are often implicitly so
    // fact and invFact are already sized due to their inline definition with MAX_N_COMB.
    // Ensure MAX_N_COMB is positive to avoid issues with array access at index 0.
    ASSERT(MAX_N_COMB > 0, "MAX_N_COMB must be positive for precompute_factorials.");
    if (MAX_N_COMB == 0)
        return; // Should not happen with current const value but good check

    fact[0] = 1;
    invFact[0] = 1;
    ModularOps<Mod> M_ops; // Local ModularOps instance for this function call
    f(i, 1, MAX_N_COMB)
    { // Used f macro
        // Safety check, though fact/invFact should be sized correctly by their definition.
        ASSERT(i < sz(fact) && i < sz(invFact), "Factorial precomputation index out of bounds.");
        fact[i] = M_ops.mul(fact[i - 1], i);
        invFact[i] = M_ops.inv(fact[i]);
    }
}

// Calculate nCr % Mod
// Assumes precompute_factorials has been called with the same Modulus.
template <ll Mod = MOD_CONST>
ll nCr_mod(int n, int r)
{
    if (r < 0 || r > n)
        return 0;
    ModularOps<Mod> M;
    return M.mul(fact[n], M.mul(invFact[r], invFact[n - r]));
}

// Calculate nPr % Mod
// Assumes precompute_factorials has been called with the same Modulus.
template <ll Mod = MOD_CONST>
ll nPr_mod(int n, int r)
{
    if (r < 0 || r > n)
        return 0;
    ModularOps<Mod> M;
    return M.mul(fact[n], invFact[n - r]);
}

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
    f(r, 1, s) // Used f macro
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

// Sieve of Eratosthenes
// Generates primes up to a given limit `max_n`.
// Also stores the smallest prime factor (spf) for each number.
struct Sieve
{
    int max_val;
    vb is_prime; // is_prime[i] is true if i is prime
    vi primes;   // List of prime numbers
    vi spf;      // spf[i] stores the smallest prime factor of i

    Sieve(int n = 1000000) : max_val(n)
    {
        ASSERT(n >= 1, "Sieve max_val must be at least 1.");
        is_prime.assign(n + 1, true);
        spf.assign(n + 1, 0);

        is_prime[0] = is_prime[1] = false;
        spf[1] = 1; // Smallest prime factor of 1 is conventionally 1 or undefined; using 1 here.

        cf(i, 2, n)
        { // Used cf macro
            if (is_prime[i])
            {
                primes.pb(i); // Used pb
                spf[i] = i;
            }
            // For composite numbers i, mark its multiples.
            // For a prime p in primes, p*i will have p as its smallest prime factor if p <= spf[i].
            // This ensures each composite is marked by its smallest prime factor exactly once.
            forV(primes)
            { // Used forV macro
                if (e > spf[i] || (ll)i * e > n)
                {          // e for element in primes
                    break; // p is no longer the smallest prime factor, or we exceed limit
                }
                is_prime[i * e] = false;
                spf[i * e] = e;
            }
        }
    }

    // Get prime factorization of k
    // Returns a vector of pairs {prime, exponent}
    vpll get_prime_factorization(int k)
    {
        ASSERT(k > 0 && k <= max_val, "get_prime_factorization input out of sieve range or non-positive.");
        vpll factors;
        if (k == 1)
            return factors; // Or return {{1,1}} depending on convention
        while (k > 1)
        {
            int p = spf[k];
            int count = 0;
            while (k % p == 0)
            {
                k /= p;
                count++;
            }
            factors.eb(p, count); // Used eb for pair construction
        }
        return factors;
    }

    // Get all distinct prime factors of k
    vll get_distinct_prime_factors(int k)
    {
        ASSERT(k > 0 && k <= max_val, "get_distinct_prime_factors input out of sieve range or non-positive.");
        vll distinct_factors;
        if (k == 1)
            return distinct_factors;
        while (k > 1)
        {
            int p = spf[k];
            distinct_factors.pb(p); // Used pb
            while (k % p == 0)
            {
                k /= p;
            }
        }
        return distinct_factors;
    }
};

#if __cplusplus >= 202002L
template <std::integral T1, std::integral T2>
constexpr bool isDivisible(T1 n, T2 divisor)
{
    if (divisor == 0)
    {
        return false;
    }
    return (n % divisor == 0);
}

template <std::integral T>
constexpr bool isOdd(T n)
{
    return !isDivisible(n, 2);
}
#else
template <typename T1, typename T2>
constexpr bool isDivisible(T1 n, T2 divisor)
{
    if (divisor == 0)
    {
        return false;
    }
    return (n % divisor == 0);
}

template <typename T>
constexpr bool isOdd(T n)
{
    return !isDivisible(n, 2);
}
#endif

// ──────────────── LINEAR ALGEBRA UTILITIES ───────────────

// Matrix struct for matrix exponentiation and other linear algebra operations.
// Assumes operations are done under a specific modulus, using Mint by default.
template <typename T = ll, ll Mod = MOD_CONST> // Allow flexible data type and modulus
struct Matrix
{
    int rows, cols;
    vector<vector<T>> mat;
    ModularOps<Mod> M; // Modular operations for the given Modulus

    Matrix(int r = 0, int c = 0, T val = 0) : rows(r), cols(c)
    {
        if (r > 0 && c > 0)
        {
            mat.assign(r, vector<T>(c, val));
        }
    }

    // Constructor for identity matrix
    static Matrix identity(int n)
    {
        Matrix id(n, n);
        f(i, 0, n)
        { // Used f macro
            id.mat[i][i] = 1;
        }
        return id;
    }

    // Matrix multiplication: C = A * B
    Matrix operator*(const Matrix &other) const
    {
        ASSERT(cols == other.rows, "Matrix multiplication: Column count of first matrix must match row count of second matrix.");
        Matrix result(rows, other.cols);
        f(i, 0, rows)
        { // Used f macro
            f(j, 0, other.cols)
            { // Used f macro
                T sum = 0;
                f(k, 0, cols)
                { // Used f macro
                    sum = M.add(sum, M.mul(mat[i][k], other.mat[k][j]));
                }
                result.mat[i][j] = sum;
            }
        }
        return result;
    }

    // For debugging or printing the matrix
    void print_matrix() const
    {
        f(i, 0, rows)
        { // Used f macro
            f(j, 0, cols)
            { // Used f macro
                cout << mat[i][j] << (j == cols - 1 ? "" : " ");
            }
            cout << NL;
        }
    }
};

// Matrix exponentiation (binary exponentiation for matrices)
// Returns base^exp % Mod. Base must be a square matrix.
template <typename T, ll Mod>
Matrix<T, Mod> matrix_power(Matrix<T, Mod> base, ll exp)
{
    ASSERT(base.rows == base.cols, "Matrix power: Base matrix must be square.");
    Matrix<T, Mod> result = Matrix<T, Mod>::identity(base.rows);
    // ModularOps instances M are already members of base and result, initialized by their constructors.
    // Re-assigning them here (base.M = ..., result.M = ...) is redundant if Matrix constructor correctly initializes M.

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = result * base;
        base = base * base;
        exp /= 2;
    }
    return result;
}

// Max Flow - Dinic's Algorithm
// Generally faster than Edmonds-Karp for many graph types.
struct DinicMaxFlow
{
    struct Edge
    {
        int to;
        ll capacity;
        int rev; // Index of the reverse edge in adj[to]
    };

    int n_nodes;
    vector<vector<Edge>> adj;
    vi level; // Stores level of each node in the level graph (distance from source)
    vi ptr;   // Pointer for DFS to keep track of the next edge to explore for a node

    DinicMaxFlow(int n = 0) : n_nodes(n)
    {
        if (n > 0)
        {
            adj.assign(n, vector<Edge>());
            level.resize(n);
            ptr.resize(n);
        }
    }

    // Adds a directed edge u->v with capacity cap.
    void add_edge(int u, int v, ll cap)
    {
        ASSERT(u >= 0 && u < n_nodes && v >= 0 && v < n_nodes, "DinicMaxFlow::add_edge: Node index out of bounds.");
        ASSERT(cap >= 0, "DinicMaxFlow::add_edge: Capacity must be non-negative.");
        adj[u].eb(v, cap, static_cast<int>(sz(adj[v])));
        adj[v].eb(u, 0, static_cast<int>(sz(adj[u]) - 1)); // Residual edge with 0 capacity initially
    }

    // BFS to build the level graph and check if sink is reachable.
    bool _bfs_dinic(int s, int t)
    {
        fill(all(level), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (const auto &edge : adj[u])
            {
                if (edge.capacity > 0 && level[edge.to] < 0)
                {
                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1; // True if sink t is reachable
    }

    // DFS to send flow along paths in the level graph (finds a blocking flow).
    // u: current node, t: sink, pushed: flow pushed so far along current path.
    ll _dfs_dinic(int u, int t, ll pushed)
    {
        if (pushed == 0)
            return 0;
        if (u == t)
            return pushed; // Reached sink

        for (int &cid = ptr[u]; cid < sz(adj[u]); ++cid)
        {
            auto &edge = adj[u][cid];
            if (level[edge.to] != level[u] + 1 || edge.capacity == 0)
                continue;

            ll tr = _dfs_dinic(edge.to, t, min(pushed, edge.capacity));
            if (tr == 0)
                continue; // No flow sent through this path

            edge.capacity -= tr;
            adj[edge.to][edge.rev].capacity += tr;
            return tr;
        }
        return 0; // No more flow can be pushed from u in this DFS phase
    }

    ll get_max_flow(int s, int t)
    {
        ASSERT(s >= 0 && s < n_nodes && t >= 0 && t < n_nodes, "DinicMaxFlow::get_max_flow: Source/sink index out of bounds.");
        if (s == t)
            return INF; // Or 0, by convention

        ll total_flow = 0;
        while (_bfs_dinic(s, t))
        {                      // While sink is reachable in level graph
            fill(all(ptr), 0); // Reset pointers for DFS for the new level graph
            while (ll pushed = _dfs_dinic(s, t, INF))
            {
                total_flow += pushed;
            }
        }
        return total_flow;
    }
};

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
#if __cplusplus >= 202002L
    for (auto &element : v)
        cin >> element;
#else
    forV(v) // Already uses forV
        cin >> e;
#endif
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
#if __cplusplus >= 202002L
    for (const auto &element : v)
        cout << element << SPACE;
#else
    forV(v) // Already uses forV
        cout << e << SPACE;
#endif
    cout << NL;
}

// Suffix Array and LCP Array Construction
// Based on an O(N log N) approach using sorting of cyclic shifts/suffixes.

// Structure to hold suffix information for sorting
struct Suffix
{
    int index;   // Original index of the suffix
    int rank[2]; // Ranks for the first and second halves of the current substring
};

// Comparison function for Suffix structures
inline int compareSuffixes(const struct Suffix &a, const struct Suffix &b)
{
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0);
}

// Builds the Suffix Array for a given string s.
// Appends a special character smaller than any in s (e.g. '$' or ASCII 0) if not present,
// to simplify suffix comparisons and ensure all suffixes are distinct.
// Here, we assume string s contains characters that can be mapped to 0..alphabet_size-1.
// For typical char strings, we can use their ASCII values.
// Returns the suffix array: a vector of starting indices of sorted suffixes.
inline vi build_suffix_array(const string &s_in)
{
    string s = s_in;
    s += char(1);                         // Append a sentinel character smaller than any typical char
    int n = static_cast<int>(s.length()); // Use int for n, consistent with typical index usage

    if (n == 0)
        return {}; // Should not happen if s_in was non-empty due to sentinel
    if (n == 1 && s[0] == char(1))
        return {0}; // Only sentinel was present

    struct Suffix suffixes[n];
    vi rank_arr(n); // Stores rank of suffix starting at i

    // Initialize ranks for the first iteration (k=1)
    f(i, 0, n)
    { // Used f macro
        suffixes[i].index = i;
        suffixes[i].rank[0] = s[i];                            // Using char ASCII as initial rank
        suffixes[i].rank[1] = ((i + 1) < n) ? (s[i + 1]) : -1; // -1 for out of bounds
    }

    // Sort suffixes based on first 2 characters
    sort(suffixes, suffixes + n, [](const Suffix &a, const Suffix &b)
         {
        if (a.rank[0] != b.rank[0]) return a.rank[0] < b.rank[0];
        return a.rank[1] < b.rank[1]; });

    // Iteratively build suffix array using doubling trick
    // k is the length of blocks being compared
    for (int k = 4; k < 2 * n; k = k * 2)
    { // Cannot use simple f/cf due to k = k*2
        // Assign new ranks to suffixes
        int rank_val = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank_val;
        rank_arr[suffixes[0].index] = rank_val;

        f(i, 1, n) // Used f macro
        {
            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i - 1].rank[1])
            {
                // Same first and second half ranks as previous suffix
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank_val;
            }
            else
            {
                // Different, assign new rank
                prev_rank = suffixes[i].rank[0];
                rank_val++;
                suffixes[i].rank[0] = rank_val;
            }
            rank_arr[suffixes[i].index] = rank_val;
        }

        // Assign rank for the second half of each suffix
        f(i, 0, n) // Used f macro
        {
            int next_index = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (next_index < n) ? rank_arr[next_index] : -1;
        }

        // Sort based on new ranks
        sort(suffixes, suffixes + n, [](const Suffix &a, const Suffix &b)
             {
            if (a.rank[0] != b.rank[0]) return a.rank[0] < b.rank[0];
            return a.rank[1] < b.rank[1]; });

        // Optimization: if all ranks are unique, array is sorted
        if (rank_val == n - 1)
            break;
    }

    vi sa(n);
    f(i, 0, n) // Used f macro
    {
        sa[i] = suffixes[i].index;
    }
    // If a sentinel was added, the suffix array will contain an entry for it.
    // Often, for problems on the original string s_in, this entry (and the sentinel itself)
    // might need to be ignored or handled. The current SA is for s_in + sentinel.
    // For typical competitive programming usage, one might return sa.subvec(1, n_original) or adjust indices.
    // Or, if string s_in already has a unique smallest char, sentinel isn't strictly necessary (but good practice).
    // Here, we return the SA for the string with sentinel. Users should be aware.
    return sa;
}

// Builds the LCP (Longest Common Prefix) array using Kasai's algorithm.
// s: The original string.
// sa: The suffix array for s.
// Returns the LCP array: lcp[i] is the LCP of s.substr(sa[i]) and s.substr(sa[i-1]).
// lcp[0] is typically 0 or undefined.
inline vi build_lcp_array(const string &s, const vi &sa)
{
    int n = sz(s);
    if (n == 0)
        return {};
    ASSERT(sz(sa) == n, "Suffix array size must match string size for LCP construction.");

    vi lcp(n, 0);
    vi rank_inv(n, 0); // rank_inv[i] = position of suffix starting at i in sa

    f(i, 0, n) // Used f macro
    {
        rank_inv[sa[i]] = i;
    }

    int k = 0; // Stores LCP of previous pair of suffixes
    f(i, 0, n) // Used f macro
    {
        if (rank_inv[i] == n - 1)
        { // Suffix s[i...] is last in sorted order, no next suffix
            k = 0;
            continue;
        }

        int j = sa[rank_inv[i] + 1]; // Index of the next suffix in sorted order
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
        {
            k++;
        }
        lcp[rank_inv[i] + 1] = k; // LCP between suffix sa[rank_inv[i]] and sa[rank_inv[i]+1]

        if (k > 0)
        {
            k--; // LCP for next pair will be at least k-1
        }
    }
    return lcp; // lcp[0] will be 0 from initialization, which is fine.
}

// ──────────────── POLYNOMIAL OPERATIONS ─────────────────

// Number Theoretic Transform (NTT)
// For polynomial multiplication under a prime modulus.
// Modulus M must be prime, of the form c * 2^k + 1.
// MOD1_CONST (998244353) is a common NTT prime: 119 * 2^23 + 1. Primitive root is 3.

namespace NTT
{
    constexpr ll MOD = MOD1_CONST; // Using 998244353
    constexpr ll PRIMITIVE_ROOT = 3;
    inline ModularOps<MOD> M; // C++17 inline variable

    // Helper for power, distinct from global nt_power to ensure correct modulus context
    inline ll power_ntt(ll base, ll exp)
    { // Marked inline
        return M.power(base, exp);
    }

    // Bit-reversal permutation
    inline void _reorder_array(vll &a)
    {
        int n = sz(a); // Used sz
        if (n == 0)
            return;
        vi rev(n);
        f(i, 0, n)
        { // Used f macro
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
            if (i < rev[i])
            {
                swap(a[i], a[rev[i]]);
            }
        }
    }

    // Core NTT function
    // `invert = true` for inverse NTT
    inline void _transform(vll &a, bool invert)
    {
        int n = sz(a); // Used sz
        if (n == 0)
            return;
        _reorder_array(a);

        for (int len = 2; len <= n; len <<= 1)
        { // Cannot use simple f/cf due to len <<= 1
            ll wlen = power_ntt(PRIMITIVE_ROOT, (MOD - 1) / len);
            if (invert)
            {
                wlen = M.inv(wlen);
            }
            for (int i = 0; i < n; i += len)
            { // Cannot use simple f/cf due to i += len
                ll w = 1;
                f(j, 0, len / 2)
                { // Used f macro
                    ll u = a[i + j];
                    ll v = M.mul(a[i + j + len / 2], w);
                    a[i + j] = M.add(u, v);
                    a[i + j + len / 2] = M.sub(u, v);
                    w = M.mul(w, wlen);
                }
            }
        }

        if (invert)
        {
            ll n_inv = M.inv(n);
            forV(a)
            {                        // Used forV macro, element is `e`
                e = M.mul(e, n_inv); // Corrected: use `e` instead of `x`
            }
        }
    }

    // Multiplies two polynomials a and b (coefficient vectors)
    // Returns the coefficient vector of a*b.
    inline vll multiply_polynomials(const vll &a_in, const vll &b_in)
    { // Renamed to avoid conflict with 'a' in forV
        if (a_in.empty() || b_in.empty())
            return {};

        vll fa(all(a_in)), fb(all(b_in));         // Used all
        int result_deg = sz(a_in) + sz(b_in) - 2; // Used sz
        if (result_deg < 0)
            result_deg = 0; // Handle empty or constant product

        int n_ntt = 1; // Renamed n to n_ntt to avoid conflict
        while (n_ntt < sz(a_in) + sz(b_in) - 1)
            n_ntt <<= 1; // Used sz. Smallest power of 2 >= result size
        if (sz(a_in) == 0 && sz(b_in) == 0)
            n_ntt = 0; // Used sz. Product of two empty polys is empty
        else if (n_ntt == 0 && (sz(a_in) > 0 || sz(b_in) > 0))
            n_ntt = 1; // Used sz. product of const and empty
        if (n_ntt == 0 && (sz(a_in) > 0 || sz(b_in) > 0) && (sz(a_in) + sz(b_in) - 1 > 0))
            n_ntt = 1; // Used sz. for single element product, result is size 1
                       // e.g. {c1} * {c2} = {c1c2}, size 1
                       // {c} * {} -> {}, size 0
                       // {} * {} -> {}, size 0
        // handle sz(a)+sz(b)-1 = 0 case (e.g. [5]*[] ) -> n=0? No, should be size of result_deg+1
        // if result_deg is -1 (e.g. a={c}, b={}), then result size should be 0.
        // if result_deg is 0 (e.g. a={c1}, b={c2}), result size is 1. n should be 1.

        int final_size = result_deg + 1;
        if (final_size < 0)
            final_size = 0;

        // Reset n_ntt based on final_size for NTT processing length
        n_ntt = 1;
        while (n_ntt < final_size)
            n_ntt <<= 1;
        if (final_size == 0)
            n_ntt = 0; // if product is truly empty

        fa.resize(n_ntt); // Pad with zeros
        fb.resize(n_ntt);

        if (n_ntt > 0)
        { // Only transform if there are elements
            _transform(fa, false);
            _transform(fb, false);
            f(i, 0, n_ntt)
            { // Used f macro
                fa[i] = M.mul(fa[i], fb[i]);
            }
            _transform(fa, true);
        }

        fa.resize(final_size); // Trim to actual result polynomial size
        return fa;
    }
} // namespace NTT

// Heavy-Light Decomposition (HLD)
// Decomposes a tree into vertex-disjoint paths for efficient path queries/updates
// when combined with a data structure (e.g., Segment Tree) on the linearized paths.
struct HLD
{
    int n_nodes;
    vector<vi> adj;
    vi parent, depth, subtree_size, heavy_child;
    vi head; // head[u] is the highest node (closest to root) in the heavy path containing u
    vi pos;  // pos[u] is the position of u in the linearized array for segment tree
    // vi val; // Optional: if storing node values directly in HLD for some reason
    int cur_pos; // Current position in the linearized array
    // bool values_on_edges; // If values are on edges rather than nodes (adjusts queries)

    HLD(int n = 0 /*, bool edge_values = false */) : n_nodes(n) /*, values_on_edges(edge_values)*/
    {
        if (n > 0)
        {
            adj.assign(n, vi());
            parent.assign(n, 0);
            depth.assign(n, 0);
            subtree_size.assign(n, 0);
            heavy_child.assign(n, -1); // -1 indicates no heavy child
            head.assign(n, 0);
            pos.assign(n, 0);
            // if (values_on_edges) val.assign(n,0); // Values typically for nodes or user manages edge values mapped to child nodes
            cur_pos = 0;
        }
    }

    void add_edge(int u, int v)
    {
        ASSERT(u >= 0 && u < n_nodes && v >= 0 && v < n_nodes, "HLD::add_edge: Node index out of bounds.");
        adj[u].pb(v); // Used pb for simple int
        adj[v].pb(u); // Used pb for simple int
    }

    // First DFS: calculate parent, depth, subtree_size, and identify heavy_child
    void _dfs_size(int u, int p, int d)
    {
        parent[u] = p;
        depth[u] = d;
        subtree_size[u] = 1;
        int max_c_size = 0;

        for (int v : adj[u])
        {
            if (v == p)
                continue;
            _dfs_size(v, u, d + 1);
            subtree_size[u] += subtree_size[v];
            if (subtree_size[v] > max_c_size)
            {
                max_c_size = subtree_size[v];
                heavy_child[u] = v;
            }
        }
    }

    // Second DFS: build heavy paths, assign head and pos (linearized position)
    void _dfs_hld(int u, int p, int h)
    {
        head[u] = h;
        pos[u] = cur_pos++;
        // if (!values_on_edges && u < sz(initial_node_values_for_seg_tree)) { /* build seg_tree_array[pos[u]] = initial_node_values[u] */ }

        if (heavy_child[u] != -1)
        {
            _dfs_hld(heavy_child[u], u, h); // Continue current heavy path
        }

        for (int v : adj[u])
        {
            if (v == p || v == heavy_child[u])
                continue;
            _dfs_hld(v, u, v); // Start new heavy path with v as its head
        }
    }

    // Call after adding all edges. Root is typically 0.
    // User should initialize a segment tree (or other DS) of size n_nodes afterwards,
    // using the `pos` array to map original node indices to segment tree indices.
    // E.g., for node u, its value is at segment_tree_array[pos[u]].
    void build(int root = 0)
    {
        if (n_nodes == 0)
            return;
        ASSERT(root >= 0 && root < n_nodes, "HLD::build: Root index out of bounds.");
        cur_pos = 0;
        _dfs_size(root, root, 0);   // parent of root is root itself, depth 0
        _dfs_hld(root, root, root); // root is head of its own path
    }

    // Helper to get LCA (using simple поднимаемся по предкам, then by depth)
    // For more performance, use the dedicated LCA struct if available.
    // This is a basic LCA for HLD path queries, not as fast as binary lifting LCA.
    int get_lca_internal(int u, int v) const
    {
        ASSERT(u >= 0 && u < n_nodes && v >= 0 && v < n_nodes, "HLD::get_lca_internal: Node index out of bounds.");
        while (head[u] != head[v])
        {
            if (depth[head[u]] > depth[head[v]])
                swap(u, v);
            v = parent[head[v]];
        }
        return (depth[u] < depth[v]) ? u : v;
    }

    // Process path from u to ancestor `anc` (inclusive of u, exclusive of anc if anc is parent of head[u] on different path)
    // Or inclusive of anc if on same heavy path.
    // Calls `func(start_pos, end_pos)` for each segment on the path in linearized array.
    // `start_pos` and `end_pos` are 0-indexed inclusive for the segment tree / linearized array.
    template <typename Callable>
    void _process_path_segments_to_ancestor(int u, int ancestor, Callable func) const
    {
        while (head[u] != head[ancestor])
        {
            func(pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        // Process remaining part on the same heavy path as ancestor
        // If u and ancestor are the same, this handles it. If values_on_edges, might need pos[ancestor]+1
        func(pos[ancestor] /*+ (values_on_edges ? 1 : 0)*/, pos[u]);
    }

    // Generic path processing function. Calls `func(start_pos, end_pos)` for segments.
    // The user's func is responsible for querying/updating their segment tree.
    template <typename Callable>
    void process_path(int u, int v, Callable func) const
    {
        ASSERT(u >= 0 && u < n_nodes && v >= 0 && v < n_nodes, "HLD::process_path: Node index out of bounds.");
        int lca = get_lca_internal(u, v);

        _process_path_segments_to_ancestor(u, lca, func);
        _process_path_segments_to_ancestor(v, lca, func);

        // The LCA itself is processed twice if u!=lca and v!=lca.
        // If values are on nodes, this might be fine if func is idempotent for point (e.g. sum over [pos[lca], pos[lca]] twice).
        // Or, if func aggregates, the user must handle it (e.g. subtract LCA value once if summing).
        // A common strategy is to query u to lca and v to lca, then handle lca separately.
        // For simplicity, this version might make func process LCA's segment twice.
        // A more robust version might have _process_path_segments_to_ancestor be exclusive of ancestor
        // and then explicitly call func(pos[lca], pos[lca]).
    }

    // Example: Query for sum on path u-v. User provides a segment tree query function.
    // ll query_path_sum(int u, int v, const SegTreeLazy<ll,ll>& seg_tree) {
    //     ll total_sum = 0;
    //     process_path(u, v, [&](int l_pos, int r_pos) {
    //         total_sum = M.add(total_sum, seg_tree.query(l_pos, r_pos)); // Assuming M.add if modular sum
    //     });
    //     // If LCA counted twice & simple sum, subtract val[lca] (or seg_tree.query(pos[lca], pos[lca])) once.
    //     // For this version, with potential double count of LCA segment, this needs care.
    //     return total_sum;
    // }

    // Example: Update nodes on path u-v. User provides a segment tree update function.
    // void update_path(int u, int v, ll val_to_add, SegTreeLazy<ll,ll>& seg_tree) {
    //     process_path(u, v, [&](int l_pos, int r_pos) {
    //         seg_tree.update(l_pos, r_pos, val_to_add);
    //     });
    //     // Similar LCA consideration if updates are not idempotent for single point double application.
    // }

    // Query for a single node u (value is at pos[u] in the segment tree)
    // int get_node_pos(int u) const {
    //     ASSERT(u >= 0 && u < n_nodes, "HLD::get_node_pos: Node index out of bounds.");
    //     return pos[u];
    // }
};

// ──────────────── DYNAMIC PROGRAMMING OPTIMIZATIONS ─────────────────

// Convex Hull Trick (CHT) - for minimizing m*x + c
// This version assumes:
// 1. Slopes 'm' are added in strictly DECREASING order.
// 2. Queries for 'x' are made in strictly INCREASING order.
struct ConvexHullTrickMinMono
{
    struct Line
    {
        ll m, c;
        ll eval(ll x) const { return m * x + c; }
        ld intersect(const Line &other) const
        {
            if (m == other.m)
            {
                return (c <= other.c) ? INF : -INF;
            }
            return static_cast<ld>(other.c - c) / (m - other.m);
        }
    };

    deque<Line> hull;
    int query_ptr = 0;

    void add_line(ll m, ll c)
    {
        if (!hull.empty())
        {
            ASSERT(m < hull.back().m, "ConvexHullTrickMinMono::add_line: Slopes must be strictly decreasing.");
        }
        while (sz(hull) >= 2)
        {                                 // Used sz
            Line l1 = hull[sz(hull) - 2]; // Used sz
            Line l2 = hull.back();        // hull.size() - 1 is hull.back()
            // Pass m, c to construct a temporary Line for intersect check, or pass m,c directly if intersect can take them
            // For simplicity, construct a temporary Line for the check against l1.
            if (l1.intersect({m, c}) <= l1.intersect(l2))
            { // Check with the incoming line {m,c}
                hull.pop_back();
            }
            else
            {
                break;
            }
        }
        hull.eb(m, c); // Used eb (emplace_back)

        // Clamp query_ptr to be within valid bounds after adding new line
        query_ptr = std::min(query_ptr, (int)sz(hull) - 1); // Used sz
    }

    ll query(ll x)
    {
        ASSERT(!hull.empty(), "ConvexHullTrickMinMono::query: Hull is empty.");

        // Advance query_ptr: while the next line in hull is better at x
        // query_ptr points to the current best line found for previous (or first) query.
        // We are looking for the line `hull[query_ptr]` such that `hull[query_ptr].eval(x)` is minimal.
        // The intersection point `hull[i].intersect(hull[i+1])` is where `hull[i+1]` becomes better than `hull[i]`.
        while (query_ptr + 1 < sz(hull) && // Used sz
               hull[query_ptr].intersect(hull[query_ptr + 1]) <= static_cast<ld>(x))
        {
            // The above condition means x is >= intersection point, so hull[query_ptr+1] is better or equal.
            // More direct: hull[query_ptr+1].eval(x) <= hull[query_ptr].eval(x)
            // However, using intersections is standard for CHT pointer advance.
            query_ptr++;
        }
        return hull[query_ptr].eval(x);
    }

    void clear()
    {
        hull.clear();
        query_ptr = 0;
    }
};

// ────────────────── OFFLINE QUERY ALGORITHMS ──────────────────

// Mo's Algorithm
// For offline processing of range queries.
// The user provides add, remove, and get_answer functions tailored to the problem.

struct MoQuery
{
    int l, r;  // 0-indexed query range [l, r]
    int id;    // Original index of the query
    int block; // Block index for Mo's sorting (l / BLOCK_SIZE)

    // Constructor to make query creation easier
    MoQuery(int _l = 0, int _r = 0, int _id = 0) : l(_l), r(_r), id(_id), block(0) {}
};

// Generic Mo's Algorithm function
// - arr: The input array.
// - queries: A vector of MoQuery objects. The `block` field will be set by this function.
// - add_fn(value, index): void, called when arr[index] (value) is added to the current window.
// - remove_fn(value, index): void, called when arr[index] (value) is removed from the current window.
// - get_ans_fn(): ResultType, returns the answer for the current window.
// - ResultType: The type of the answer for each query.
// Note: The state for add_fn, remove_fn, get_ans_fn (e.g., frequency counts, current answer) should be managed
//       by the context where these lambdas/functors are defined and captured by them.

template <typename ResultType, typename AddFn, typename RemoveFn, typename GetAnsFn>
vector<ResultType> mos_algorithm(
    const vll &arr, // Assuming array elements are long long, change if needed
    vector<MoQuery> &queries,
    AddFn add_fn,
    RemoveFn remove_fn,
    GetAnsFn get_ans_fn)
{
    if (queries.empty())
    {
        return vector<ResultType>();
    }
    // arr can be empty if queries specify ranges on a conceptual empty array, though unusual for typical Mo's.
    // If arr is empty but queries exist, behavior depends on how add/remove handle out-of-bounds if not guarded.
    // For safety, one might return default answers if arr is empty and queries are not.
    // However, typical Mo's assumes arr is non-empty if queries are non-empty and valid.

    int n = sz(arr);           // Used sz. Size of the array
    int q_count = sz(queries); // Used sz.
    vector<ResultType> answers(q_count);

    if (n == 0)
    { // Handle empty array case: all queries (if any) likely get default/problem-specific empty result
        for (const auto &query : queries)
        {
            // answers[query.id] = get_ans_fn(); // This might be unsafe if get_ans_fn expects some state from add/remove
            // It's better to let problem-specific logic decide what an empty array range means.
            // Or, the lambdas themselves should handle n=0 if they can be called.
            // For now, returning default-constructed ResultType if n=0.
            if (query.id < q_count)
                answers[query.id] = ResultType{};
        }
        return answers;
    }

    int block_size = static_cast<int>(sqrt(n)) + 1; // +1 to avoid 0 and improve performance

    // Precompute block for each query
    for (auto &query : queries)
    {
        query.block = query.l / block_size;
    }

    sort(all(queries), [&](const MoQuery &a, const MoQuery &b)
         {
             if (a.block != b.block)
             {
                 return a.block < b.block;
             }
             // "Snake order" or alternating R for minor optimization
             if (a.block % 2 == 0)
             { // Even block: sort by R ascending
                 return a.r < b.r;
             }
             return a.r > b.r; // Odd block: sort by R descending
         });

    int current_l = 0;
    int current_r = -1; // Current window is [current_l, current_r], initially empty

    for (const auto &query : queries)
    {
        int l = query.l;
        int r = query.r;

        // Adjust window [current_l, current_r] to [l, r]
        // Order of these loops matters for correctness of add/remove logic.
        // Typically: expand first, then shrink.

        // Shrink left pointer
        while (current_l > l)
        {
            current_l--;
            ASSERT(current_l >= 0 && current_l < n, "Mo's: current_l out of bounds during shrink left.");
            add_fn(arr[current_l], current_l);
        }
        // Expand right pointer
        while (current_r < r)
        {
            current_r++;
            ASSERT(current_r >= 0 && current_r < n, "Mo's: current_r out of bounds during expand right.");
            add_fn(arr[current_r], current_r);
        }
        // Shrink right pointer
        while (current_r > r)
        {
            ASSERT(current_r >= 0 && current_r < n, "Mo's: current_r out of bounds during shrink right.");
            remove_fn(arr[current_r], current_r);
            current_r--;
        }
        // Expand left pointer (effectively shrinking the window from left by moving current_l forward)
        while (current_l < l)
        {
            ASSERT(current_l >= 0 && current_l < n, "Mo's: current_l out of bounds during expand left.");
            remove_fn(arr[current_l], current_l);
            current_l++;
        }

        answers[query.id] = get_ans_fn();
    }
    return answers;
}

// ────────────────── GEOMETRIC ALGORITHMS ──────────────────

// Basic 2D Point/Vector structure and operations
// Uses long double (ld) for precision in geometric calculations.

struct Point
{
    ld x, y;

    Point(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}

    // Vector operations
    Point operator+(const Point &other) const { return Point(x + other.x, y + other.y); }
    Point operator-(const Point &other) const { return Point(x - other.x, y - other.y); }
    Point operator*(ld scalar) const { return Point(x * scalar, y * scalar); }
    Point operator/(ld scalar) const
    {
        ASSERT(std::abs(scalar) > EPS, "Point division by zero or near-zero scalar.");
        return Point(x / scalar, y / scalar);
    }

    // Dot product
    ld dot(const Point &other) const { return x * other.x + y * other.y; }
    // Cross product (2D: magnitude of the 3D cross product vector along z-axis)
    ld cross(const Point &other) const { return x * other.y - y * other.x; }

    // Squared Euclidean norm (magnitude squared)
    ld norm_sq() const { return x * x + y * y; }
    // Euclidean norm (magnitude)
    ld norm() const { return sqrt(norm_sq()); }

    // Distance to another point
    ld dist(const Point &other) const { return (*this - other).norm(); }
    // Squared distance to another point
    ld dist_sq(const Point &other) const { return (*this - other).norm_sq(); }

    // Angle of the vector from origin in radians, in range [-PI, PI]
    ld angle() const { return atan2(y, x); }

    // Rotate point around the origin by angle_rad radians counter-clockwise
    Point rotate(ld angle_rad) const
    {
        ld cos_a = cos(angle_rad);
        ld sin_a = sin(angle_rad);
        return Point(x * cos_a - y * sin_a, x * sin_a + y * cos_a);
    }

    // Normalize to a unit vector (if norm > 0)
    Point normalize() const
    {
        ld len_sq = norm_sq();
        if (len_sq < EPS * EPS)
            return Point(0, 0); // Or handle error, or return as is
        ld len = sqrt(len_sq);
        return Point(x / len, y / len);
    }

    // Comparison operators (handle floating point with EPS)
    bool operator==(const Point &other) const
    {
        ld dx = x - other.x, dy = y - other.y;
        return dx * dx + dy * dy < EPS * EPS;
    }
    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }
    // Lexicographical comparison for sorting (e.g., for sweep line)
    bool operator<(const Point &other) const
    {
        ld dx = x - other.x;
        if (dx * dx > EPS * EPS)
        {
            return x < other.x;
        }
        ld dy = y - other.y;
        if (dy * dy > EPS * EPS)
        {
            return y < other.y;
        }
        return false; // Points are considered equal for ordering if very close
    }
};

// Scalar multiplication (scalar * Point)
inline Point operator*(ld scalar, const Point &p) { return p * scalar; }

// To find orientation of ordered triplet (p, q, r).
// Returns:
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
inline int orientation(Point p, Point q, Point r)
{
    ld val = (q.y - p.y) * (r.x - q.x) -
             (q.x - p.x) * (r.y - q.y);
    // Or, using cross product: val = (q - p).cross(r - q);

    if (val * val < EPS * EPS)
        return 0;             // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
                              // Convention for cross product: (q-p) x (r-q)
                              // Positive if (r-q) is CCW from (q-p) => p-q-r is CCW
                              // Negative if (r-q) is CW from (q-p)  => p-q-r is CW
                              // Let's adjust for common interpretation: (q-p).cross(r-p)
                              // val = (q-p).cross(r-p) = (q.x-p.x)*(r.y-p.y) - (q.y-p.y)*(r.x-p.x)
                              // if val > 0, r is to the left of directed line pq -> CCW
                              // if val < 0, r is to the right of directed line pq -> CW
    // Re-evaluating based on (q-p).cross(r-q):
    // (q-p) = (qx-px, qy-py)
    // (r-q) = (rx-qx, ry-qy)
    // cross = (qx-px)(ry-qy) - (qy-py)(rx-qx)
    // If positive, (r-q) is CCW from (q-p). So p->q->r turns left (CCW).
    // If negative, (r-q) is CW from (q-p). So p->q->r turns right (CW).
    // My initial formula for val was: (qy-py)(rx-qx) - (qx-px)(ry-qy), which is -( (q-p).cross(r-q) )
    // So, if my val > 0 => cross < 0 => Clockwise.
    // If my val < 0 => cross > 0 => Counter-clockwise.
    // The current return: val > 0 -> 1 (CW), val < 0 -> 2 (CCW). This is consistent with my initial formula.
}

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
inline bool on_segment(Point p, Point q, Point r)
{
    // Check orientation first, ensure they are collinear before calling this.
    // ASSERT(orientation(p,q,r) == 0, "Points must be collinear for on_segment check.");
    // This check is implicit if orientation() returns 0 using EPS.
    return (q.x <= std::max(p.x, r.x) + EPS && q.x >= std::min(p.x, r.x) - EPS &&
            q.y <= std::max(p.y, r.y) + EPS && q.y >= std::min(p.y, r.y) - EPS);
}

// Convex Hull (Monotone Chain Algorithm)
// Returns a vector of points representing the convex hull in counter-clockwise order.
// Points on an edge of the hull (collinear) are included if they are vertices.
// If all points are collinear, it returns the two extreme points.
inline vector<Point> convex_hull(vector<Point> &points)
{
    int n_pts = sz(points); // Used sz, renamed n to n_pts
    if (n_pts <= 2)
    { // Hull is the points themselves if n_pts <= 2 (or empty if n=0)
        // Sort to ensure consistent order for n_pts=2 if desired, though not strictly necessary for hull definition
        sort(all(points)); // Used all
        return points;
    }

    sort(all(points)); // Used all
    // Remove duplicate points to simplify hull construction, common practice.
    // points.erase(unique(all(points)), points.end());
    // n_pts = sz(points);
    // if (n_pts <= 2) return points; // Re-check after unique
    // For now, assume unique points or let the algorithm handle them (collinear checks deal with it)

    vector<Point> upper_hull, lower_hull;

    // Build upper hull
    f(i, 0, n_pts)
    { // Used f macro, ensure n_pts is used
        // While last two points in upper_hull and points[i] make a non-left turn (CW or collinear)
        // (orientation == 1 (CW) or orientation == 0 (collinear and points[i] is not further))
        // We want strictly CCW turns for the upper hull points to be convex.
        // So pop if orientation is CW or Collinear where points[i] doesn't extend the line strictly left.
        // A simpler rule for upper hull: pop while orientation(hull[-2], hull[-1], points[i]) is not CCW (i.e., is CW or collinear)
        // orientation == 2 is CCW.
        while (sz(upper_hull) >= 2 && orientation(upper_hull[sz(upper_hull) - 2], upper_hull.back(), points[i]) != 2)
        { // Used sz
            upper_hull.pop_back();
        }
        upper_hull.eb(points[i]); // Used eb for Point construction
    }

    // Build lower hull
    rf(i, n_pts, 0)
    { // Used rf macro, ensure n_pts is used
        // While last two points in lower_hull and points[i] make a non-right turn (CCW or collinear)
        // We want strictly CW turns for the lower hull points relative to path direction.
        // So pop if orientation is CCW or Collinear.
        // orientation == 1 is CW
        while (sz(lower_hull) >= 2 && orientation(lower_hull[sz(lower_hull) - 2], lower_hull.back(), points[i]) != 1)
        { // Used sz
            lower_hull.pop_back();
        }
        lower_hull.eb(points[i]); // Used eb for Point construction
    }

    // Concatenate hulls
    // The first point of upper_hull is the same as the last point of lower_hull (leftmost).
    // The last point of upper_hull is the same as the first point of lower_hull (rightmost).
    // Remove duplicates at merge points.
    vector<Point> hull = upper_hull;
    // Add points from lower_hull, excluding its first and last (already in upper_hull)
    for (int i = 1; i < sz(lower_hull) - 1; ++i)
    {
        hull.eb(lower_hull[i]);
    }

    // Handle collinear case where upper and lower might be just two points.
    // If all points are collinear, hull will contain points sorted, then reverse sorted without middle points.
    // E.g. P1, P2, P3, P4 sorted. Upper: P1, P4. Lower: P4, P1. Result: P1, P4.
    // This seems fine. unique() after sort at start could simplify if strictly distinct vertices are needed.
    // The current logic should correctly form the hull boundary.
    // If n=3 and collinear, e.g. (0,0), (1,0), (2,0).
    // Sort: (0,0), (1,0), (2,0).
    // Upper: (0,0), (2,0) ( (1,0) is popped as (0,0)-(2,0)-(1,0) is not CCW, actually (0,0)-(1,0)-(2,0) is collinear, pop (1,0))
    // (0,0) -> add (0,0)
    // (1,0) -> add (1,0). UH: (0,0), (1,0)
    // (2,0) -> o( (0,0), (1,0), (2,0) ) = 0. Pop (1,0). UH: (0,0). Add (2,0). UH: (0,0), (2,0).
    // Lower (reverse from (2,0), (1,0), (0,0) ):
    // (2,0) -> add (2,0)
    // (1,0) -> add (1,0). LH: (2,0), (1,0)
    // (0,0) -> o( (2,0), (1,0), (0,0) ) = 0. Pop (1,0). LH: (2,0). Add (0,0). LH: (2,0), (0,0).
    // Hull = upper_hull = (0,0), (2,0).
    // lower_hull points to add: none (1 to sz-1 is empty range if sz=2).
    // Correct for collinear points: returns the two extreme points.

    return hull;
}

// Line Segment Intersection
// Checks if line segment p1-q1 intersects line segment p2-q2.
inline bool segments_intersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case: segments cross each other
    if (o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0)
    {
        if (o1 != o2 && o3 != o4)
        {
            return true;
        }
    }

    // Special Cases (collinear points)
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && on_segment(p1, p2, q1))
        return true;
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && on_segment(p1, q2, q1))
        return true;
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && on_segment(p2, p1, q2))
        return true;
    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && on_segment(p2, q1, q2))
        return true;

    return false; // Doesn't fall in any of the above cases
}

// Enum to represent the result of line intersection test
enum class LineIntersectionStatus
{
    INTERSECTING,
    COLLINEAR,
    PARALLEL_DISTINCT,
    LINES_ARE_POINTS // Edge case: one or both lines are defined by identical points
};

// Finds the intersection point of two lines defined by (p1, q1) and (p2, q2).
// Returns the status and populates intersection_point if they intersect at a single point.
inline LineIntersectionStatus get_line_intersection(Point p1, Point q1, Point p2, Point q2, Point &intersection_point)
{
    // Line segment p1q1 represented as p1 + t * (q1 - p1)
    // Line segment p2q2 represented as p2 + u * (q2 - p2)
    Point dir1 = q1 - p1;
    Point dir2 = q2 - p2;

    // Check for degenerate cases (lines are points)
    if (dir1.norm_sq() < EPS * EPS && dir2.norm_sq() < EPS * EPS)
    { // Both lines are points
        if ((p1 - p2).norm_sq() < EPS * EPS)
        { // Points are the same
            intersection_point = p1;
            return LineIntersectionStatus::COLLINEAR; // Or INTERSECTING, depends on convention for coinciding points
        }
        return LineIntersectionStatus::LINES_ARE_POINTS;
    }
    if (dir1.norm_sq() < EPS * EPS)
    { // Line 1 is a point
        if (orientation(p2, q2, p1) == 0)
        { // Point p1 lies on line p2q2
            intersection_point = p1;
            return LineIntersectionStatus::COLLINEAR;
        }
        return LineIntersectionStatus::LINES_ARE_POINTS;
    }
    if (dir2.norm_sq() < EPS * EPS)
    { // Line 2 is a point
        if (orientation(p1, q1, p2) == 0)
        { // Point p2 lies on line p1q1
            intersection_point = p2;
            return LineIntersectionStatus::COLLINEAR;
        }
        return LineIntersectionStatus::LINES_ARE_POINTS;
    }

    ld det = dir1.cross(dir2);

    if (det * det < EPS * EPS)
    { // Lines are parallel or collinear
        // Check if they are collinear: orientation of p1, q1, p2 should be 0
        if (orientation(p1, q1, p2) == 0)
        {
            // Could still be collinear and non-overlapping segments, but lines are collinear.
            // For line intersection, any point on the line could be an "intersection".
            // We don't set an intersection_point here as there are infinitely many.
            return LineIntersectionStatus::COLLINEAR;
        }
        return LineIntersectionStatus::PARALLEL_DISTINCT;
    }

    // Lines intersect at a single point
    // t = (p2 - p1).cross(dir2) / det
    // u = (p1 - p2).cross(dir1) / (-det)  which is (p2 - p1).cross(dir1) / det
    ld t = (p2 - p1).cross(dir2) / det;
    // ld u = (p1 - p2).cross(dir1) / (-det); // Can be used to check if intersection is on segment p2q2

    intersection_point = p1 + dir1 * t;
    return LineIntersectionStatus::INTERSECTING;
}

// Closest Pair of Points (Divide and Conquer)
// Helper function to calculate squared Euclidean distance (to avoid sqrt until the end)
inline ld dist_sq_helper(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// Helper struct to store a pair of points and their squared distance
struct PointPair
{
    Point p1, p2;
    ld dist_sq = INF; // Initialize with a large value

    PointPair() = default;
    PointPair(Point _p1, Point _p2) : p1(_p1), p2(_p2)
    {
        dist_sq = dist_sq_helper(p1, p2);
    }

    // Update if a new pair is closer
    void update(Point _p1, Point _p2)
    {
        ld d_sq = dist_sq_helper(_p1, _p2);
        if (d_sq < dist_sq)
        {
            dist_sq = d_sq;
            p1 = _p1;
            p2 = _p2;
        }
    }
    void update(const PointPair &other)
    {
        if (other.dist_sq < dist_sq)
        {
            dist_sq = other.dist_sq;
            p1 = other.p1;
            p2 = other.p2;
        }
    }
};

// Brute force closest pair for small number of points
inline PointPair closest_pair_brute_force(const vector<Point> &points_sorted_x, int start_idx, int end_idx)
{
    PointPair min_pair;
    min_pair.dist_sq = INF; // Ensure it starts at max
    if (end_idx - start_idx + 1 < 2)
        return min_pair; // Not enough points

    cf(i, start_idx, end_idx)
    { // Used cf macro
        cf(j, i + 1, end_idx)
        { // Used cf macro
            min_pair.update(points_sorted_x[i], points_sorted_x[j]);
        }
    }
    return min_pair;
}

// Recursive function for closest pair
inline PointPair closest_pair_recursive(vector<Point> &points_sorted_x, vector<Point> &temp_strip_points, int start_idx, int end_idx)
{
    int n_pts_rec = end_idx - start_idx + 1; // Renamed n to n_pts_rec
    if (n_pts_rec <= 3)
    { // Base case: brute force for 3 or fewer points
        // Need to sort this small subset by X if not already done by overall sort for the range.
        // However, points_sorted_x is already sorted by x for the current range.
        return closest_pair_brute_force(points_sorted_x, start_idx, end_idx);
    }

    int mid_idx = start_idx + (n_pts_rec / 2) - 1; // Adjusted for 0-indexed range [start_idx, end_idx]
    Point mid_point = points_sorted_x[mid_idx];

    PointPair delta_left = closest_pair_recursive(points_sorted_x, temp_strip_points, start_idx, mid_idx);
    PointPair delta_right = closest_pair_recursive(points_sorted_x, temp_strip_points, mid_idx + 1, end_idx);

    PointPair min_delta_pair = delta_left;
    min_delta_pair.update(delta_right);

    ld min_dist_sq_so_far = min_delta_pair.dist_sq;
    if (min_dist_sq_so_far < EPS * EPS)
    { // If distance is effectively zero (e.g. duplicate points)
        return min_delta_pair;
    }

    // Build the strip of points within sqrt(min_dist_sq_so_far) of the midline
    temp_strip_points.clear();
    temp_strip_points.reserve(end_idx - start_idx + 1); // Reserve maximum possible size
    cf(i, start_idx, end_idx)
    { // Used cf macro
        ld dx = points_sorted_x[i].x - mid_point.x;
        if (dx * dx < min_dist_sq_so_far)
        {
            temp_strip_points.eb(points_sorted_x[i]); // Used eb for Point construction
        }
    }

    // Sort strip points by y-coordinate
    sort(all(temp_strip_points), [](const Point &a, const Point &b) { // Used all
        return a.y < b.y;
    });

    // Find closest pair in the strip
    f(i, 0, sz(temp_strip_points))
    { // Used f and sz macros
        f(j, i + 1, sz(temp_strip_points))
        { // Used f and sz macros
            ld dy = temp_strip_points[j].y - temp_strip_points[i].y;
            if (dy * dy >= min_dist_sq_so_far)
                break; // Optimization: no need to check further points
            min_delta_pair.update(temp_strip_points[i], temp_strip_points[j]);
            // Update min_dist_sq_so_far for better pruning
            min_dist_sq_so_far = min_delta_pair.dist_sq;
        }
    }
    return min_delta_pair;
}

// Main function to find the closest pair of points
// Input: a vector of Points. The vector will be sorted by this function.
// Returns a PointPair struct containing the two closest points and their squared distance.
// If less than 2 points, dist_sq in PointPair will be INF.
inline PointPair find_closest_pair(vector<Point> &points)
{
    // int n = sz(points); // Original line using sz() macro which casts to ll
    int n_pts_main = sz(points); // Renamed n to n_pts_main, used points.size()
    if (n_pts_main < 2)
    {
        return PointPair(); // Returns with dist_sq = INF
    }

    // Sort points by x-coordinate. This is a prerequisite for the divide and conquer.
    sort(all(points), [](const Point &a, const Point &b) { // Used all
        ld dx = a.x - b.x;
        if (dx * dx > EPS * EPS)
            return a.x < b.x;
        return a.y < b.y; // Secondary sort by y for consistency / duplicate points
    });

    // It's good practice to check for duplicate points after sorting if they should be handled as 0 distance.
    // For now, the algorithm should still work but might do extra work or report 0 for identical points.
    // If points can be identical, min_dist_sq could be 0. Update method handles this.

    vector<Point> temp_strip_points;       // Temporary storage for strip points, passed by reference to avoid reallocations
    temp_strip_points.reserve(n_pts_main); // Reserve space to avoid reallocations

    return closest_pair_recursive(points, temp_strip_points, 0, n_pts_main - 1); // n_pts_main-1 is now int
}

#endif // CP_UTILS_HPP