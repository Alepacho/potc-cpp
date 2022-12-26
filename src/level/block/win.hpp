#ifndef POTC_BLOCK_WIN_H
#define POTC_BLOCK_WIN_H

#include "block.hpp"

class WinBlock : public Block {
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::WIN; }
    void addEntity(Entity* entity) override;
};

#endif // POTC_BLOCK_WIN_H
