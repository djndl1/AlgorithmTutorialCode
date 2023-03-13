#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utest.h"


unsigned long fibonacci_nontail(unsigned int n)
{
        if (n <= 1) return n;
        return fibonacci_nontail(n - 1) + fibonacci_nontail(n - 2);
}

static unsigned long fibonacci_tail_impl(unsigned int n, unsigned long previous, unsigned long current)
{
        if (n == 0) return previous;
        if (n == 1) return current;
        return fibonacci_tail_impl(n - 1, current, current + previous);
}

unsigned long fibonacci_tail(unsigned int n)
{
        return fibonacci_tail_impl(n, 0, 1);
}

/**
 * @brief the whole logic is basically the same as the tail recursive version above
 */
unsigned long fibonacci_iterative_reverse(unsigned int n)
{
        unsigned long previous = 0;
        unsigned long current = 1;
        for (unsigned int i = n; i > 0; i--) {
                unsigned long temp = previous;
                previous = current;
                current += temp;
        }

        return previous;
}

unsigned long fibonacci_iterative(unsigned int n)
{
        unsigned long previous = 0;
        unsigned long current = 1;
        for (unsigned int i = 0; i < n; i++) {
                unsigned long temp = previous;
                previous = current;
                current += temp;
        }

        return previous;
}

UTEST(FIB, ITER_REV)
{
        unsigned long zero_result = fibonacci_iterative_reverse(0);
        ASSERT_EQ(0, zero_result);

        unsigned long one_result = fibonacci_iterative_reverse(1);
        ASSERT_EQ(1, one_result);

        unsigned long two_result = fibonacci_iterative_reverse(2);
        ASSERT_EQ(1, two_result);

        unsigned long n_result = fibonacci_iterative_reverse(9);
        ASSERT_EQ(34, n_result);
}

UTEST(FIB, ITER)
{
        unsigned long zero_result = fibonacci_iterative(0);
        ASSERT_EQ(0, zero_result);

        unsigned long one_result = fibonacci_iterative(1);
        ASSERT_EQ(1, one_result);

        unsigned long two_result = fibonacci_iterative(2);
        ASSERT_EQ(1, two_result);

        unsigned long n_result = fibonacci_iterative(9);
        ASSERT_EQ(34, n_result);
}

UTEST(FIB, TAIL)
{
        unsigned long zero_result = fibonacci_tail(0);
        ASSERT_EQ(0, zero_result);

        unsigned long one_result = fibonacci_tail(1);
        ASSERT_EQ(1, one_result);

        unsigned long two_result = fibonacci_tail(2);
        ASSERT_EQ(1, two_result);

        unsigned long n_result = fibonacci_tail(9);
        ASSERT_EQ(34, n_result);
}

UTEST(FIB, NONTAIL)
{
        unsigned long zero_result = fibonacci_nontail(0);
        ASSERT_EQ(0, zero_result);

        unsigned long one_result = fibonacci_nontail(1);
        ASSERT_EQ(1, one_result);

        unsigned long two_result = fibonacci_nontail(2);
        ASSERT_EQ(1, two_result);

        unsigned long n_result = fibonacci_nontail(9);
        ASSERT_EQ(34, n_result);
}

UTEST_MAIN();