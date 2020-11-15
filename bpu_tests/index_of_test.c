//
// Created by hornedheck on 15.11.2020.
//

#include "lib/lib.h"
#include <stdlib.h>
#include <stdint.h>

int main() {
    print_s("INDEX OF TEST\n");

    const uint16_t size = 100;
    uint16_t items[size];
    for (uint16_t i = 0; i < size; ++i) {
        items[i] = random() % 1000;
    }
    items[90] = 1001;
    int16_t res = -1;
    for (uint16_t i = 0; i < size; ++i) {
        if (items[i] == 90) {
            res = i;
            break;
        }
    }

    exit_proc();

}
