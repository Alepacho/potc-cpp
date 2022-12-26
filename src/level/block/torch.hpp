#ifndef POTC_BLOCK_TORCH_H
#define POTC_BLOCK_TORCH_H

#include "block.hpp"

class TorchBlock : public Block {
private:
    Sprite* torchSprite;
public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::TORCH; }
    TorchBlock();
    void decorate(Level* level, int x, int y) override;
    void tick() override;
};

#endif // POTC_BLOCK_TORCH_H
