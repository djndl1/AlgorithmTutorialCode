#include <stdint.h>

#include "utest.h"


int gcd_tail(int a, int b)
{
        if (b == 0) return a;

        return gcd_tail(b, a % b);
}

int gcd_iter(int a, int b)
{
        while (b != 0) {
                int temp = a;
                a = b;
                b = temp % b;
        }
        return a;
}

UTEST(GCD, ITER) {
        ASSERT_EQ(5, gcd_iter(20, 25));
}

UTEST(GCD, TAIL) {
        ASSERT_EQ(5, gcd_tail(20, 25));
}

UTEST_MAIN();
