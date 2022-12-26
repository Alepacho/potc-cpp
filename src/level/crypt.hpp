#ifndef POTC_LEVEL_CRYPT_H
#define POTC_LEVEL_CRYPT_H

#include "level.hpp"
#include "../game.hpp"

class CryptLevel : public Level {
public:
    CryptLevel() {
		floorCol = 0x404040;
		ceilCol = 0x404040;
		wallCol = 0x404040;
		name = "The Crypt";
	}

    void switchLevel(int id) override {
		if (id == 1) game->switchLevel("overworld", 2);
	}

    void getLoot(int id) override {
		Level::getLoot(id);
		if (id == 1) game->getLoot(&ITEM::flippers);
	}
};

#endif // POTC_LEVEL_CRYPT_H