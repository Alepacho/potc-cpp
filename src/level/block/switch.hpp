#ifndef POTC_BLOCK_SWITCH_H
#define POTC_BLOCK_SWITCH_H

#include "solid.hpp"

class SwitchBlock : public SolidBlock {
private:
    bool pressed = false;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::SWITCH; }
    SwitchBlock() {
        trace("BLOCK::INIT", "SWITCH");
        tex = 2;
    }
    bool use(Level* level, Item* item) override;
};

#endif // POTC_BLOCK_DOOR_H
