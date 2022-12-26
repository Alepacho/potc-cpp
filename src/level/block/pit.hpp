#ifndef POTC_BLOCK_PIT_H
#define POTC_BLOCK_PIT_H

#include "block.hpp"
#include "../../utils/trace.hpp"

class PitBlock : public Block {
private:
    bool filled = false;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::PIT; }
    PitBlock() {
        trace("BLOCK::INIT", "PIT");
        floorTex = 1;
        blocksMotion = true;
    }

    void addEntity(Entity* entity) override;
    bool blocks(Entity* entity) override;
};

#endif // POTC_BLOCK_PIT_H