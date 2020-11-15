//
// Created by hornedheck on 15.11.2020.
//

#include <stdint.h>
#include "lib/lib.h"

void check_null(uint64_t pointer) {
    if (!pointer) {
        print_s("Null\n");
    } else {
        print_s("Not null\n");
    }
}

int main() {
    print_s("FUNC TEST\n");
    check_null(1u);
    check_null(1u);
    check_null(0u);
    check_null(1u);
    check_null(1u);
    check_null(0u);
    check_null(1u);
    check_null(1u);
    check_null(0u);

    exit_proc();
}
