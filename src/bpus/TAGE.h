//
// Created by hornedheck on 23.11.2020.
//

#ifndef RISCV_SIMULATOR_TAGE_H
#define RISCV_SIMULATOR_TAGE_H

#include "../BranchPredictor.h"
#include "GAp.h"

class TAGE : public BranchPredictor {

public:
    bool predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) override;

    void update(uint32_t pc, bool branch) override;

    std::string name() override;

    TAGE();

private:

    BranchPredictor *T0;

    constexpr static const float a = 2.0;
    constexpr static const float L_1 = 2.0;

    static const uint8_t T_COUNT = 6;
    static const uint16_t T_SIZE = 256;

    struct t_item {
        uint8_t u = 1;
        int8_t p = 0;
    } t[T_COUNT][T_SIZE];
    uint64_t ghr = 0;

    static const uint16_t U_RESET_LIMIT = 2048u;
    uint16_t u_reset_counter = 0;

    static uint8_t get_history_length(uint8_t i);

    static uint16_t hash(uint32_t pc, uint64_t history, uint8_t h_size);


    void update_ghr(bool branch);

    uint64_t get_history(uint8_t length) const;

    void update_useful(uint8_t i, uint8_t tag, bool branch);

    void reset_useful();

    void update_prediction(uint8_t i, uint8_t tag, bool up);
};


#endif //RISCV_SIMULATOR_TAGE_H
