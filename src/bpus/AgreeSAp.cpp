//
// Created by hornedheck on 14.11.2020.
//

#include "AgreeSAp.h"

uint AgreeSAp::get_index(uint32_t pc, uint8_t history) {
    return (pc % PC_LIMIT << PC_OFFSET) + (history % HISTORY_LIMIT);
}

bool AgreeSAp::predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) {
    uint8_t set = get_set(pc);
    auto i = get_index(pc, bhr[set]);
    auto prediction = 1 < (uint8_t) pht[bhr[set]][i];
    auto is_agree = btb[pc % BTB_LIMIT];
    return !(prediction ^ is_agree);
}

uint8_t AgreeSAp::get_set(uint32_t pc) {
    return (pc >> SET_OFFSET) % SET_LIMIT;
}

void AgreeSAp::update(uint32_t pc, bool branch) {
    auto set = get_set(pc);
    uint8_t btb_i = pc % BTB_LIMIT;
    if (!is_btb_set[btb_i]) {
        btb[btb_i] = branch;
        is_btb_set[btb_i] = true;
    }
    auto i = get_index(pc, bhr[set]);
    auto p = pht[bhr[set]][i];
    if ((STATE::PNT < p) == btb[btb_i]) {
        if (p != STATE::T) {
            pht[bhr[set]][i] = (STATE)((uint8_t) p + 1);
        }
    } else {
        if (p != STATE::NT) {
            pht[bhr[set]][i] = (STATE)((uint8_t) p - 1);
        }
    }
    bhr[set] = (bhr[set] << 1u) % BHR_LIMIT + branch;

}

std::string AgreeSAp::name() {
    return "Agree SAp";
}
