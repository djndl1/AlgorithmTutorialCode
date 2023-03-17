#include <stdlib.h>
#include <stdint.h>

#include <stdbool.h>

#include "utest.h"
#include <math.h>

/**
 * @brief check if a queen at a certain position is compatible with the all existing queens
 *
 * @param chess_board the array representing the positions of all the existing queens
 * @param row the row number of the queen to check
 * @param col the column number of the queen to check
 */
bool compatible_with(int chess_board[], int row, int col)
{
        for (unsigned int j = 0; j < row; j++) {
                if (chess_board[j] == col) return false;
                if (abs(chess_board[j] - col) == row - j) return false;
        }
        return true;
}

void print_configuration(int chess_board[], int n)
{
        for (int i = 0; i < n; i++) {
                printf("%d: %d ", i, chess_board[i]);
        }
        putchar('\n');
}

/**
 * @brief find the n-th queen's position in the chess board
 *
 * @param chess_board queens' positions
 * @param rownum the n-th row on which a queen should be placed
 * @param n the size of the chess board
 * @return int the solution count
 */
int n_queens(int chess_board[], int rownum, int n)
{
        int cnt = 0;
        for (int i = 0; i < n; i++) { // test against each column for this row
                if (compatible_with(chess_board, rownum, i)) {
                        chess_board[rownum] = i;
                        if (rownum == n - 1) {
                                print_configuration(chess_board, n);
                                cnt++;
                        } else {
                                cnt += n_queens(chess_board, rownum + 1,  n);
                        }
                } // if this row yields no solution, immediate bail out and
                  // get back to the next solution of the last row by iterating over i
        }

        return cnt;
}

UTEST(NQUEENS, EIGHT) {
        int chess_board[8] = { -1 };
        int cnt = n_queens(chess_board, 0, 8);

        ASSERT_EQ(92, cnt);
}

UTEST_MAIN();