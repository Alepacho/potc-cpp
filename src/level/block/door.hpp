#ifndef POTC_BLOCK_DOOR_H
#define POTC_BLOCK_DOOR_H

#include "solid.hpp"

class DoorBlock : public SolidBlock {
public:
    bool open = false;
    double openness = 0;

    BLOCK::TYPE type() const override { return BLOCK::TYPE::DOOR; }
    DoorBlock() {
        trace("BLOCK::INIT", "DOOR");
        tex = 4;
        solidRender = false;
    }
    bool use(Level* level, Item* item) override;
    void tick() override;
    bool blocks(Entity* entity) override;
};

#endif // POTC_BLOCK_DOOR_H
