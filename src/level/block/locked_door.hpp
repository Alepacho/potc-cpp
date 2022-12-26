#ifndef POTC_BLOCK_LOCKED_DOOR_H
#define POTC_BLOCK_LOCKED_DOOR_H

#include "door.hpp"

class LockedDoorBlock : public DoorBlock {
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::LOCKED_DOOR; }
    LockedDoorBlock() {
        trace("BLOCK::INIT", "LOCKED DOOR");
        tex = 5;
    }
    bool use(Level* level, Item* item) override;
    void trigger(bool pressed) override;
};

#endif // POTC_BLOCK_LOCKED_DOOR_H
