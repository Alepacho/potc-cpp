#ifndef POTC_BLOCK_CHEST_H
#define POTC_BLOCK_CHEST_H

#include "block.hpp"

class ChestBlock : public Block {
private:
    bool open = false;
    Sprite* chestSprite;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::CHEST; }
    ChestBlock();
    bool use(Level* level, Item* item) override;
};

#endif // POTC_BLOCK_ALTAR_H
