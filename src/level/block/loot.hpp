#ifndef POTC_BLOCK_LOOT_H
#define POTC_BLOCK_LOOT_H

#include "block.hpp"

class LootBlock : public Block {
private:
    bool taken = false;
    Sprite* sprite;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::LOOT; }
    LootBlock();
    void addEntity(Entity* entity) override;
    bool blocks(Entity* entity) override;
};

#endif // POTC_BLOCK_LOOT_H
