#ifndef POTC_LEVEL_ICE_H
#define POTC_LEVEL_ICE_H

#include "level.hpp"
#include "../game.hpp"

class IceLevel : public Level {
public:
    IceLevel() {
		floorCol = 0xB8DBE0;
		ceilCol = 0xB8DBE0;
		wallCol = 0x6BE8FF;
		name = "The Frost Cave";
	}

    void switchLevel(int id) override {
		if (id == 1) game->switchLevel("overworld", 5);
	}

    void getLoot(int id) override {
		Level::getLoot(id);
		if (id == 1) game->getLoot(&ITEM::skates);
	}
};

#endif // POTC_LEVEL_ICE_H