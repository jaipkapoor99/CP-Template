#include "../include/cp_utils.hpp"
using namespace std;

void test_dsu()
{
    DEBUG_SECTION("🔗 Disjoint Set Union (DSU) Testing");
    TIMER_START(dsu_test);
    
    DEBUG_FUNC();
    DSU dsu(5);
    DEBUG_VAR(dsu.num_sets());
    
    INFO("Uniting elements 0 and 1...");
    dsu.unite(0, 1);
    DEBUG("After unite(0,1):", "connected(0,1) =", dsu.connected(0, 1));
    
    INFO("Uniting elements 2 and 3...");
    dsu.unite(2, 3);
    DEBUG("After unite(2,3):", "connected(2,3) =", dsu.connected(2, 3));
    
    ASSERT(dsu.connected(0, 1), "DSU: 0 and 1 should be connected");
    ASSERT(!dsu.connected(0, 2), "DSU: 0 and 2 should not be connected");
    ASSERT(dsu.size(0) == 2, "DSU: Size of component containing 0 should be 2");
    
    DEBUG_VAR(dsu.size(0));
    DEBUG_VAR(dsu.size(2));
    DEBUG_VAR(dsu.num_sets());
    
    TIMER_END(dsu_test);
    TEST_PASS("DSU Basic Operations");
}

void test_fenwick()
{
    DEBUG_SECTION("🌳 Fenwick Tree (Binary Indexed Tree) Testing");
    TIMER_START(fenwick_test);
    
    DEBUG_FUNC();
    FenwickTree<ll> ft(5);
    DEBUG("Created Fenwick Tree of size 5");
    
    INFO("Adding values to Fenwick Tree...");
    ft.update(0, 5);
    DEBUG("Updated index 0 with value 5");
    ft.update(2, 3);
    DEBUG("Updated index 2 with value 3");
    ft.update(4, 7);
    DEBUG("Updated index 4 with value 7");
    
    ll prefix_sum = ft.query(2);
    DEBUG_VAR(prefix_sum);
    ASSERT(prefix_sum == 8, "Fenwick: Prefix sum [0,2] should be 8");
    
    ll range_sum = ft.query_range(2, 4);
    DEBUG_VAR(range_sum);
    ASSERT(range_sum == 10, "Fenwick: Range sum [2,4] should be 10");
    
    TIMER_END(fenwick_test);
    TEST_PASS("Fenwick Tree Operations");
}

void test_geometry()
{
    DEBUG_SECTION("📐 Geometry Algorithms Testing");
    TIMER_START(geometry_test);
    
    DEBUG_FUNC();
    Point p1(0, 0);
    Point p2(3, 4);
    
    DEBUG("Point p1:", p1.x, p1.y);
    DEBUG("Point p2:", p2.x, p2.y);
    
    ld distance = p1.dist(p2);
    DEBUG_VAR(distance);
    ASSERT(abs(distance - 5.0) < EPS, "Geometry: Distance should be 5");
    
    ld norm = p2.norm();
    DEBUG_VAR(norm);
    ASSERT(abs(norm - 5.0) < EPS, "Geometry: Norm should be 5");

    INFO("Testing convex hull algorithm...");
    vector<Point> points = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
    DEBUG("Input points:", points);
    
    auto hull = convex_hull(points);
    DEBUG("Convex hull:", hull);
    DEBUG_VAR(hull.size());
    ASSERT(hull.size() >= 3, "Geometry: Convex hull should have at least 3 points");
    
    TIMER_END(geometry_test);
    TEST_PASS("Geometry Algorithms");
}

void test_string_algorithms()
{
    DEBUG_SECTION("🔤 String Algorithms Testing");
    TIMER_START(string_test);
    
    DEBUG_FUNC();
    string text = "abcabcabc";
    string pattern = "abc";
    DEBUG_VAR(text);
    DEBUG_VAR(pattern);
    
    INFO("Running KMP string search...");
    auto occurrences = kmp_search(text, pattern);
    DEBUG("KMP occurrences:", occurrences);
    DEBUG_VAR(occurrences.size());
    ASSERT(occurrences.size() == 3, "KMP: Should find 3 occurrences");

    INFO("Testing string hashing...");
    StringHashing sh(text);
    auto hash1 = sh.get_hash(0, 2);
    auto hash2 = sh.get_hash(3, 5);
    DEBUG("Hash of substring [0,2]:", hash1);
    DEBUG("Hash of substring [3,5]:", hash2);
    ASSERT(hash1.first == hash2.first && hash1.second == hash2.second, 
           "String Hashing: Same substrings should have same hash");
    
    TIMER_END(string_test);
    TEST_PASS("String Algorithms");
}

