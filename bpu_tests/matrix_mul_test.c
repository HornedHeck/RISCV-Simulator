//
// Created by hornedheck on 15.11.2020.
//

#include "lib/lib.h"

const int M = 10;

void matrix_mul(int a[M][M], int b[M][M], int c[M][M]) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < M; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main() {

    print_s("MATRIX MUL TEST\n");

    int A[M][M], B[M][M], C[M][M];
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            A[i][j] = i;
            B[i][j] = j;
        }
    }

    matrix_mul(A, B, C);

    exit_proc();
}