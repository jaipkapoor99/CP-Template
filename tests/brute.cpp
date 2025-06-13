#include "../include/cp_utils.hpp"

// TODO: Implement your brute force solution here
// This should solve the same problem as main.cpp but with a simpler, slower approach
void solve_brute(int test_case_num) 
{
    int n;
    read(n);
    
    // Example brute force: sum 1 to n using a loop instead of formula
    ll result = 0;
    for (int i = 1; i <= n; i++) {
        result += i;
    }
    
    print(result);
}

int main()
{
    FASTINOUT;
    int t;
    read(t);
    
    f(i, 0, t)
        solve_brute(i + 1);
        
    return 0;
}