void test_number_theory()
{
    DEBUG_SECTION("🔢 Number Theory Testing");
    TIMER_START(number_theory_test);
    
    DEBUG_FUNC();
    
    INFO("Testing primality checks...");
    bool is_17_prime = isPrime(17);
    bool is_15_prime = isPrime(15);
    DEBUG("isPrime(17):", is_17_prime);
    DEBUG("isPrime(15):", is_15_prime);
    ASSERT(is_17_prime, "Number Theory: 17 should be prime");
    ASSERT(!is_15_prime, "Number Theory: 15 should not be prime");

    INFO("Testing sieve of Eratosthenes...");
    Sieve sieve(100);
    DEBUG("Sieve created for numbers up to 100");
    DEBUG("sieve.is_prime[17]:", sieve.is_prime[17]);
    DEBUG("sieve.is_prime[15]:", sieve.is_prime[15]);
    DEBUG("First 10 primes:", vector<int>(sieve.primes.begin(), sieve.primes.begin() + min(10, (int)sieve.primes.size())));
    
    ASSERT(sieve.is_prime[17], "Sieve: 17 should be prime");
    ASSERT(!sieve.is_prime[15], "Sieve: 15 should not be prime");
    
    TIMER_END(number_theory_test);
    TEST_PASS("Number Theory");
}

void test_modular_arithmetic()
{
    DEBUG_SECTION("🧮 Modular Arithmetic Testing");
    TIMER_START(modular_test);
    
    DEBUG_FUNC();
    
    INFO("Testing modular addition...");
    ll result_add = Mint::add(500000000, 600000000);
    DEBUG("Mint::add(500000000, 600000000):", result_add);
    // 500000000 + 600000000 = 1100000000, mod 1000000007 = 99999993
    ASSERT(result_add == 99999993, "Modular: Addition should wrap correctly");

    INFO("Testing modular multiplication...");
    ll result_mul = Mint::mul(1000000000, 2);
    DEBUG("Mint::mul(1000000000, 2):", result_mul);
    // 1000000000 * 2 = 2000000000, mod 1000000007 = 999999993
    ASSERT(result_mul == 999999993, "Modular: Multiplication should work correctly");
    
    INFO("Testing modular exponentiation...");
    ll result_pow = Mint::power(2, 10);
    DEBUG("Mint::power(2, 10):", result_pow);
    ASSERT(result_pow == 1024, "Modular: 2^10 should be 1024");
    
    TIMER_END(modular_test);
    TEST_PASS("Modular Arithmetic");
}

void run_comprehensive_tests()
{
    DEBUG_SECTION("🧪 COMPREHENSIVE TEMPLATE TESTING");
    
    INFO("Starting template component verification...");
    
    PROGRESS(0, 6);
    test_dsu();
    PROGRESS(1, 6);
    
    test_fenwick();
    PROGRESS(2, 6);
    
    test_geometry();
    PROGRESS(3, 6);
    
    test_string_algorithms();
    PROGRESS(4, 6);
    
    test_number_theory();
    PROGRESS(5, 6);
    
    test_modular_arithmetic();
    PROGRESS(6, 6);
    
    SUCCESS("🎉 ALL TESTS COMPLETED SUCCESSFULLY! 🎉");
}

int main()
{
    FASTINOUT;

    // Header with colorful banner
    DEBUG_SECTION("🚀 COMPETITIVE PROGRAMMING TEMPLATE VALIDATOR");
    INFO("Initializing comprehensive test suite...");
    TRACE("Test execution started");
    
    TIMER_START(total_execution);

    try
    {
        run_comprehensive_tests();
        
        DEBUG_SECTION("📊 TEST RESULTS SUMMARY");
        SUCCESS("Template verification complete - all components working!");
        cout << BRIGHT_GREEN << "✅ Template verification complete - all components working!" << RESET << NL;
    }
    catch (const exception &e)
    {
        TEST_FAIL("Template Test Suite");
        WARNING("Test suite failed with exception");
        DEBUG("Exception details:", e.what());
        return 1;
    }

    TIMER_END(total_execution);
    
    DEBUG_SECTION("🏁 EXECUTION COMPLETE");
    INFO("Template testing finished successfully!");
    
    return 0;
}