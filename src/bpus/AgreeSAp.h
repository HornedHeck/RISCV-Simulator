//
// Created by hornedheck on 14.11.2020.
//

#ifndef RISCV_SIMULATOR_AGREESAP_H
#define RISCV_SIMULATOR_AGREESAP_H

#include "../BranchPredictor.h"

/**
 * Set Size 256bit
 * Set index 3bit
 * BHR 2^3 * 5bit
 * PHT 2^3 * 2^5 * 2bit
 * TAG 3bit
 * BTB 2^3*1bit
 */
class AgreeSAp : public BranchPredictor {

public:
    bool predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) override;

    void update(uint32_t pc, bool branch) override;

    std::string name() override;

private:
    static const int SET_SIZE = 256;
    static const uint8_t SET_OFFSET = 8;
    static const uint8_t BHR_LIMIT = 32;
    static const uint8_t SET_LIMIT = 8;
    static const uint8_t PHT_LIMIT = 32;
    static const uint8_t BTB_LIMIT = 64;
    uint8_t bhr[SET_LIMIT] = {0};
    STATE pht[BHR_LIMIT][PHT_LIMIT] = {{STATE::NT}};
    bool btb[BHR_LIMIT] = {true};
    bool is_btb_set[BHR_LIMIT] = {false};

    static uint get_index(uint32_t pc, uint8_t history);

    static uint8_t get_set(uint32_t pc);
};


#endif //RISCV_SIMULATOR_AGREESAP_H
