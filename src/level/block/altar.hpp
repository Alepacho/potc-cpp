#ifndef POTC_BLOCK_ALTAR_H
#define POTC_BLOCK_ALTAR_H

#include "block.hpp"

class AltarBlock : public Block {
private:
    bool filled = false;
    Sprite* sprite;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::ALTAR; }
    AltarBlock();
    void addEntity(Entity* entity) override;
    bool blocks(Entity* entity) override { return blocksMotion; }
};

#endif // POTC_BLOCK_ALTAR_H
