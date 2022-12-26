#ifndef POTC_BLOCK_WATER_H
#define POTC_BLOCK_WATER_H

#include "block.hpp"

class WaterBlock : public Block {
private:
    int steps = 0;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::WATER; }
    WaterBlock() {
        trace("BLOCK::INIT", "WATER");
        blocksMotion = true;
    }
    void tick() override;
    bool blocks(Entity* entity) override;
    double getFloorHeight(Entity* e) override { return -0.5; }
    double getWalkSpeed(Player* player) override { return 0.4; }
};

#endif // POTC_BLOCK_WATER_H
