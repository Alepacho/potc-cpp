#ifndef POTC_LEVEL_LADDER_BLOCK_H
#define POTC_LEVEL_LADDER_BLOCK_H

#include "block.hpp"

#include "../../utils/trace.hpp"

class LadderBlock : public Block {
    private:
        int LADDER_COLOR = 0xDB8E53;
    public:
        bool wait;

    BLOCK::TYPE type() const override { return BLOCK::TYPE::LADDER; }
	LadderBlock(bool down); // see block.cpp
    void removeEntity(Entity* entity) override;
    void addEntity(Entity* entity) override;
};

#endif // POTC_LEVEL_SOLID_BLOCK_H