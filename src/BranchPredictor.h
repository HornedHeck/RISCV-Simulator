/*
 * The branch perdiction module with the following strategies
 *   Always Taken
 *   Always Not Taken
 *   Backward Taken, Forward Not Taken
 *   Branch Prediction Buffer with 2bit history information
 * 
 * Created by He, Hao on 2019-3-25
 */

#ifndef BRANCH_PREDICTOR_H
#define BRANCH_PREDICTOR_H

#include <cstdint>
#include <string>

const int PRED_BUF_SIZE = 4096;

class BranchPredictor {
public:

    enum class STATE : uint8_t {
        NT = 0,
        PNT = 1,
        PT = 2,
        T = 3
    };

    virtual bool predict(uint32_t pc, uint32_t insttype, int64_t op1, int64_t op2,
                         int64_t offset) = 0;

    virtual void update(uint32_t pc, bool branch) = 0;

    virtual std::string name() = 0;

};

#endif