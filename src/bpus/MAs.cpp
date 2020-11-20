//
// Created by hornedheck on 20.11.2020.
//

#include "MAs.h"

bool MAs::predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) {
    auto history = bht[pc % BHR_COUNT];
    return history == (1 < (uint8_t) pht[get_index(pc)]);
}

void MAs::update(uint32_t pc, bool branch) {
    auto history = bht[pc % BHR_COUNT];
    auto index = get_index(pc);

    auto p = pht[index];
    bool prediction = history == (1 < (uint8_t) pht[get_index(pc)]);

    if (prediction == branch) {
        if (p != STATE::T) {
            pht[index] = (STATE)(1 + (uint8_t) p);
        }
    } else {
        if (p != STATE::NT) {
            pht[index] = (STATE)((uint8_t) p - 1);
        }
    }

    bht[pc % BHR_COUNT] = branch;
    ghr = ((ghr << 1u) ^ branch) % GHR_LIMIT;
}

std::string MAs::name() {
    return "MAs";
}

uint32_t MAs::get_index(uint32_t pc) const {
    return ((pc << GHR_SIZE) ^ ghr) % PHT_SIZE;
}
