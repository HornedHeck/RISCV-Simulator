//
// Created by hornedheck on 17.11.2020.
//

#include "lib/lib.h"
#include <string.h>

#define M 10

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

void foo(int i) {
    if ((i & 3) == 0) {
        1 + 1;
    }
}

void baz(int i) {
    if (i % 3 == 0) {
        1 + 1;
    }
}

void quicksort(int *a, int begin, int end) {
    int i, j, t, pivot;
    if (begin > end)
        return;

    pivot = a[begin];
    i = begin;
    j = end;
    while (i != j) {
        while (a[j] >= pivot && i < j)
            j--;
        while (a[i] <= pivot && i < j)
            i++;
        if (i < j) {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    a[begin] = a[i];
    a[i] = pivot;

    quicksort(a, begin, i - 1);
    quicksort(a, i + 1, end);
}

int main() {
    print_s("ALIASING TEST\n");

    int A[M][M], B[M][M], C[M][M];
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            A[i][j] = i;
            B[i][j] = j;
        }
    }

    matrix_mul(A, B, C);


    int array[20];
    for (int i = 0; i < 20; ++i) {
        array[i] = (100 / i + 20 * i - i * i) % 100;
    }

    if ((2023 & 1) == 1) {
        1 + 2;
    }

    if (1 == 2) {
        M + 3;
    }

    for (int i = 0; i < 19; ++i) {
        int p = -1;
        int v = array[i];
        for (int j = i + 1; j < 20; ++j) {
            if (v > array[j]) {
                p = j;
                v = array[j];
            }
            if (p != -1) {
                array[i] ^= array[j] ^= array[i] ^= array[j];
            }
        }
    }

    for (int i = 0; i < 20; ++i) {
        if ((i & 1) == 0) {
            foo(i);
        } else {
            baz(i);
        }
    }


    int a[10] = {5, 3, 5, 6, 7, 1, 3, 5, 6, 1};
    quicksort(a, 0, 9);

    exit_proc();
}