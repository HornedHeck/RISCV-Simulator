//
// Created by hornedheck on 15.11.2020.
//

#include <stdint.h>
#include "lib/lib.h"

int main() {

    print_s("IFS TEST\n");

    uint16_t d = 0;
    uint32_t a = 10;
    uint32_t b = 12;
    uint32_t c = 14;

    // Test benefits of global history
    if (a == c) {
        ++d;
    }

    if (b == c) {
        ++d;
    }

    if (a == c || b == c) {
        ++d;
    }

    if (a != c) {
        ++d;
    }

    if (a != b) {
        ++d;
    }

    if (3 == 1) {
        ++d;
    }

    if (2 == 2) {
        ++d;
    }

    if (2 == 2) {
        ++d;
    }

    exit_proc();
}