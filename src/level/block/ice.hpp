#ifndef POTC_BLOCK_ICE_H
#define POTC_BLOCK_ICE_H

#include "block.hpp"

class IceBlock : public Block {
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::ICE; }
    IceBlock() {
        trace("BLOCK::INIT", "ICE");
        blocksMotion = false;
		floorTex = 16;
    }
    void tick() override;
    double getWalkSpeed(Player* player) override;
    double getFriction(Player* player) override;
    bool blocks(Entity* entity) override;
};

#endif // POTC_BLOCK_ICE_H
