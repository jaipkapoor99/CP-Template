#include "cp_utils.hpp"

void solve(int test_case_num) 
{
    int n;
    read(n);
    DEBUG("Test case", test_case_num, "Input n:", n);
    
    // Simple calculation
    ll result = n * (n + 1) / 2;  // Sum of 1 to n
    TRACE("Calculated result:", result);
    
    print(result);
}

int main()
{
    FASTINOUT;
    int t;
    read(t);
    
    f(i, 0, t)
        solve(i + 1);
        
    return 0;
} 