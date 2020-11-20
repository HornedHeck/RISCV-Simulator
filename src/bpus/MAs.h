//
// Created by hornedheck on 20.11.2020.
//

#ifndef RISCV_SIMULATOR_MAS_H
#define RISCV_SIMULATOR_MAS_H

#include "../BranchPredictor.h"

class MAs : public BranchPredictor {

public:
    bool predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) override;

    void update(uint32_t pc, bool branch) override;

    std::string name() override;

private:

    static const uint8_t PHT_SIZE = 32;
    static const uint8_t BHR_COUNT = 16;

    STATE pht[PHT_SIZE] = {STATE::PNT};
    uint8_t bht[BHR_COUNT] = {0};
    uint8_t ghr = 0;

    static const uint8_t GHR_LIMIT = 4;
    static const uint8_t GHR_SIZE = 2;

    uint32_t get_index(uint32_t pc) const;

};


#endif //RISCV_SIMULATOR_MAS_H
