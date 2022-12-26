#ifndef POTC_BLOCK_PRESSURE_PLATE_H
#define POTC_BLOCK_PRESSURE_PLATE_H

#include "block.hpp"

class PressurePlateBlock : public Block {
public:
    bool pressed = false;
    BLOCK::TYPE type() const override { return BLOCK::TYPE::PRESSURE_PLATE; }
    PressurePlateBlock() {
        floorTex = 2;
    }
    void tick() override;
    double getFloorHeight(Entity* e) override {
        if (pressed) return -0.02; else return 0.02;
    }
};

#endif // POTC_BLOCK_PRESSURE_PLATE_H
