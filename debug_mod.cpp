#include "cp_utils.hpp"

int main()
{
    FASTINOUT;

    ll add_result = Mint::add(500000000, 600000000);
    ll mul_result = Mint::mul(1000000000, 2);

    DEBUG("Add result:", add_result);
    DEBUG("Mul result:", mul_result);
    DEBUG("MOD_CONST:", MOD_CONST);

    // Manual calculation
    ll manual_add = (500000000LL + 600000000LL) % MOD_CONST;
    ll manual_mul = (1000000000LL * 2LL) % MOD_CONST;

    DEBUG("Manual add:", manual_add);
    DEBUG("Manual mul:", manual_mul);

    return 0;
}