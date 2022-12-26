#ifndef POTC_BLOCK_SPIRIT_WALL_H
#define POTC_BLOCK_SPIRIT_WALL_H

#include "block.hpp"

class SpiritWallBlock : public Block {
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::SPIRIT_WALL; }
    SpiritWallBlock();
    bool blocks(Entity* entity) override;
};

#endif // POTC_BLOCK_SPIRIT_WALL_H
