//
// Created by hornedheck on 14.11.2020.
//

#include "GAp.h"

bool GAp::predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) {
    return 1 < (uint8_t) pht[ghr][pc % PHT_ENTRIES_COUNT];
}

void GAp::update(uint32_t pc, bool branch) {
    uint32_t i = pc % PHT_ENTRIES_COUNT;
    auto value = (uint8_t) pht[ghr][i];
    if (branch) {
//        +=1
        if (value < 4) {
            pht[ghr][i] = (STATE)(value + 1);
        }
    } else {
//        -=1
        if (value > 0) {
            pht[ghr][i] = (STATE)(value - 1);
        }
    }

    ghr <<= (uint8_t) 1;
    ghr += branch;
    ghr %= PHT_COUNT;
}

std::string GAp::name() {
    return "GAp";
}
