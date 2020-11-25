//
// Created by hornedheck on 23.11.2020.
//

#include "TAGE.h"
#include <math.h>

bool TAGE::predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) {
    for (int8_t i = T_COUNT - 1; i >= 0; --i) {

        auto h_len = get_history_length(i);
        auto history = get_history(h_len);
        auto r_tag = hash(pc, history, h_len);
        auto l_tag = r_tag % 8;
        if (l_tag != 7 && l_tag != 0 && (l_tag & (i + 1)) == i + 1) {
            auto h_tag = r_tag >> 3u;
            auto item = t[i][h_tag];
            if (item.u > 0) {
                return item.p > 0;
            }
        }
    }

    return T0->predict(pc, insttype, op1, op2, offset);
}

void TAGE::update_useful(uint8_t i, uint8_t tag, bool up) {
    if (up) {
        if (t[i][tag].u < 4) {
            t[i][tag].u++;
        }
    } else {
        if (t[i][tag].u > 0) {
            t[i][tag].u--;
        }
    }
}

void TAGE::update_prediction(uint8_t i, uint8_t tag, bool up) {
    if (up) {
        if (t[i][tag].p < 4) {
            t[i][tag].p++;
        }
    } else {
        if (t[i][tag].p > -4) {
            t[i][tag].p--;
        }
    }
}


void TAGE::reset_useful() {
    for (auto &i : t) {
        for (auto &j : i) {
            j.u = 0;
        }
    }
    u_reset_counter = 0;
}


void TAGE::update_ghr(bool branch) {
    ghr = (ghr << 1u) ^ branch;
}

void TAGE::update(uint32_t pc, bool branch) {
    u_reset_counter++;

//  Alternative pred data
    bool alt_pred[T_COUNT];
    uint8_t alt_count = 0;

//  Prediction component
    bool pred = T0->predict(pc, 0, 0, 0, 0);
    uint8_t pred_i = T_COUNT;
    uint8_t pred_t = 0;

//  Prediction error data;
    uint8_t highest_u_i = 0;
    uint8_t next_pos = 0;

//  Get prediction data
    for (uint8_t i = 0; i < T_COUNT; ++i) {
        auto h_len = get_history_length(i);
        auto history = get_history(h_len);
        auto r_tag = hash(pc, history, h_len);
        auto l_tag = r_tag % 8;
        if (l_tag != 7 && l_tag != 0 && (l_tag & (i + 1)) == i + 1) {
            auto h_tag = r_tag >> 3u;
            auto item = t[i][h_tag];
            if (item.u > 0) {
                highest_u_i = i;
                next_pos = i;

                if (pred_i != T_COUNT) {
                    // push to alt_pred
                    alt_pred[alt_count] = pred;
                    alt_count++;
                }
                pred_i = i;
                pred_t = h_tag;
                pred = item.p > 0;
            } else {
                if (next_pos <= highest_u_i) {
                    next_pos = i;
                }
            }
        }
    }

//  Update useful counters;
    if (alt_count > 0) {
        for (int i = 0; i < alt_count; ++i) {
            if (alt_pred[i] != pred) {
                update_useful(pred_i, pred_t, pred == branch);
                break;
            }
        }
    }

//   Choose T_i to update
    if (pred_i < T_COUNT) {
        // update T_i table
        update_prediction(pred_i, pred_t, pred == branch);
        if (pred != branch) {
            if (next_pos != highest_u_i) {
//              Ready to insert
                auto h_len = get_history_length(next_pos);
                auto history = get_history(h_len);
                auto tag = hash(pc, history, h_len) >> 3u;
                t[next_pos][tag].p = 1;
                t[next_pos][tag].u = 0;
            } else {
//              Decrement all higher T_j
                for (int i = highest_u_i + 1; i < T_COUNT; ++i) {
                    for (int j = 0; j < T_SIZE; ++j) {
                        update_useful(i, j, false);
                    }
                }
            }
        }
    } else {
        // update T0
        T0->update(pc, branch);
    }

    if (u_reset_counter == U_RESET_LIMIT) {
        reset_useful();
    }

    update_ghr(branch);
}

std::string TAGE::name() {
    return "TAGE";
}

uint8_t TAGE::get_history_length(uint8_t i) {
    return (uint8_t) (pow(a, i) * L_1 + 0.5);
}


uint64_t TAGE::get_history(uint8_t length) const {
    return ghr % (2u << length);
}

/// returns m bit len hashcode
uint16_t multiplication_hash(uint64_t src, uint64_t a, uint8_t w, uint8_t m) {
    src ^= src >> (uint8_t) (w - m);
    return (a * src) >> (uint8_t) (w - m);
}

static const uint64_t cutter_a = 89113731521u;
static const uint8_t cutter_m = 32;

uint32_t history_cutter(uint64_t history, uint8_t w) {
    if (w < cutter_m) {
        return multiplication_hash(history, cutter_a, cutter_m, w);
    } else {
        return multiplication_hash(history, cutter_a, w, cutter_m);
    }
}

uint16_t general_cutter(uint64_t src) {
    return multiplication_hash(src, cutter_a, 64, 11);
}

uint16_t TAGE::hash(uint32_t pc, uint64_t history, uint8_t h_size) {
    uint64_t src = ((uint64_t) pc << 32u) ^ history_cutter(history, h_size);
    return general_cutter(src);
}

TAGE::TAGE() {
    T0 = new GAp();
}

