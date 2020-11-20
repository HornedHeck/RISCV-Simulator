//
// Created by hornedheck on 20.11.2020.
//

#include "PAs.h"

bool PAs::predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) {

    auto history = bht[pc % BHR_COUNT];

    auto set = get_set(pc);
    auto index = get_index(pc, set);

    return 1 < (uint8_t) pht[history][index];
}

void PAs::update(uint32_t pc, bool branch) {
    auto history = bht[pc % BHR_COUNT];

    auto set = get_set(pc);
    auto index = get_index(pc, set);

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

    bht[pc % BHR_COUNT] = ((history << 1u) + branch) % PHT_COUNT;
}

std::string PAs::name() {
    return "PAs";
}

uint PAs::get_set(uint32_t pc) {
    return pc >> SET_SIZE;
}

uint32_t PAs::get_index(uint32_t pc, uint32_t set) {
    return ((pc % ADDRESS_LIMIT) ^ (set << SET_OFFSET)) % PHT_SIZE;
}

