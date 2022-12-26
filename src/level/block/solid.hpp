#ifndef POTC_LEVEL_SOLID_BLOCK_H
#define POTC_LEVEL_SOLID_BLOCK_H

#include "block.hpp"
#include "../../utils/trace.hpp"

class SolidBlock : public Block {
    public:
    BLOCK::TYPE type() const override { return BLOCK::TYPE::SOLID; }
	SolidBlock() : Block() {
		// trace("BLOCK:INIT", "SOLID");
		solidRender  = true;
		blocksMotion = true;
	}
};

#endif // POTC_LEVEL_SOLID_BLOCK_H