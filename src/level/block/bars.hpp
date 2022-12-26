#ifndef POTC_BLOCK_BARS_H
#define POTC_BLOCK_BARS_H

#include "block.hpp"

class BarsBlock : public Block {
private:
    bool open = false;
    Sprite* sprite;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::BARS; }
    BarsBlock();
    bool use(Level* level, Item* item) override;
    bool blocks(Entity* entity) override;
};

#endif // POTC_BLOCK_BARS_H
