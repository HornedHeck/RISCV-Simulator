//
// Created by hornedheck on 20.11.2020.
//

#include "PAp.h"

bool PAp::predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) {
    auto history = bht[pc % BHR_COUNT];
    return 1 < (uint8_t) pht[history][pc % PHT_SIZE];
}

void PAp::update(uint32_t pc, bool branch) {
    auto history = bht[pc % BHR_COUNT];
    auto index = pc % PHT_SIZE;
    auto p = pht[history][index];
    if ((1 < (uint8_t) p) == branch) {
        if (p != STATE::T) {
            pht[history][index] = (STATE)(1 + (uint8_t) p);
        }
    } else {
        if (p != STATE::NT) {
            pht[history][index] = (STATE)((uint8_t) p - 1);
        }
    }
    bht[pc % BHR_COUNT] = ((history << 1u) ^ branch) % PHT_COUNT;
}

std::string PAp::name() {
    return "PAp";
}
