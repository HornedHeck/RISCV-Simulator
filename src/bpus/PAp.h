//
// Created by hornedheck on 20.11.2020.
//

#ifndef RISCV_SIMULATOR_PAP_H
#define RISCV_SIMULATOR_PAP_H

#include "../BranchPredictor.h"

class PAp : public BranchPredictor {

public:
    bool predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) override;

    void update(uint32_t pc, bool branch) override;

    std::string name() override;

private:
//  Total size: 280b

    static const uint8_t BHR_COUNT = 8;
    static const uint8_t PHT_COUNT = 8;
    static const uint8_t PHT_SIZE = 16 ;

    uint8_t bht[BHR_COUNT] = {0};
    STATE pht[PHT_COUNT][PHT_SIZE] = {{STATE::PT}};

};


#endif //RISCV_SIMULATOR_PAP_H
