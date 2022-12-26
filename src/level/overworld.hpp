#ifndef POTC_LEVEL_OVERWORLD_H
#define POTC_LEVEL_OVERWORLD_H

#include "level.hpp"

class OverworldLevel : public Level {
public:
    OverworldLevel() {
        trace("LEVEL::INIT", "OVERWORLD");
        ceilTex = -1;
		floorCol = 0x508253;
		floorTex = 8 * 3;
		wallCol = 0xa0a0a0;
		name = "The Island";
    }

    void switchLevel(int id) override;
    void getLoot(int id) override;
};

#endif // POTC_LEVEL_OVERWORLD_H