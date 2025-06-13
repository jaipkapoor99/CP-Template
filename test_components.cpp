#include "cp_utils.hpp"
using namespace std;

void test_dsu()
{
    DEBUG("Testing DSU...");
    DSU dsu(5);
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    ASSERT(dsu.connected(0, 1), "DSU: 0 and 1 should be connected");
    ASSERT(!dsu.connected(0, 2), "DSU: 0 and 2 should not be connected");
    ASSERT(dsu.size(0) == 2, "DSU: Size of component containing 0 should be 2");
    DEBUG("DSU tests passed!");
}

void test_fenwick()
{
    DEBUG("Testing Fenwick Tree...");
    FenwickTree<ll> ft(5);
    ft.update(0, 5);
    ft.update(2, 3);
    ft.update(4, 7);
    ASSERT(ft.query(2) == 8, "Fenwick: Prefix sum [0,2] should be 8");
    ASSERT(ft.query_range(2, 4) == 10, "Fenwick: Range sum [2,4] should be 10");
    DEBUG("Fenwick Tree tests passed!");
}

void test_geometry()
{
    DEBUG("Testing Geometry...");
    Point p1(0, 0);
    Point p2(3, 4);
    ASSERT(abs(p1.dist(p2) - 5.0) < EPS, "Geometry: Distance should be 5");
    ASSERT(abs(p2.norm() - 5.0) < EPS, "Geometry: Norm should be 5");

    // Test convex hull
    vector<Point> points = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    auto hull = convex_hull(points);
    ASSERT(hull.size() >= 3, "Geometry: Convex hull should have at least 3 points");
    DEBUG("Geometry tests passed!");
}

void test_string_algorithms()
{
    DEBUG("Testing String Algorithms...");
    string text = "abcabcabc";
    string pattern = "abc";
    auto occurrences = kmp_search(text, pattern);
    ASSERT(occurrences.size() == 3, "KMP: Should find 3 occurrences");

    StringHashing sh(text);
    auto hash1 = sh.get_hash(0, 2);
    auto hash2 = sh.get_hash(3, 5);
    ASSERT(hash1.first == hash2.first && hash1.second == hash2.second, "String Hashing: Same substrings should have same hash");
    DEBUG("String algorithms tests passed!");
}

void test_number_theory()
{
    DEBUG("Testing Number Theory...");
    ASSERT(isPrime(17), "Number Theory: 17 should be prime");
    ASSERT(!isPrime(15), "Number Theory: 15 should not be prime");

    Sieve sieve(100);
    ASSERT(sieve.is_prime[17], "Sieve: 17 should be prime");
    ASSERT(!sieve.is_prime[15], "Sieve: 15 should not be prime");
    DEBUG("Number theory tests passed!");
}

void test_modular_arithmetic()
{
    DEBUG("Testing Modular Arithmetic...");
    // 500000000 + 600000000 = 1100000000, mod 1000000007 = 99999993
    ASSERT(Mint::add(500000000, 600000000) == 99999993, "Modular: Addition should wrap correctly");
    // 1000000000 * 2 = 2000000000, mod 1000000007 = 999999993
    ASSERT(Mint::mul(1000000000, 2) == 999999993, "Modular: Multiplication should work correctly");
    DEBUG("Modular arithmetic tests passed!");
}

int main()
{
    FASTINOUT;

    DEBUG("Starting comprehensive template tests...");

    try
    {
        test_dsu();
        test_fenwick();
        test_geometry();
        test_string_algorithms();
        test_number_theory();
        test_modular_arithmetic();

        DEBUG(GREEN, "🎉 ALL TESTS PASSED! Template is working correctly!", RESET);
        cout << "✅ Template verification complete - all components working!" << NL;
    }
    catch (const exception &e)
    {
        DEBUG(RED, "❌ Test failed with exception:", e.what(), RESET);
        return 1;
    }

    return 0;
}