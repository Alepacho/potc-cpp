#ifndef POTC_LEVEL_TEMPLE_H
#define POTC_LEVEL_TEMPLE_H

#include "level.hpp"
#include "../game.hpp"

class TempleLevel : public Level {
private:
	int triggerMask = 0;
public:
    TempleLevel() {
		floorCol = 0x8A6496;
		ceilCol = 0x8A6496;
		wallCol = 0xCFADDB;
		name = "The Temple";
	}

    void switchLevel(int id) override {
		if (id == 1) game->switchLevel("overworld", 3);
	}

    void getLoot(int id) override {
		Level::getLoot(id);
		if (id == 1) game->getLoot(&ITEM::skates);
	}

	void trigger(int id, bool pressed) override {
		triggerMask |= 1 << id;
		if (!pressed) triggerMask ^= 1 << id;

		if (triggerMask == 14) {
			Level::trigger(1, true);
		} else {
			Level::trigger(1, false);
		}
	}
};

#endif // POTC_LEVEL_TEMPLE_H