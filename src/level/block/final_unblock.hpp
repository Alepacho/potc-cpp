#ifndef POTC_BLOCK_FINAL_UNBLOCK_H
#define POTC_BLOCK_FINAL_UNBLOCK_H

#include "solid.hpp"

class FinalUnlockBlock : public SolidBlock {
private:
    bool pressed = false;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::FINAL_UNBLOCK; }
    FinalUnlockBlock() {
        trace("BLOCK::INIT", "FINAL UNBLOCK");
        tex = 8 + 3;
    }
    bool use(Level* level, Item* item) override;
};

#endif // POTC_BLOCK_FINAL_UNBLOCK_H
