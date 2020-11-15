//
// Created by hornedheck on 15.11.2020.
//

#ifndef RISCV_SIMULATOR_AGREEGAP_H
#define RISCV_SIMULATOR_AGREEGAP_H

#include "../BranchPredictor.h"

class AgreeGAp : public BranchPredictor {

public:
    bool predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) override;

    void update(uint32_t pc, bool branch) override;

    std::string name() override;

private:
    static const int PHT_COUNT = 8;
    static const int PHT_ENTRIES_COUNT = 16;
    static const int TAG_LIMIT = 10;
    uint8_t ghr = 0;
    STATE pht[PHT_COUNT][PHT_ENTRIES_COUNT] = {{STATE::PT}};
    bool btb[TAG_LIMIT] = {false};
    bool btb_set[TAG_LIMIT] = {false};

    static uint8_t get_tag(uint32_t pc);

    static uint8_t get_pht_index(uint32_t pc, uint8_t ghr);

};


#endif //RISCV_SIMULATOR_AGREEGAP_H
