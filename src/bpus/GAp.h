#ifndef RISCV_SIMULATOR_GAP_H
#define RISCV_SIMULATOR_GAP_H

#include "../BranchPredictor.h"

/**
 * GHR - 5bits
 * 32 PHT with 32 entries of 2 bits
 */
class GAp : public BranchPredictor {

    bool predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2, int64_t offset) override;

    void update(uint32_t pc, bool branch) override;

public:
    std::string name() override;

private:
    static const int PHT_COUNT = 32;
    static const int PHT_ENTRIES_COUNT = 32;
    uint8_t ghr = 0;
    STATE pht[PHT_COUNT][PHT_ENTRIES_COUNT];

};


#endif //RISCV_SIMULATOR_GAP_H
