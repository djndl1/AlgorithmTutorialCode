#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "utest.h"

/**
 * logn time complexity
 * after the first two iterations, the remainder is at most half of its original values
 * theorem: if m > n, then m mod n < m / 2:
 * proof:
 *      if n < m / 2, then m mod n < n < m / 2
 *      if n > m / 2, then m = n * 1 + rem and rem = m - n < m / 2
 */
unsigned int gcd(unsigned int m, unsigned int n)
{
	unsigned int rem;
	while (n > 0) { // if m < n, it swaps m and n
		rem = m % n;
		m = n;
		n = rem;
	}
	return m;
}

UTEST(GCD, Simple)
{
        unsigned int result = gcd(50, 15);

        ASSERT_EQ(5, result);
}

UTEST_MAIN();