#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utest.h"

unsigned long factorial_nontail(unsigned int n)
{
        if (n == 0 || n == 1) return 1;
        else {
                return n * factorial_nontail(n - 1);
        }
}

static unsigned long factorial_tail_impl(unsigned int n, unsigned long result)
{
        if (n == 0 || n == 1) return result;
        else {
                return factorial_tail_impl(n - 1, n * result);
        }
}

unsigned long factorial_tail(unsigned int n)
{
        return factorial_tail_impl(n, 1);
}

unsigned long factorial_iter(unsigned int n)
{
        if (n == 0 || n == 1) return 0;

        unsigned long result = 1;
        for (unsigned int i = n; i > 0; i--) {
                result *= i;
        }

        return result;
}

UTEST(FACTORIAL, ITER)
{
        unsigned long result = factorial_iter(5);

        ASSERT_EQ(120, result);
}

UTEST(FACTORIAL, NON_TAIL)
{
        unsigned long result = factorial_nontail(5);

        ASSERT_EQ(120, result);
}

UTEST(FACTORIAL, TAIL)
{
        unsigned long result = factorial_tail(5);

        ASSERT_EQ(120, result);
}

UTEST_MAIN();