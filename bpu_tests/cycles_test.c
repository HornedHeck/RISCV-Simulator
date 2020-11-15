//
// Created by hornedheck on 15.11.2020.
//

#include <stdint.h>
#include "lib/lib.h"

int main() {

    print_s("CYCLES TEST\n");

    for (uint8_t i = 0; i < 5; ++i) {
        print_s("Act, ");
    }
    print_c('\n');

    for (uint8_t i = 0; i < 3; ++i) {
        for (uint8_t j = 0; j < 2; ++j) {
            print_s("Act embedded, ");
        }
        print_c('\n');
    }

    exit_proc();
}
