#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <utest.h>

#include "xmalloc.h"

#define MAX(a, b) ((a > b) ? a : b)

int max_subsequence_sum_cubic_complexity(int a[], size_t n)
{
	int max_sum = 0;
	int best_i = -1;
	int best_j = -1;

	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int this_sum = 0;
			for (int k = i; k <= j; k++) {
				this_sum += a[k];
			}
			if (this_sum > max_sum) { /* update max_sum, best_i, best_j */
				max_sum = this_sum;
				best_i = i;
				best_j = j;
			}
		}
	}
	return (max_sum);
}

int max_subsequence_sum_square_complexity(int a[], size_t n)
{
	int this_sum, max_sum, best_i, best_j;
	max_sum = 0;
	best_i = best_j = -1;

	for (size_t i = 0; i < n; i++) {
		this_sum = 0; // previous sum is saved with j increasing
		for (size_t j = i; j < n; j++) {
			this_sum += a[j];
			if (this_sum > max_sum) {
				max_sum = this_sum;
				best_i = i;
				best_j = j;
			}
		}
	}
	return (max_sum);
}

int max_sub_sum(int a[], size_t left, size_t right);

int max_subsequence_sum_recursive_nlogn_complexity(int a[], size_t n)
{
	return max_sub_sum(a, 0, n - 1);
}

int max3(int a, int b, int c)
{
	int ab_max = MAX(a, b);
	int bc_max = MAX(b, c);
	return MAX(ab_max, bc_max);
}

int max_sub_sum(int a[], size_t left, size_t right)
{
	if (left == right)
		return a[left];

	int center = (left + right) / 2;
	int max_left_sum = max_sub_sum(a, left, center);
	int max_right_sum = max_sub_sum(a, center + 1, right);

	int max_left_border_sum = 0;
	int left_border_sum = 0;
	for (size_t i = center; i >= left; i--) {
		left_border_sum += a[i];
		if (left_border_sum > max_left_border_sum)
			max_left_border_sum = left_border_sum;

		if (i == 0) {
			break;
		}
	}

	int max_right_border_sum = 0;
	int right_border_sum = 0;
	for (size_t i = center + 1; i <= right; i++) {
		right_border_sum += a[i];
		if (right_border_sum > max_right_border_sum)
			max_right_border_sum = right_border_sum;

		if (i == SIZE_MAX) {
			break;
		}
	}

	return max3(max_left_sum, max_right_sum, max_left_border_sum + max_right_border_sum);
}

/**
 * one-pass read without storing in the main memory, online algorithms, which requires constant space
 * and runs in linear time
 */
int max_subsequence_sum_n_complexity(int a[], size_t n)
{
	int this_sum = 0, max_sum = 0;
	int i = 0;
	int j;
	int best_i = -1;
	int best_j = -1;

	for (j = 0; j < n; j++) {
		this_sum += a[j];
		if (this_sum > max_sum) {
			max_sum = this_sum;
			best_i = i;
			best_j = j;
		} else if (this_sum < 0) { 
			// if the sum is negative, any positive integers afterwards will have to be used for compensation first
			// better drop the subsequence;
			// or the sum of any subsequence after this one must be greater than this one
			i = j + 1;
			this_sum = 0;
		}
	}
	return (max_sum);
}

int *generate_test_array(size_t array_len)
{
	srand(time(NULL));

	int *array = xmalloc(sizeof(int) * array_len);
	for (size_t i = 0; i < array_len; i++) {
		array[i] = rand() / 10000;
	}

	return array;
}

typedef int test_impl_t(int[], size_t);

void test_implementation(test_impl_t f, size_t len, char *name)
{
	int *a = generate_test_array(len);

	printf("%s: testing\n", name);
	int sum = f(a, len);

	printf("%s: %d\n", name, sum);
}

UTEST(MaxSubsequenceSum, CubicHundred) // 0.0007 second
{
	test_implementation(max_subsequence_sum_cubic_complexity, 100, "Cubic Implementation 100:");
}

UTEST(MaxSubsequenceSum, CubicThousand) // about 0.7 second
{
	test_implementation(max_subsequence_sum_cubic_complexity, 1000, "Cubic Implementation 1000:");
}

UTEST(MaxSubsequenceSum, CubicMyriad) // about 10 minutes
{
	//test_implementation(max_subsequence_sum_cubic_complexity, 10000, "Cubic Implementation 10000:");
}

UTEST(MaxSubsequenceSum, SquareHundred) // 0.245979ms
{
	test_implementation(max_subsequence_sum_square_complexity, 100, "Square Implementation 100:");
}

UTEST(MaxSubsequenceSum, SquareThousand) // 1.58903ms
{
	test_implementation(max_subsequence_sum_square_complexity, 1000, "Square Implementation 100:");
}

UTEST(MaxSubsequenceSum, SquareMyriad) // 146.860659ms
{
	test_implementation(max_subsequence_sum_square_complexity, 10000, "Square Implementation 100:");
}

UTEST(MaxSubsequenceSum, RecursiveHundred)
{
	test_implementation(max_subsequence_sum_recursive_nlogn_complexity, 100, "Recursive Implementation 100:");
}

UTEST(MaxSubsequenceSum, RecursiveThousand)
{
	test_implementation(max_subsequence_sum_recursive_nlogn_complexity, 1000, "Recursive Implementation 1000:");
}

UTEST(MaxSubsequenceSum, RecursiveMyriad)
{
	test_implementation(max_subsequence_sum_recursive_nlogn_complexity, 10000, "Recursive Implementation 10000:");
}

UTEST(MaxSubsequenceSum, NHundred)
{
	test_implementation(max_subsequence_sum_n_complexity, 100, "N Complexity Implementation 100:");
}

UTEST(MaxSubsequenceSum, NThousand)
{
	test_implementation(max_subsequence_sum_n_complexity, 1000, "N Complexity Implementation 1000:");
}

UTEST(MaxSubsequenceSum, NMyriad)
{
	test_implementation(max_subsequence_sum_n_complexity, 10000, "N Complexity Implementation 10000:");
}

UTEST_MAIN();