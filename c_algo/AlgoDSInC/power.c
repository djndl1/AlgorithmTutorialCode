#include <stdint.h>

#include "utest.h"

long power_nontail(long base, long exp)
{
        if (exp == 0) return 1;
        else if (exp < 0) return power_nontail(1 / base, -exp);

        long p = 1;
        if (exp % 2 == 1) p = base;

        return p * power_nontail(base * base, exp / 2);
}

static long power_tail_impl(long base, long exp, long result)
{
        if (exp == 0) return result;
        else if (exp < 0) return power_tail_impl(1 / base, -exp, result);

        long p = result;
        if (exp % 2 == 1) p = base * result;

        return power_tail_impl(base * base, exp / 2, p);
}

long power_tail(long base, long exp)
{
        return power_tail_impl(base, exp, 1);
}

long power_iter(long base, long exp)
{
        if (exp < 0) return power_iter(1 / base, -exp);

        long result = 1;
        while (exp != 0) {
                if (exp % 2 == 1) result *= base;

                base *= base;
                exp /= 2;
        }

        return result;
}

UTEST(POWER, ITER)
{
        ASSERT_EQ(9765625, power_iter(5, 10));
}

UTEST(POWER, TAIL)
{
        ASSERT_EQ(9765625, power_tail(5, 10));
}

UTEST(POWER, NONTAIL)
{
        ASSERT_EQ(9765625, power_nontail(5, 10));
}

UTEST_MAIN();