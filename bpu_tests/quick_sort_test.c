//
// Created by hornedheck on 15.11.2020.
//

#include "lib/lib.h"
#include <stdlib.h>

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

    print_s("QUICK SORT TEST\n");

    const int N = 10;
    int a[10] = {5, 3, 5, 6, 7, 1, 3, 5, 6, 1};
    quicksort(a, 0, N - 1);

    const int M = 100;
    int b[100];
    for (int i = 0; i < 100; ++i) {
        b[i] = (int) random() % 1000;
    }
    quicksort(b, 0, M - 1);

    exit_proc();
}