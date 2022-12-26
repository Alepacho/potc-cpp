#ifndef POTC_BLOCK_VANISH_H
#define POTC_BLOCK_VANISH_H

#include "solid.hpp"

class VanishBlock : public SolidBlock {
private:
    bool gone = false;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::VANISH; }

    VanishBlock() : SolidBlock() {
        trace("BLOCK::INIT", "VANISH");
        tex = 1;
    }
    bool use(Level* level, Item* item) override;
};

#endif // POTC_BLOCK_VANISH_H
