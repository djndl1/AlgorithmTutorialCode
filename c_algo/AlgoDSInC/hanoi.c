#include <stdint.h>

#include "utest.h"

typedef enum hanoi_tower {
	TOWER_A,
	TOWER_B,
	TOWER_C,
} hanoi_tower_t;

const char *get_hanoi_name(hanoi_tower_t tower)
{
	switch (tower) {
	case TOWER_A:
		return "TOWER_A";
	case TOWER_B:
		return "TOWER_B";
	case TOWER_C:
		return "TOWER_C";
	default:
		return NULL;
	}
}

/**
 * @brief O(2^n)
 * @param A the source tower
 * @param B the relay tower
 * @param C the destination tower
 * @param n the number of disks
 */
void hanoi_nontail(hanoi_tower_t A, hanoi_tower_t B, hanoi_tower_t C, int n)
{
        if (n == 0) return;
	hanoi_nontail(A, C, B, n - 1);
	printf("Moving %d-th disk from tower %s to %s\n", n, get_hanoi_name(A), get_hanoi_name(C));
	hanoi_nontail(B, A, C, n - 1);
}

UTEST(HANOI, TAIL)
{
        hanoi_nontail(TOWER_A, TOWER_B, TOWER_C, 3);
}

UTEST(HANOI, NONTAIL)
{
        hanoi_nontail(TOWER_A, TOWER_B, TOWER_C, 3);
}

UTEST_MAIN();