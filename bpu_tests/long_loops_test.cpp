//
// Created by hornedheck on 15.11.2020.
//

#include "lib/lib.h"

int main() {

    print_s("LONG LOOPS TEST\n");


    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 20; ++j);
    }

    exit_proc();

}
