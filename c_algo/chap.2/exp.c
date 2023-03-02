#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utest.h"

/**
 * O(logn)
 */
int ipow(int x, unsigned int n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	if (n % 2 == 0)
		return (ipow(x * x, n / 2));
	else
		return (ipow(x, n - 1) * x); // convert the odd case to even
}

UTEST(POW, One)
{
        ASSERT_EQ(1, ipow(1, 0));
}

UTEST_MAIN();