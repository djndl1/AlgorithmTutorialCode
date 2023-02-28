#include <stdio.h>
#include <stdlib.h>

#include "utest.h"

/**
 * useful for relatively static data since sorting is not frequent
 */
int binary_search(int a[], int x, size_t n)
{
	if (n == 0)
		return -1;

        // neither indexers cannot be unsigned
	int low = 0;
	int high = n - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (a[mid] < x)
			low = mid + 1;
		else if (a[mid] > x)
			high = mid - 1;
		else
			return mid; /* found */
	}
	return -1;
}

UTEST(BIN_SEARCH, ODD)
{
	int a[] = { 1, 2, 3, 4, 6, 8, 9, 12, 13 };

	int pos = binary_search(a, 4, sizeof(a) / sizeof(a[0]));

	ASSERT_EQ(3, pos);
}

UTEST(BIN_SEARCH, EVEN)
{
	int a[] = { 1, 2, 3, 4, 6, 8, 9, 12 };

	int pos = binary_search(a, 4, sizeof(a) / sizeof(a[0]));

	ASSERT_EQ(3, pos);
}

UTEST_MAIN();