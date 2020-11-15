//
// Created by hornedheck on 15.11.2020.
//

#include "AgreeGAp.h"


bool AgreeGAp::predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) {

    auto p = 1 < (uint8_t) pht[ghr][get_pht_index(pc, ghr)];
    auto bias = btb[get_tag(pc)];
    return p == bias;
}

void AgreeGAp::update(uint32_t pc, bool branch) {
    auto tag_i = get_tag(pc);
    if (!btb_set[tag_i]) {
        btb[tag_i] = branch;
        btb_set[branch] = true;
    } else {
        auto pht_i = get_pht_index(pc, ghr);
        if (btb[tag_i] == branch) {
            if (pht[ghr][pht_i] != STATE::T) {
                pht[ghr][pht_i] = (STATE)((uint8_t) pht[ghr][pht_i] + 1);
            }
        } else {
            if (pht[ghr][pht_i] != STATE::NT) {
                pht[ghr][pht_i] = (STATE)((uint8_t) pht[ghr][pht_i] - 1);
            }
        }

    }

    ghr <<= (uint8_t) 1;
    ghr += branch;
    ghr %= PHT_COUNT;
}

std::string AgreeGAp::name() {
    return "Agree GAp";
}

uint8_t AgreeGAp::get_tag(uint32_t pc) {
    return pc % TAG_LIMIT;
}

uint8_t AgreeGAp::get_pht_index(uint32_t pc, uint8_t ghr) {
    return (pc ^ ghr) % PHT_ENTRIES_COUNT;
}
